//
//  ParticleManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ParticleManager__
#define __OpenGL_2D_Framework__ParticleManager__

#include "Particle.h"

class ParticleManager{
protected:
private:
public:
    ParticleManager();
    ~ParticleManager();
    
    void render();
    void update();
    void addParticle();
    void deleteSprite();
    bool globalVisible;
};

#endif /* defined(__OpenGL_2D_Framework__ParticleManager__) */
