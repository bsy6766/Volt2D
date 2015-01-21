//
//  ParticleSystemManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ParticleSystemManager__
#define __OpenGL_2D_Framework__ParticleSystemManager__

#include "ParticleSystem.h"
#include <list>
#include <iostream>

class ParticleSystemManager{
protected:
private:
    std::list<ParticleSystem *> particleSystemList;
	int size;

public:
    ParticleSystemManager();
    ~ParticleSystemManager();
    
	//render particle system
    void render();

	//update and remove from list if it's dead
    void update();

	//add particle system on list
    void addParticleSystem(ParticleSystem *particleSystemPtr);
    
    bool visible;
};

#endif /* defined(__OpenGL_2D_Framework__ParticleSystemManager__) */
