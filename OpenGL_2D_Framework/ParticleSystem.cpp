//
//  ParticleSystem.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/25/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ParticleSystem.h"
#include "Director.h"

ParticleSystem::ParticleSystem():
RenderableObject(),
size(0),
totalCreatedParticles(0),
livingParticleNum(0),
liveCount(0),
duration(0),
totalElapsedTime(0),
startColor(Color::NONE),
startColorVar(Color::NONE),
endColor(Color::NONE),
endColorVar(Color::NONE),
applyColor(true),
applyOpacity(true),
speed(0),
speedVar(0),
gravityX(0),
gravityXVar(0),
gravityY(0),
gravityYVar(0),
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
lifeTime(0),
lifeTimeVar(0),
texture(0),
usingDefaultTexture(true),
vpbo(0),
newLifePoint(0)
{
    this->progPtr = Director::getInstance().getProgramPtr("ParticleSystem");
//    this->totalCreatedParticles = 0;
//	this->newLifePoint = 0;
}

ParticleSystem::~ParticleSystem(){
    cout << "[SYSTEM] Deleting ParticleSystem" << endl;
    for(std::list<Particle*>::const_iterator ci = particleList.begin(); ci != particleList.end(); ++ci){
        delete (*ci);
    }
    
    glDeleteBuffers(1, &vpbo);
}

ParticleSystem* ParticleSystem::createWithSize(string objectName, int size){
    ParticleSystem* newPS = new ParticleSystem();
    if(size < 0){
        cout << "[SYSTEM::WARNING] ParticleSystem must have particle size greater than 0" << endl;
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
    ParticleSystem* newPS = new ParticleSystem();
    if(newPS->initWithLua(fileName)){
        newPS->setName(objectName);
        return newPS;
    }
    else{
        cout << "[SYSTEM::ERROR] Failed to initialize ParticleSystem from xml." << endl;
        delete newPS;
        return nullptr;
    }
}

bool ParticleSystem::initWithLua(string fileName){
    //particle config (pc)
    LuaConfig* pc = LuaConfig::create(fileName);
    
    if(pc){
        std::string configName = "particleSystem";
        pc->loadConfig(configName, Director::getInstance().getWorkingDir() + "/../" + fileName);
        this->duration = (double)pc->getFloat(configName, "duration");
        this->totalElapsedTime = 0;
        this->size = (int)pc->getFloat(configName, "size");
        this->livingParticleNum = 0;
        this->totalCreatedParticles = 0;
        this->liveCount = 0;
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
        this->applyOpacity = pc->getBoolean(configName, "applyOpacity");
        this->speed = pc->getFloat(configName, "speed");
        this->speedVar = pc->getFloat(configName, "speedVar");
        this->gravityX = pc->getFloat(configName, "gravityX");
        this->gravityXVar = pc->getFloat(configName, "gravityXVar");
        this->gravityY = pc->getFloat(configName, "gravityY");
        this->gravityYVar = pc->getFloat(configName, "gravityYVar");
        this->tanAccel = pc->getFloat(configName, "tanAccel");
        this->tanAccelVar = pc->getFloat(configName, "tanAccelVar");
        this->radialAccel = pc->getFloat(configName, "radialAccel");
        this->radialAccelVar = pc->getFloat(configName, "radialAccelVar");
//        this->emissionRate = (float)(((double)this->size) / this->duration);
        this->emitAngle = pc->getFloat(configName, "emitAngle");
        this->emitAngleVar = pc->getFloat(configName, "emitAngleVar");
        this->startSize = pc->getFloat(configName, "startSize");
        this->startSizeVar = pc->getFloat(configName, "startSizeVar");
        this->endSize = pc->getFloat(configName, "endSize");
        this->endSizeVar = pc->getFloat(configName, "endSizeVar");
        this->lifeTime = pc->getFloat(configName, "lifeTime");
        this->lifeTimeVar = pc->getFloat(configName, "lifeTimeVar");

        string textureName = pc->getString(configName, "textureName");
        this->initCustomTexture(textureName, GL_TEXTURE_2D);
        delete pc;
        
        return this->initialize();
    }
    else{
        return false;
    }
}

void ParticleSystem::initWithSize(int size){
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
    
    glBindVertexArray(0);
}

void ParticleSystem::initDefaultTexture(){
    assert(!this->texture);
    texture = Texture::createTextureWithFile("system/default_particle.png", GL_TEXTURE_2D);
    assert(this->texture);
    this->usingDefaultTexture = true;
}

void ParticleSystem::initCustomTexture(string textureName, GLenum target){
    //if it already has default texture, delete it
    if(texture)
        delete texture;
    this->usingDefaultTexture = false;
    
    //If vertex array is already generated
    if(this->bufferObject.vao){
        //delete all buffer and generate new
        glDeleteBuffers(1, &this->vpbo);
        this->deleteVertexData();
    }
    //create single texture
    texture = Texture::createTextureWithFile(textureName, target);

    //compute vertex data, uv coordinate and indices.
    this->computeVertexData();
    
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
    
    glBindVertexArray(0);
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

//void ParticleSystem::initParticleSystem(double duration, double lifeTime, double lifeTimeVar, float speed, float speedVar, double emitAngle, double emitAngleVar, float gravityX, float gravityY){
//    this->duration = duration;
//
//	this->particlePerSec = this->totalParticleCount / this->duration;
//    
//	//if particle's life time variance is greater than base life time, we force to set life time 1 greater than life time var
//	if (lifeTime < lifeTimeVar)
//		lifeTime = lifeTimeVar + 1;
//
//    this->lifeTime = lifeTime;
//    this->lifeTimeVar = lifeTimeVar;
//    
//    this->speed = speed;
//    this->speedVar = speedVar;
//    
//	//limite boundary
//	if (emitAngle > 360)
//		emitAngle = 360;
//	else if (emitAngle < 0)
//		emitAngle = 0;
//
//    this->emitAngle = emitAngle;
//
//	if (emitAngleVar > 360)
//		emitAngleVar = 360;
//	else if (emitAngleVar < 0)
//		emitAngleVar = 0;
//
//    this->emitAngleVar = emitAngleVar;
//    
//    this->gravityX = gravityX;
//    this->gravityY = gravityY;
//    
//
//	//rand seed
//	srand((unsigned int)time(NULL));
//}

void ParticleSystem::update(){
    //get elapsed time
	double elapsedTime = Timer::getInstance().getElapsedTime();

    //distance vector.
	std::vector<GLfloat> vertexDistanceData;

    //if total create particles is less than total size
	if (this->totalCreatedParticles <= this->size){
		//add to total
		totalElapsedTime += elapsedTime;

		int newParticleNumber = 0;
		float currentPoint = 0;

        //check time
        if (totalElapsedTime <= duration){
            //if particle system isn't dead yet
            //build up point
			currentPoint = this->emissionRate * (float)elapsedTime;
		}
		else{
            //particle is done with creating particle.
            //compute remaining time
			float remainingTime = elapsedTime - (totalElapsedTime - duration);
            //build up point with remaining time
			currentPoint = this->emissionRate * remainingTime;
		}

		//if the point hasn't stacked up to 1 yet,
		if (currentPoint < 1){
			//add it
			this->newLifePoint += currentPoint;
			//if newLifePoint is bigger than 1, need to add particle
			if (newLifePoint >= 1){
				//newParticleNumber = floor(newLifePoint);
				newParticleNumber = newLifePoint / 1;
				//keep the fractional point for later
				newLifePoint -= newParticleNumber * 1;
			}
		}
		//else, add new particle
		else{
			newParticleNumber = floor(currentPoint);
			newLifePoint += (currentPoint - newParticleNumber);
		}

		//update data
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
            float randLifeTime = Utility::computeRandom(minLifeTime, maxLifeTime);
            
            //speed
            float minSpeed = this->speed - this->speedVar;
            if(minSpeed < 0)
                minSpeed = 0;
            float maxSpeed = this->speed + this->speedVar;
            float randSpeed = Utility::computeRandom(minSpeed, maxSpeed);
            
            //emitAngle
            float minEmitAngle = this->emitAngle - this->emitAngleVar;
            if(minEmitAngle < 0)
                minEmitAngle = 0;
            float maxEmitAngle = this->emitAngle + this->emitAngleVar;
            float randEmitAngle = Utility::computeRandom(minEmitAngle, maxEmitAngle);
            
            //create, init, add
            Particle* newParticle = new Particle();
            newParticle->initParticle(glm::vec2(), randLifeTime, randSpeed, randEmitAngle);
            particleList.push_back(newParticle);
		}
	}

	//update particles data
	int liveCount = 0;

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
                double directionAngle = (*ci)->direction;
                float speed = (*ci)->speed;

				float movedX = (float)cos(directionAngle * M_PI / 180) * elapsedTime * speed;
				float movedY = (float)sin(directionAngle * M_PI / 180) * elapsedTime * speed;
                
                //gravity
				float gAccelX = 0, gAccelY = 0;

				if (gravityX != 0)
					gAccelX = GRAVITY * (float)livedTime * (gravityX / 3000);
                if(gravityY != 0)
					gAccelY = GRAVITY * (float)livedTime * (gravityY / 3000);
                
				//get current distance
				glm::vec2 currentDistance = (*ci)->positionData;

				//calculate new distace
				float xMoved = currentDistance.x + movedX + gAccelX;
				float yMoved = currentDistance.y + movedY + gAccelY;

				//update data
				(*ci)->updateDistnace(xMoved, yMoved);

				//push back to vector
				vertexDistanceData.push_back(xMoved);
				vertexDistanceData.push_back(yMoved);
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
    glBindBuffer(GL_ARRAY_BUFFER, vpbo);
	if (livingParticleNum > 0){
		glBufferData(GL_ARRAY_BUFFER, livingParticleNum * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, livingParticleNum * sizeof(GLfloat) * 3, &vertexDistanceData[0]); // Buffer orphaning, a common way to improve streaming perf. See above link for details. So clearing data?
	}
}

void ParticleSystem::render(){
    //pre condition check before render
    if(!this->RenderableObject::visible) return;
    if(this->livingParticleNum == 0) return;
    
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
    matrixUniformLocation("translateMat", this->translateMat);
    matrixUniformLocation("scaleMat", this->scaleMat);
    floatUniformLocation("opacity", this->opacity);
    
    //bind vertex array
    glBindVertexArray(this->bufferObject.vao);
    
    //enable attribs
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
    glEnableVertexAttribArray(progPtr->attrib("posVert"));
    
    //Divisor
    glVertexAttribDivisor(progPtr->attrib("vert"), 0);		//0. Always use same quad vertex
    glVertexAttribDivisor(progPtr->attrib("uvVert"), 0);	//0. Always use same indices
    glVertexAttribDivisor(progPtr->attrib("posVert"), 1);	//1, Use 1 pos(vec3) value for each quad
    
    //draw living particles
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, livingParticleNum);
    glBindVertexArray(0);
    glUseProgram(0);
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