//
//  Particle.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__Particle__
#define __CS364FinalProject__Particle__

#include <glm/glm.hpp>

class Particle{
private:
public:
    //defualt
    Particle();
    ~Particle();
    
    bool dead;
    
    glm::vec2 positionData;
    double lifeTime;
	double livedTime;
    float speed;
    double direction;    //like angle
    
    void initParticle(glm::vec2 posData, double lifeTime, float speed, double direction);
    void updatePosition();

	void updateDistnace(float x, float y);
};

#endif /* defined(__CS364FinalProject__Particle__) */
