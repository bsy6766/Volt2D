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

/**
*	Layer class
*	Base class of each layers
*	Layers must be created by individually. unable to copy or assgin it. 
*	Can add up to 5 layers to single Scene.
*/

class Layer{
protected:
    int z;  //z depth. Used for layers only.
private:
    
public:
    Layer(int z);                    //constructor
    Layer(const Layer& other);  //copy constructor. not implementing. can't copy layer
	void operator=(const Layer& other);	//assignment operator. not implementing. can't assign layer
	~Layer();
    
    /**
     *  Add sprite to the layer
     */
    void addSprite(Sprite* sprite);
    void addParticle(ParticleSystem* particleSystem);
	int getZ();
};

#endif /* defined(__OpenGL_2D_Framework__Layer__) */
