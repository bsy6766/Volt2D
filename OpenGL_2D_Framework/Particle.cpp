//
//  Particle.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "Particle.h"

Particle::Particle(){
    dead = false;
}

Particle::~Particle(){
    dead = true;
}

void Particle::initParticle(glm::vec2 posData, double lifeTime, float speed, double direction){
    this->positionData = posData;
    this->lifeTime = lifeTime;
	this->livedTime = 0;
    this->speed = speed;
	this->direction = direction;
}

void Particle::updateDistnace(float x, float y){
	positionData.x = x;
	positionData.y = y;
}