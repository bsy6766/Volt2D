//
//  ParticleSystemManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ParticleSystemManager.h"

using std::cout;
using std::endl;

ParticleSystemManager::ParticleSystemManager(){
    cout << "Creating Particle System Manager" << endl;
	this->size = 0;
	this->visible = true;
}

ParticleSystemManager::~ParticleSystemManager(){
    cout << "Deleting Particle System Manager" << endl;
    cout << "ParticleSystemManager: Deleting " << particleSystemList.size() << " remaining particle systems" << endl;
    
    //delete any remaining particle system
    for(std::list<ParticleSystem *>::const_iterator ci = particleSystemList.begin(); ci != particleSystemList.end(); ++ci){
        delete (*ci);
    }

	this->size = 0;
}

void ParticleSystemManager::render(){
	//if the list is empty, return
	if (size == 0)
		return;

	//if not visible, return
	if (!visible)
		return;

    //iterate through particle system list and render.
    //if particle system is in this list, then it means it's still alive.
    for(std::list<ParticleSystem *>::const_iterator ci = particleSystemList.begin(); ci != particleSystemList.end(); ++ci){
        (*ci)->render();
    }
}

void ParticleSystemManager::update(){
    //iterate through particle system list and update.
    //if particle system is dead, then remove from the list
    for(std::list<ParticleSystem *>::const_iterator ci = particleSystemList.begin(); ci != particleSystemList.end();){
        //for loop doesn't increment iterator. you must define it since this loop can erase element
        //if element(particle system) is daed
        if((*ci)->isDead()){
            //delete and remove from list
            delete (*ci);
            ci = particleSystemList.erase(ci);
        }
        else{
            //particle system is still alive. keep it and update.
            (*ci)->update();
            //increment iterator
            ++ci;
        }
    }
}

void ParticleSystemManager::addParticleSystem(ParticleSystem *particleSystemPtr){
    //check nullptr. if 0, return
    if(particleSystemPtr == 0)
        return;
    
    //add to list
    particleSystemList.push_back(particleSystemPtr);
}