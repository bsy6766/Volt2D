//
//  Particle.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Particle.h"

Particle::Particle():
dead(false),
pos(glm::vec2()),
lifeTime(-1),
livedTime(0),
speed(0),
dirVec(glm::vec2()),
radialAccel(0),
tanAccel(0),
spawnedPosition(glm::vec2())
{
    
}

Particle::~Particle(){
    dead = true;
}