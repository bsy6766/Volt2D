//
//  Particle.h
//  Volt2D
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Particle__
#define __Volt2D__Particle__

#include "Utility.hpp"
#include "Color.h"

namespace Volt2D{
class Particle{
private:
    /**
     * Colors
     */
    Color startColor;
    Color endColor;
    glm::vec4 colorDiff;
    
    /**
     *  Sizes
     */
    float startSize;
    float endSize;
    float sizeDiff;
    
    /**
     *  Angles
     */
    float startAngle;
    float endAngle;
    float angleDiff;
    
public:
    //defualt
    Particle();
    
    //Destructor
    ~Particle();
    
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
    
    /**
     *  Size getter & setter
     */
    float getCurSize();
    void setSize(float start, float end);
    
    /**
     *  Angle getter & setter
     */
    float getCurAngle();
    void setAngle(float start, float end);
    
    /**
     *  Color getter & setter
     */
    Color getCurColor();
    void setColor(Color start, Color end);
};
}

#endif /* defined(__Volt2D__Particle__) */
