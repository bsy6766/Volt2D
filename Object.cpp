//
//  Object.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Object.h"

Object::Object()
:size(Director::getInstance().getWindowSize()),
visible(true)
{
    position = glm::vec3(size.w/2, size.h/2, 0);
}

Object::~Object(){
    
}

void Object::setPosition(glm::vec3 position){
    this->position = position;
}

glm::vec3 Object::getPosition(){
    return this->position;
}

bool Object::isVisible(){
    return this->visible;
}