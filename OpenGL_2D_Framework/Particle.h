//
//  Particle.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Particle__
#define __OpenGL_2D_Framework__Particle__

#include <glm/glm.hpp>

class Particle{
private:
public:
    //defualt
    Particle();
	//default with init
	Particle(glm::vec2 posData, double lifeTime, float speed, double direction);
	//destructor
    ~Particle();
    
	//true = dead
    bool dead;
    
	//position
    glm::vec2 positionData;

	//lifeTime = how long does it lives
    double lifeTime;
	//livedTime = how long did it live
	double livedTime;

	//speed of particle
    float speed;

	//in radian. Default angle is 90 degrees(north)
    double direction;    
    
	//initialize particle
    void initParticle(glm::vec2 posData, double lifeTime, float speed, double direction);

	//update current distance
	void updateDistnace(float x, float y);
};

#endif /* defined(__OpenGL_2D_Framework__Particle__) */
