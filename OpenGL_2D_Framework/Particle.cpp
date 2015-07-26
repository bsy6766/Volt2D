//
//  Particle.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Particle.h"

Particle::Particle():
dead(false),
pos(glm::vec2()),
lifeTime(-1),
livedTime(0),
speed(0),
dirVec(glm::vec2()),
radialAccel(0),
tanAccel(0),
spawnedPosition(glm::vec2()),
startColor(Color::WHITE),
endColor(Color::WHITE),
colorDiff(glm::vec4())
{
}

Particle::~Particle(){
    dead = true;
}

Color Particle::getCurColor(){
//    colorDiff = endColor - startColor;
    double t = livedTime / lifeTime;
    glm::vec4 temp = this->colorDiff;
    temp.r *= t;
    temp.r += startColor.getR();
    temp.g *= t;
    temp.g += startColor.getG();
    temp.b *= t;
    temp.b += startColor.getB();
    temp.a *= t;
    temp.a += startColor.getA();
    return Color::createWithRGBA(temp.r, temp.g, temp.b, temp.a);
}

void Particle::setColor(Color start, Color end){
    this->startColor = start;
    this->endColor = end;
    this->colorDiff = end.getRGBA() - start.getRGBA();
}