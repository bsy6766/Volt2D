//
//  Particle.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Particle__
#define __OpenGL_2D_Framework__Particle__

#include "CommonInclude.hpp"
#include "Color.h"

class Particle{
private:
    /**
     * Color
     */
    Color startColor;
    Color endColor;
    glm::vec4 colorDiff;
public:
    //defualt
    Particle();
    
    //Destructor
    ~Particle();
    
    /**
     *
     */
    Color getCurColor();
    
    /**
     *  Particle's life. True if dead
     */
    bool dead;
    
    /**
     *  Current position of particle in the world
     */
    glm::vec2 pos;
    
    /**
     *  Position where particle spawned
     */
    glm::vec2 spawnedPosition;

    /**
     *  Particle's total life time (life span)
     */
    double lifeTime;

    /**
     *  Total time that particle lived
     */
	double livedTime;

    /**
     *  Speed of particle
     *  @deprecated
     */
    float speed;

    /**
     *  Direction vector.
     */
    glm::vec2 dirVec;
    
    /**
     *  Radial acceleration. Power of pulling particle back to spawn point
     */
    float radialAccel;
    
    /**
     *  Tangential acceleration. Power applies perpenticullar to particle's direction
     */
    float tanAccel;
    
    void setColor(Color start, Color end);
};

#endif /* defined(__OpenGL_2D_Framework__Particle__) */
