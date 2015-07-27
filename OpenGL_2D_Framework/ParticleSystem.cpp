//
//  ParticleSystem.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/25/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//
//
//  Idea from Cocos2d and LOVE game engine.
//
//

#include "ParticleSystem.h"
#include "Director.h"

ParticleSystem::ParticleSystem():
RenderableObject(),
blend(true),
posVar(glm::vec3()),
size(0),
totalCreatedParticles(0),
livingParticleNum(0),
duration(0),
totalElapsedTime(0),
startColor(Color::NONE),
startColorVar(Color::NONE),
endColor(Color::NONE),
endColorVar(Color::NONE),
applyColor(true),
speed(0),
speedVar(0),
gravityX(0),
gravityY(0),
tanAccel(0),
tanAccelVar(0),
radialAccel(0),
radialAccelVar(0),
emissionRate(0),
emitAngle(0),
emitAngleVar(0),
startSize(0),
startSizeVar(0),
endSize(0),
endSizeVar(0),
startAngle(0),
startAngleVar(0),
endAngle(0),
endAngleVar(0),
lifeTime(0),
lifeTimeVar(0),
texture(0),
vpbo(0),
cbo(0),
srbo(0),
newLifePoint(0)
{
    //use particle system shader
    this->progPtr = Director::getInstance().getProgramPtr("ParticleSystem");
}

ParticleSystem::~ParticleSystem(){
    cout << "[SYSTEM] Deleting ParticleSystem" << endl;
    for(auto it : particleList){
        delete it;
    }
    
    glDeleteBuffers(1, &vpbo);
    glDeleteBuffers(1, &cbo);
    glDeleteBuffers(1, &srbo);
}

ParticleSystem* ParticleSystem::createWithSize(string objectName, int size){
    //Create particle system with only with size, using default texture.
    ParticleSystem* newPS = new ParticleSystem();
    if(size < 0){
        cout << "[SYSTEM::WARNING] ParticleSystem must have particle size greater than 0" << endl;
        //for size to equal or greater than 0.
        size = 0;
    }
    //initialize empty particle system with size only
    newPS->initWithSize(size);
    //use default.
    newPS->initDefaultTexture();
    newPS->computeVertexData();
    newPS->setName(objectName);
    return newPS;
}

ParticleSystem* ParticleSystem::createWithLuaConfig(string objectName, string fileName){
    //create particle system with lua script.
    ParticleSystem* newPS = new ParticleSystem();
    if(newPS->initWithLua(fileName)){
        newPS->setName(objectName);
        return newPS;
    }
    else{
        cout << "[SYSTEM::ERROR] Failed to initialize ParticleSystem from Lua scrip." << endl;
        delete newPS;
        return nullptr;
    }
}

bool ParticleSystem::initWithLua(string fileName){
    //particle config (pc)
    LuaConfig* pc = LuaConfig::create(fileName);
    
    if(pc){
        //load config. setting name must be "particleSystem"
        std::string configName = "particleSystem";
        bool result = pc->loadConfig(configName, Director::getInstance().getWorkingDir() + "/../" + fileName);
        
        //LuaConfig fail check. return false if failed.
        if(result == false){
            delete pc;
            return false;
        }
        
        //read data.
        this->blend = pc->getBoolean(configName, "blend");
        this->duration = (double)pc->getFloat(configName, "duration");
        
        this->posVar = glm::vec3(pc->getFloat(configName, "posVar.x"),
                                 pc->getFloat(configName, "posVar.y"),
                                 pc->getFloat(configName, "posVar.z"));
        
        this->totalElapsedTime = 0;
        
        this->size = (int)pc->getFloat(configName, "size");
        this->livingParticleNum = 0;
        this->totalCreatedParticles = 0;
        
        this->startColor =
                Color::createWithRGBA(pc->getFloat(configName, "startColor.r"),
                                      pc->getFloat(configName, "startColor.g"),
                                      pc->getFloat(configName, "startColor.b"),
                                      pc->getFloat(configName, "startColor.a"));
        this->startColorVar =
                Color::createWithRGBA(pc->getFloat(configName, "startColorVar.r"),
                                      pc->getFloat(configName, "startColorVar.g"),
                                      pc->getFloat(configName, "startColorVar.b"),
                                      pc->getFloat(configName, "startColorVar.a"));
        this->endColor =
                Color::createWithRGBA(pc->getFloat(configName, "endColor.r"),
                                      pc->getFloat(configName, "endColor.g"),
                                      pc->getFloat(configName, "endColor.b"),
                                      pc->getFloat(configName, "endColor.a"));
        this->endColorVar =
                Color::createWithRGBA(pc->getFloat(configName, "endColorVar.r"),
                                      pc->getFloat(configName, "endColorVar.g"),
                                      pc->getFloat(configName, "endColorVar.b"),
                                      pc->getFloat(configName, "endColorVar.a"));
        this->applyColor = pc->getBoolean(configName, "applyColor");
        
        this->speed = pc->getFloat(configName, "speed");
        this->speedVar = pc->getFloat(configName, "speedVar");
        
        this->gravityX = pc->getFloat(configName, "gravityX");
        this->gravityY = pc->getFloat(configName, "gravityY");
        
        this->tanAccel = pc->getFloat(configName, "tanAccel");
        this->tanAccelVar = pc->getFloat(configName, "tanAccelVar");
        
        this->radialAccel = pc->getFloat(configName, "radialAccel");
        this->radialAccelVar = pc->getFloat(configName, "radialAccelVar");
        
        this->emitAngle = pc->getFloat(configName, "emitAngle");
        this->emitAngleVar = pc->getFloat(configName, "emitAngleVar");
        
        this->startSize = pc->getFloat(configName, "startSize");
        this->startSizeVar = pc->getFloat(configName, "startSizeVar");
        this->endSize = pc->getFloat(configName, "endSize");
        this->endSizeVar = pc->getFloat(configName, "endSizeVar");
        
        this->startAngle = pc->getFloat(configName, "startAngle");
        this->startAngleVar = pc->getFloat(configName, "startAngleVar");
        this->endAngle = pc->getFloat(configName, "endAngle");
        this->endAngleVar = pc->getFloat(configName, "endAngleVar");
        
        this->lifeTime = pc->getFloat(configName, "lifeTime");
        this->lifeTimeVar = pc->getFloat(configName, "lifeTimeVar");

        string textureName = pc->getString(configName, "textureName");
        this->initCustomTexture(textureName, GL_TEXTURE_2D);
        
        //release lua config
        delete pc;
        
        //initialize
        return this->initialize();
    }
    else{
        return false;
    }
}

void ParticleSystem::initWithSize(int size){
    //ugh...
    this->size = size;
}

void ParticleSystem::computeVertexData(){
    //get texture size. Default particle textures have all same size for both width and height
    int w, h;
    this->texture->getTextureSize(w, h);
    
    float width = (float)w / SCREEN_TO_WORLD_SCALE;
    float height = (float)h / SCREEN_TO_WORLD_SCALE;
    
    this->vertexData.push_back(vec3(-width/2, -height/2, GLOBAL_Z_VALUE));
    this->vertexData.push_back(vec3(-width/2, height/2, GLOBAL_Z_VALUE));
    this->vertexData.push_back(vec3(width/2, -height/2, GLOBAL_Z_VALUE));
    this->vertexData.push_back(vec3(width/2, height/2, GLOBAL_Z_VALUE));
    
    //quad texture UV
    uvVertexData.push_back(glm::vec2(0, 0));
    uvVertexData.push_back(glm::vec2(0, 1));
    uvVertexData.push_back(glm::vec2(1, 0));
    uvVertexData.push_back(glm::vec2(1, 1));
    
    //quad indicies
    indicesData.push_back(0);
    indicesData.push_back(1);
    indicesData.push_back(2);
    indicesData.push_back(1);
    indicesData.push_back(2);
    indicesData.push_back(3);
}

void ParticleSystem::loadVertexData(){
    glGenVertexArrays(1, &this->bufferObject.vao);
    glBindVertexArray(this->bufferObject.vao);
    
    //vertex buffer
    glGenBuffers(1, &this->bufferObject.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glGenBuffers(1, &this->bufferObject.uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glGenBuffers(1, &this->bufferObject.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferObject.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
    
    //allocating blank position buffer
    glGenBuffers(1, &this->vpbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vpbo);
    glBufferData(GL_ARRAY_BUFFER, this->size * sizeof(glm::vec3), NULL, GL_STREAM_DRAW);
    glVertexAttribPointer(progPtr->attrib("posVert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //color
    glGenBuffers(1, &this->cbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->cbo);
    glBufferData(GL_ARRAY_BUFFER, this->size * sizeof(glm::vec4), NULL, GL_STREAM_DRAW);
    glVertexAttribPointer(progPtr->attrib("particleColor"), 4/*RGBA*/, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //size
    glGenBuffers(1, &this->srbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->srbo);
    glBufferData(GL_ARRAY_BUFFER, this->size * sizeof(glm::vec4), NULL, GL_STREAM_DRAW);
    glVertexAttribPointer(progPtr->attrib("particleTransform"), 4, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindVertexArray(0);
}

void ParticleSystem::initDefaultTexture(){
    assert(!this->texture);
    texture = Texture::createTextureWithFile("default_particle.png", GL_TEXTURE_2D);
    assert(this->texture);
}

void ParticleSystem::initCustomTexture(string textureName, GLenum target){
    //if it already has default texture, delete it
    if(texture)
        delete texture;
    
    //If vertex array is already generated
    if(this->bufferObject.vao){
        //delete all buffer and generate new
        glDeleteBuffers(1, &this->vpbo);
        glDeleteBuffers(1, &this->cbo);
        glDeleteBuffers(1, &this->srbo);
        this->deleteVertexData();
    }
    //create single texture
    texture = Texture::createTextureWithFile(textureName, target);

    //compute vertex data, uv coordinate and indices.
    this->computeVertexData();
    this->loadVertexData();
}

bool ParticleSystem::initialize(){
    //duration must be greater than 0. Be strict on duration
    if(this->duration <= 0){
        cout << "[SYSTEM::ERROR] ParticleSystem's duration can not be greater than 0." << endl;
        return false;
    }
    
    //comptue emmisionRate
    this->emissionRate = (float)(((double)this->size) / this->duration);
    //emit angle
    if(this->emitAngle > 360 || this->emitAngle < 0){
        //wrap it into boundary if it's too big
        Utility::wrapAngle(this->emitAngle);
        cout << "[SYSTEM::WARNING] ParticleSystem's emission angle must be in range of 0 to 360 degrees." << endl;
    }
    //limit emit
    if(this->emitAngleVar > 360 || this->emitAngleVar < 0){
        //wrap it into boundary if it's too big
        Utility::wrapAngle(this->emitAngleVar);
        cout << "[SYSTEM::WARNING] ParticleSystem's emission angle variation must be in range of 0 to 360 degrees." << endl;
    }
    
    //take care lifeTime and lifeTimeVar issue on particle creation
    
    //new seed
    srand((unsigned int)time(NULL));
    
    return true;
}

void ParticleSystem::update(){
    //get elapsed time
	double elapsedTime = Timer::getInstance().getElapsedTime();
    
    //update number for new particles.
    //do this unitl it spawns all particles
    if(this->totalCreatedParticles < this->size){
        //add up elapsed time
        this->totalElapsedTime = elapsedTime;
        
        //init vars
        int newParticleNumber = 0;
        float curLifePoint = 0;
        
        //compute.
        if(this->totalElapsedTime < this->duration){
            //if time didn't exceed duration, use all elapsed time
            curLifePoint = this->emissionRate * (float)elapsedTime;
            //ignore floating points
            newParticleNumber += floor(curLifePoint);
            //store floating points
            newLifePoint += (curLifePoint - newParticleNumber);
            if(newLifePoint > 1){
                //if stored floating points gathered enough to build new particle
                //it can be more than one. get it.
                int additionalParticle = newLifePoint / 1;
                //sub. goes back to < 1
                newLifePoint -= additionalParticle;
                //prepare to spawn
                newParticleNumber += additionalParticle;
            }
        }
        else{
            //get elapsed time without exceed time. Same as above but just using valied time
            double exceededTime = this->totalElapsedTime - this->duration;
            double valiedTime = elapsedTime - exceededTime;
            curLifePoint = this->emissionRate * valiedTime;
            newParticleNumber += floor(curLifePoint);
            newLifePoint+= (curLifePoint - newParticleNumber);
        }
        
        //sum up.
        totalCreatedParticles += newParticleNumber;
        
        //if no particle is created
        if (totalCreatedParticles == 0)
            return;
        
        //add new particle
        for (int i = 0; i<newParticleNumber; ++i){
            //generate random values
            //lifeTime
            float minLifeTime = this->lifeTime - this->lifeTimeVar;
            if(minLifeTime < 0)
                minLifeTime = 0;
            float maxLifeTime = this->lifeTime + this->lifeTimeVar;
            float randLifeTime = Utility::randRange(minLifeTime, maxLifeTime);
            
            //speed
            float minSpeed = this->speed - this->speedVar;
            float maxSpeed = this->speed + this->speedVar;
            float randSpeed = Utility::randRange(minSpeed, maxSpeed);
            
            //emitAngle
            float minEmitAngle = this->emitAngle - this->emitAngleVar;
            float maxEmitAngle = this->emitAngle + this->emitAngleVar;
            float randEmitAngle = Utility::randRange(minEmitAngle, maxEmitAngle);
            
            //create, init, add
            float maxX = this->position.x + this->posVar.x;
            float minX = this->position.x - this->posVar.x;
            float maxY = this->position.y + this->posVar.y;
            float minY = this->position.y + this->posVar.y;
            float randX = Utility::randRange(minX, maxX);
            float randY = Utility::randRange(minY, maxY);
            randX /= SCREEN_TO_WORLD_SCALE;
            randY /= SCREEN_TO_WORLD_SCALE;
            
            //radial
            float minRadial = this->radialAccel - this->radialAccelVar;
            float maxRadial = this->radialAccel + this->radialAccelVar;
            float randRadial = Utility::randRange(minRadial, maxRadial);
            
            //tan
            float minTan = this->tanAccel - this->tanAccelVar;
            float maxTan = this->tanAccel + this->tanAccelVar;
            float randTan = Utility::randRange(minTan, maxTan);
            
            glm::vec2 dirVec
                    = glm::vec2(
                                cosf(randEmitAngle * M_PI / 180.0f),
                                sinf(randEmitAngle * M_PI / 180.0f)
                                ) * randSpeed / POWER_SCALE;
            
            //color
            Color minStartColor = startColor - startColorVar;
            Color maxStartColor = startColor + startColorVar;
            Color randStartColor =
                        Color::createWithRGBA(
                                Utility::randRange(minStartColor.getR(), maxStartColor.getR()),
                                Utility::randRange(minStartColor.getG(), maxStartColor.getG()),
                                Utility::randRange(minStartColor.getB(), maxStartColor.getB()),
                                Utility::randRange(minStartColor.getA(), maxStartColor.getA())
                                             );
            
            Color minEndColor = endColor - endColorVar;
            Color maxEndColor = endColor + endColorVar;
            Color randEndColor =
                        Color::createWithRGBA(
                                Utility::randRange(minEndColor.getR(), maxEndColor.getR()),
                                Utility::randRange(minEndColor.getG(), maxEndColor.getG()),
                                Utility::randRange(minEndColor.getB(), maxEndColor.getB()),
                                Utility::randRange(minEndColor.getA(), maxEndColor.getA())
                                 );
            
            float minStartSize = this->startSize - this->startSizeVar;
            float maxStartSize = this->startSize + this->startSizeVar;
            float randStartSize = Utility::randRange(minStartSize, maxStartSize);
            
            float randEndSize = 0;
            if(this->endSize == -1){
                randEndSize = randStartSize;
            }
            else{
                float minEndSize = this->endSize - this->endSizeVar;
                float maxEndSize = this->endSize + this->endSizeVar;
                randEndSize = Utility::randRange(minEndSize, maxEndSize);
            }
            
            float minStartAngle = this->startAngle - this->startAngleVar;
            float maxStartAngle = this->startAngle + this->startAngleVar;
            float randStartAngle = Utility::randRange(minStartAngle, maxStartAngle);
            
            float minEndAngle = this->endAngle - this->endAngleVar;
            float maxEndAngle = this->endAngle + this->endAngleVar;
            float randEndAngle = Utility::randRange(minEndAngle, maxEndAngle);
            
            Particle* p = new Particle();
            p->pos = glm::vec2(randX, randY);
            p->lifeTime = randLifeTime;
            p->speed = randSpeed;
            p->dirVec = dirVec;
            p->radialAccel = randRadial;
            p->tanAccel = randTan;
            p->spawnedPosition = p->pos;
            p->setColor(randStartColor, randEndColor);
            p->setSize(randStartSize, randEndSize);
            p->setAngle(randStartAngle, randEndAngle);
            
            particleList.push_back(p);
        }
    }

	//update particles data
    int liveCount = 0;
    
    //distance vector.
    std::vector<GLfloat> vertexDistanceData;
    
    //color vector
    std::vector<glm::vec4> colorData;
    
    //size
    std::vector<glm::vec4> scaleRotData;
    
    //spin
//    std::vector<float> angleData;

	//iterate through particle list
	for (std::list<Particle*>::const_iterator ci = particleList.begin(); ci != particleList.end();) {
		//get time val
		double lifeTime = (*ci)->lifeTime;
		double livedTime = (*ci)->livedTime;

		//if particle was alive on previous iteration
		if (livedTime < lifeTime){
			//update and get particle's up time
			(*ci)->livedTime += elapsedTime;
			//update
			livedTime = (*ci)->livedTime;

			//if particle's time didn't exceed its life time
            if(livedTime < lifeTime){
                //bunch of vec2s
                glm::vec2 tmp, radial, tangential, gravity;
                
                //initialize like always.
                tmp = glm::vec2();
                radial = glm::vec2();
                tangential = glm::vec2();
                gravity = glm::vec2(gravityX, gravityY);
                
                //pointer.
                Particle* p = (*ci);
                
                //get normalize. make sure subtract spawn pos distance from currnet particle's distance to compute normal from the spawn point not the origin of the screen since particle posistion is from the origin of the screen.
                glm::vec2 norm = p->pos - p->spawnedPosition;
                
                if(norm.x || norm.y){
                    //normalize. Not sure if it work with glm::normalize
                    float x = norm.x;
                    float y = norm.y;
                    float n = x * x + y * y;
                    
                    if(n != 1.0f){
                        n = sqrt(n);
                        if(n != 0){
                            n = 1.0f / n;
                            x *= n;
                            y *= n;
                        }
                    }
                    
                    radial = glm::vec2(x, y);
                }
                
                //assign same thing to tangential vector with radial
                tangential = radial;
                //apply radial acceleration to radial vector
                radial = radial * p->radialAccel;
                
                //now flip x and y with -y to y.
                float newY = tangential.x;
                tangential.x = -tangential.y;
                tangential.y = newY;
                //apply tangential acceleration
                tangential = tangential * p->tanAccel;
                
                //sum up all vectors and apply time
                tmp = radial + tangential + gravity;
                tmp *= elapsedTime;
                
                //update the direction vector
                p->dirVec = p->dirVec + tmp / POWER_SCALE;
                
                //move particle based on new direction vector
                tmp = glm::vec2(p->dirVec.x * elapsedTime, p->dirVec.y * elapsedTime);
                p->pos = p->pos + tmp;
                
                //deal color here!
                Color curColor = Color::WHITE;
                if(this->applyColor){
                    curColor = p->getCurColor();
                }
                colorData.push_back(curColor.getRGBA());
//                Utility::printVec4(curColor.getRGBA());
                
                //deal size & rotation here!
                float newSizeScale = p->getCurSize() / DEFAULT_SIZE_RATE;
                glm::vec3 scaleVec(newSizeScale, newSizeScale, 1.0f);
                glm::mat4 scaleMatrix = glm::scale(glm::mat4(), scaleVec);
                
                float newAngle = p->getCurAngle();
                glm::mat4 scaleRotMat = glm::rotate(scaleMatrix, newAngle, Utility::Z_AXIS);
                
                scaleRotData.push_back(glm::vec4(scaleRotMat[0][0], scaleRotMat[0][1], scaleRotMat[1][0], scaleRotMat[1][1]));
                
                //update pos vert.
                //beware that all rendering starts from world origin (0, 0).
                //origin -> spawn pos -> current particle pos.
                vertexDistanceData.push_back(p->pos.x);
                vertexDistanceData.push_back(p->pos.y);
                vertexDistanceData.push_back(0);
                
				//increment iterator
				++ci;
				//count
				liveCount++;
            }
            else{
                //dead. remove. erase function return the next element. So we don't increment iterator
				delete (*ci);
				ci = particleList.erase(ci);
            }
        }
		else{
			//what?
		}
    }

	livingParticleNum = liveCount;

    //update Data
    if (livingParticleNum > 0){
        glBindBuffer(GL_ARRAY_BUFFER, vpbo);
		glBufferData(GL_ARRAY_BUFFER, livingParticleNum * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, livingParticleNum * sizeof(GLfloat) * 3, &vertexDistanceData[0]); // Buffer orphaning, a common way to improve streaming perf. See above link for details. So clearing data?
        
        glBindBuffer(GL_ARRAY_BUFFER, cbo);
        assert(colorData.size() == livingParticleNum);
        glBufferData(GL_ARRAY_BUFFER, livingParticleNum * sizeof(glm::vec4), NULL, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, livingParticleNum * sizeof(glm::vec4), &colorData[0]); // Buffer orphaning, a common way to improve streaming perf. See above link for details. So clearing data?
        
        glBindBuffer(GL_ARRAY_BUFFER, srbo);
        assert(scaleRotData.size() == livingParticleNum);
        glBufferData(GL_ARRAY_BUFFER, livingParticleNum * sizeof(glm::vec4), NULL, GL_STREAM_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, livingParticleNum * sizeof(glm::vec4), &scaleRotData[0]); // Buffer orphaning, a common way to improve streaming perf. See above link for details. So clearing data?
	}
    
    RenderableObject::update();
}

void ParticleSystem::render(){
    //pre condition check before render
    if(!this->RenderableObject::visible) return;
    if(this->livingParticleNum == 0) return;
    
    if(this->blend)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    glUseProgram(this->progPtr->getObject());
    
    if(this->texture->canBoundThisTexture()){
        texture->bind(GL_TEXTURE0);
    }
    
    //get main camera
    glm::mat4 cameraMat = Director::getInstance().getCameraPtr()->getMatrix();
    matrixUniformLocation("cameraMat", cameraMat);
    
    //get parent matrix
    glm::mat4 parentMat;
    if(this->parent){
        parentMat = this->parent->getTransformMat();
    }
    
    matrixUniformLocation("parentMat", parentMat);
    matrixUniformLocation("modelMat", this->modelMat);
    matrixUniformLocation("rotateMat", this->rotateMat);
    mat4 tMat = mat4();
    matrixUniformLocation("translateMat", tMat);
    matrixUniformLocation("scaleMat", this->scaleMat);
//    floatUniformLocation("opacity", this->opacity);
    
    //bind vertex array
    glBindVertexArray(this->bufferObject.vao);
    
    //enable attribs
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
    glEnableVertexAttribArray(progPtr->attrib("posVert"));
    glEnableVertexAttribArray(progPtr->attrib("particleColor"));
    glEnableVertexAttribArray(progPtr->attrib("particleTransform"));
    
    //Divisor
    glVertexAttribDivisor(progPtr->attrib("vert"), 0);		//0. Always use same quad vertex
    glVertexAttribDivisor(progPtr->attrib("uvVert"), 0);	//0. Always use same indices
    glVertexAttribDivisor(progPtr->attrib("posVert"), 1);	//1, Use 1 pos(vec3) value for each quad
    glVertexAttribDivisor(progPtr->attrib("particleColor"), 1);	//1, Use 1 color(vec4) value for each quad
    glVertexAttribDivisor(progPtr->attrib("particleTransform"), 1);	//1, Use 1 scaleXY(vec2) value for each quad
    
    //draw living particles
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, livingParticleNum);
    glBindVertexArray(0);
    glUseProgram(0);
    
    if(this->blend)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool ParticleSystem::isDead(){
    //if time is up
    if(totalElapsedTime >= duration){
        //if all particle is dead
        if(particleList.size() == 0){
            return true;
        }
    }
    return false;
}