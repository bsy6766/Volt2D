//
//  ParticleSystem.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/25/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "ParticleSystem.h"

using std::cout;
using std::endl;

ParticleSystem::ParticleSystem(int size){
    this->totalParticleCount = size;
    this->totalElapsedTime = 0;
    this->totalCreatedParticles = 0;
    this->position = glm::vec2(640, 360);   //default position
    this->visible = true;
	this->newLifePoint = 0;
}

ParticleSystem::~ParticleSystem(){
    cout << "deleting particle system" << endl;
    for(std::list<Particle*>::const_iterator ci = particleList.begin(); ci != particleList.end(); ++ci){
        delete (*ci);
    }

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vpbo);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &uvbo);
}

ParticleSystem* ParticleSystem::initWithParticleSize(int size){
    ParticleSystem *ret = new ParticleSystem(size);
    return ret;
}

void ParticleSystem::initParticleTexture(GLenum _textureTarget, const std::string& _fileName, Program *progPtr){
    this->progPtr = progPtr;
    texture = new Texture(_textureTarget, _fileName);
    texture->load(progPtr->getObject());
    int w,h;
    texture->getImageSize(w, h);
    
    cout << "create particle texture with path of " << _fileName << endl;
    
    float width = (float)w / 10;
    float height = (float)h / 10;
    
    const GLfloat vertices[] = {
        -(width/2), -(height/2), 0,
        -(width/2), height/2, 0,
        width/2, -(height/2), 0,
        width/2, height/2, 0
    };
    
    for(int i = 0; i<12; i++){
        vertexData.push_back(vertices[i]);
    }
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //vertex buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
    
    //allocating blank position buffer
    glGenBuffers(1, &vpbo);
    glBindBuffer(GL_ARRAY_BUFFER, vpbo);
    glBufferData(GL_ARRAY_BUFFER, totalParticleCount * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
    glVertexAttribPointer(progPtr->attrib("posVert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindVertexArray(0);
}

void ParticleSystem::initParticleSystem(double duration, double lifeTime, double lifeTimeVar, float speed, float speedVar, double emitAngle, double emitAngleVar, float gravityX, float gravityY){
    this->duration = duration;

	this->particlePerSec = this->totalParticleCount / this->duration;
    
	//if particle's life time variance is greater than base life time, we force to set life time 1 greater than life time var
	if (lifeTime < lifeTimeVar)
		lifeTime = lifeTimeVar + 1;

    this->lifeTime = lifeTime;
    this->lifeTimeVar = lifeTimeVar;
    
    this->speed = speed;
    this->speedVar = speedVar;
    
	//limite boundary
	if (emitAngle > 360)
		emitAngle = 360;
	else if (emitAngle < 0)
		emitAngle = 0;

    this->emitAngle = emitAngle;

	if (emitAngleVar > 360)
		emitAngleVar = 360;
	else if (emitAngleVar < 0)
		emitAngleVar = 0;

    this->emitAngleVar = emitAngleVar;
    
    this->gravityX = gravityX;
    this->gravityY = gravityY;
    
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

	//rand seed
	srand((unsigned int)time(NULL));
}

void ParticleSystem::update(){
    //get time
	double elapsedTime = Timer::getInstance().getElapsedTime();
	//cout << "elapsed time = " << elapsedTime << endl;
	std::vector<GLfloat> vertexDistanceData;

	if (totalCreatedParticles <= totalParticleCount){

		//add to total
		totalElapsedTime += elapsedTime;
		//cout << "total elapsed time = " << totalElapsedTime << endl;

		int newParticleNumber = 0;
		float currentPoint = 0;

		//if particle system isn't dead yet
		if (totalElapsedTime <= duration){
			currentPoint = this->particlePerSec * (float)elapsedTime;
		}
		else{
			float remainingTime = elapsedTime - (totalElapsedTime - duration);
			currentPoint = this->particlePerSec * remainingTime;
		}

		//if the point hasn't stacked up to 1 yet,
		if (currentPoint < 1){
			//add it
			newLifePoint += currentPoint;
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

		//if (newParticleNumber)
		//	cout << totalCreatedParticles << " particles created so far..." << endl;

		//add new particle
		for (int i = 0; i<newParticleNumber; ++i){
			//new particle
			particleList.push_back(new Particle());
			//init
			particleList.back()->initParticle(
				glm::vec2(),
				computeRandom(lifeTime - lifeTimeVar, lifeTime + lifeTimeVar),
				computeRandom(speed - speedVar, speed + speedVar),
				computeRandom(emitAngle - emitAngleVar / 2, emitAngle + emitAngleVar / 2)
				);

			cout << "Created new particle with lifetime = " << particleList.back()->lifeTime << endl;
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
			//cout << "particle #" << index / 4 << " lived time = " << livedTime << endl;

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
				cout << "particle dead" << endl;
            }
        }
		else{
			//what?
		}
    }

	livingParticleNum = liveCount;
	//cout << "currently living particle = " << livingParticleNum << endl;

	//if (livingParticleNum == 0){
	//	glBindBuffer(GL_ARRAY_BUFFER, vpbo);
	//	glBufferData(GL_ARRAY_BUFFER, totalParticleCount * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details. So clearing data?
	//	return;
	//}

    //update Data
    glBindBuffer(GL_ARRAY_BUFFER, vpbo);
	if (livingParticleNum > 0){
		glBufferData(GL_ARRAY_BUFFER, livingParticleNum * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, livingParticleNum * sizeof(GLfloat) * 3, &vertexDistanceData[0]); // Buffer orphaning, a common way to improve streaming perf. See above link for details. So clearing data?
	}
//    glBufferSubData(GL_ARRAY_BUFFER, 0, liveCount * sizeof(GLfloat) * 4, &vertexDistanceData[0]);
	//if (livingParticleNum > 0)
	//	glBufferSubData(GL_ARRAY_BUFFER, 0, livingParticleNum * sizeof(GLfloat) * 3, &vertexDistanceData[0]);
	//cout << "size = " << vertexDistanceData.size() << endl;
}

void ParticleSystem::render(){
    if(visible && livingParticleNum > 0){
        texture->bind(GL_TEXTURE0);
        
        GLint modelUniformLocation = glGetUniformLocation(progPtr->getObject(), "modelMat");
        if(modelUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "modelMat");
        glm::mat4 modelMat = glm::mat4();
        glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, &modelMat[0][0]);
        
        GLint opacityUniformLocation = glGetUniformLocation(progPtr->getObject(), "opacity");
        if(opacityUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "opacity");
        float opacity = 255;
        glUniform1fv(opacityUniformLocation, 1, &opacity);
        
        GLint particleUniformLocation = glGetUniformLocation(progPtr->getObject(), "particle");
        if(particleUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "particle");
        glUniform1i(particleUniformLocation, 1);
        
        glBindVertexArray(vao);
        glEnableVertexAttribArray(progPtr->attrib("vert"));
        glEnableVertexAttribArray(progPtr->attrib("uvVert"));
        glEnableVertexAttribArray(progPtr->attrib("posVert"));
        
        glVertexAttribDivisor(progPtr->attrib("vert"), 0);
        glVertexAttribDivisor(progPtr->attrib("uvVert"), 0);
        glVertexAttribDivisor(progPtr->attrib("posVert"), 1);
        
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, livingParticleNum);
    }
}

void ParticleSystem::setPosition(glm::vec2 position){
    this->position = position;
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