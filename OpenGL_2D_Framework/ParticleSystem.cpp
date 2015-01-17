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
    glBufferData(GL_ARRAY_BUFFER, totalParticleCount * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
    glVertexAttribPointer(progPtr->attrib("posVert"), 4, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindVertexArray(0);
}

void ParticleSystem::initParticleSystem(double duration, double lifeTime, double lifeTimeVar, float speed, float speedVar, double emitAngle, double emitAngleVar, float gravityX, float gravityY){
    this->duration = duration;

	this->particlePerSec = this->totalParticleCount / this->duration;
    
    this->lifeTime = lifeTime;
    this->lifeTime = lifeTimeVar;
    
    this->speed = speed;
    this->speedVar = speedVar;
    
    this->emitAngle = emitAngle;
    this->emitAngleVar = emitAngleVar;
    
    this->gravityX = gravityX;
    this->gravityY = gravityY;
    
    srand((unsigned int)time(NULL));
    
    for(int i = 0; i<totalParticleCount; ++i){
        particleList.push_back(new Particle());
        particleList.back()->initParticle(
            position,
            computeRandom(lifeTime - lifeTimeVar, lifeTimeVar + lifeTimeVar),
            computeRandom(speed - speedVar, speed + speedVar),
            computeRandom(emitAngle - emitAngleVar/2, emitAngle + emitAngleVar/2)
                                          );
      
        vertexDistanceData.push_back(0);
        vertexDistanceData.push_back(0);
        vertexDistanceData.push_back(0);
        vertexDistanceData.push_back(1);
    }
    
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

void ParticleSystem::update(){
    //get time
	float elapsedTime = (float)Timer::getInstance().getElapsedTime();
	cout << "elapsed time = " << elapsedTime << endl;
    
    //add to total
	totalElapsedTime += elapsedTime;
    cout << "total elapsed time = " << totalElapsedTime << endl;
    
    int newParticleNumber = 0;
	float currentPoint = 0;

    //if particle system isn't dead yet
    if(totalElapsedTime < duration){
		currentPoint = this->particlePerSec * elapsedTime;
    }
    else{
        double remainingTime = elapsedTime - (totalElapsedTime - duration);
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
    totalCreatedParticles += newParticleNumber;
    
	if (newParticleNumber)
		cout << totalCreatedParticles << " particles created so far..." << endl;
    
    
    //iterate through particle lise
    //if particle list is empty, push back N particles at initial state
    //else, continue iterating
        //if lifetime is greater than 0, it's alive
            //subtract elapsed time
            //if particle is still alive, update position
                //update
            //else, this needs to die,
                //if (Ncounter < N)
                    //revive particle and reset to initial state
                //else
                    //remove from list
        //else, it's dead
            //if (Ncounter < N)
                //revive particle and reset to initial state
            //else
                //remove from list
    
    int index = 0;
//    liveCount = 0;
    
    for (std::list<Particle*>::const_iterator ci = particleList.begin(); ci != particleList.end(); ++ci) {
        if((*ci)->lifeTime > 0){
            //particle is alive
            (*ci)->lifeTime -= elapsedTime;
            if((*ci)->lifeTime > 0){
                double directionAngle = (*ci)->direction;
                float speed = (*ci)->speed;
//                cout << "angle = " << directionAngle << endl;
                float movedX = (float)cos(directionAngle * M_PI / 180) * elapsedTime * speed;
                float movedY = (float)sin(directionAngle * M_PI / 180) * elapsedTime * speed;
                
                //gravity
                float gAccelX = 9.8 * (float)totalElapsedTime * (gravityX / 3000);
                float gAccelY = 9.8 * (float)totalElapsedTime * (gravityY / 3000);
                
                vertexDistanceData.at(index) += (movedX + gAccelX);
                vertexDistanceData.at(index+1) += (movedY + gAccelY);
                vertexDistanceData.at(index+2) = 0; //z
                vertexDistanceData.at(index+3) = 1; //size
            }
            else{
                //dead. remove
            }
        }
        index+=4;
//        liveCount++;
    }
    
    //totalElapsedTime += elapsedTime;
    
    //update Data
    glBindBuffer(GL_ARRAY_BUFFER, vpbo);
    glBufferData(GL_ARRAY_BUFFER, totalParticleCount * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details. So clearing data?
//    glBufferSubData(GL_ARRAY_BUFFER, 0, liveCount * sizeof(GLfloat) * 4, &vertexDistanceData[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, totalParticleCount * sizeof(GLfloat) * 4, &vertexDistanceData[0]);
}

void ParticleSystem::render(){
    if(visible){
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
            throw std::runtime_error( std::string("Program uniform not found: " ) + "opacity");
        glUniform1i(particleUniformLocation, 1);
        
        glBindVertexArray(vao);
        glEnableVertexAttribArray(progPtr->attrib("vert"));
        glEnableVertexAttribArray(progPtr->attrib("uvVert"));
        glEnableVertexAttribArray(progPtr->attrib("posVert"));
        
        glVertexAttribDivisor(progPtr->attrib("vert"), 0);
        glVertexAttribDivisor(progPtr->attrib("uvVert"), 0);
        glVertexAttribDivisor(progPtr->attrib("posVert"), 1);
        
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, totalParticleCount);
    }
}

void ParticleSystem::setPosition(glm::vec2 position){
    this->position = position;
}