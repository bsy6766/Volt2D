//
//  Color.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Color.h"

const Color Color::WHITE = Color(255, 255, 255, 1);
const Color Color::RED = Color(255, 0, 0, 1);

Color::Color(float r, float g, float b, float a)
{
    setR(r);
    setG(g);
    setB(b);
    setA(a);
}

void Color::wrapColorBoundary(float &color){
    if(color > 255.0)
        color = 255;
    else if(color < 0)
        color = 0;
}

void Color::setR(float r){
    wrapColorBoundary(r);
    this->r = r;
}

void Color::setG(float g){
    wrapColorBoundary(g);
    this->g = g;
}

void Color::setB(float b){
    wrapColorBoundary(b);
    this->b = b;
}

void Color::setA(float a){
    if(a < 0)
        a = 0;
    else if(a>1.0)
        a = 1;
    this->a = a;
}

glm::vec3 Color::getColor(){
    return glm::vec3(r,g,b);
}

float Color::getA(){
    return this->a;
}

float Color::getR(){
    return this->r;
}

float Color::getG(){
    return this->g;
}

float Color::getB(){
    return this->b;
}