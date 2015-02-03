//
//  Layer.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Layer__
#define __OpenGL_2D_Framework__Layer__

#include "Sprite.h"
#include "SpriteManager.h"
#include "ParticleSystem.h"
#include "ParticleSystemManager.h"

class Layer{
protected:
    int z;  //z depth. Used for layers only.
private:
    
public:
    Layer();                    //constructor
    Layer(const Layer& other);  //copy constructor
    
    /**
     *  Add sprite to the layer
     */
    void addSprite(Sprite* sprite);
    void addParticle(ParticleSystem* particleSystem);
};

#endif /* defined(__OpenGL_2D_Framework__Layer__) */
