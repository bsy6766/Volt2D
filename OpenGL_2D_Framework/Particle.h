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
    
    glm::vec2 position;
    double lifeTime;
    float speed;
    double direction;    //like angle
    
    void initParticle(glm::vec2 position, double lifeTime, float speed, double direction);
    void updatePosition();
};

#endif /* defined(__CS364FinalProject__Particle__) */
