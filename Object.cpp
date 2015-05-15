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
position(glm::vec3(0, 0, 0)),
visible(true)
{
    cout << "Object::Object()" << endl;
}

Object::~Object(){
    cout << "Object::~Object()" << endl;
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