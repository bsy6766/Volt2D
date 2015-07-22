//
//  ActionJumpTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionJumpTo.h"

ActionJumpTo::ActionJumpTo():
ActionObject()
{
    
}

ActionJumpTo::~ActionJumpTo(){
    
}

ActionJumpTo* ActionJumpTo::createJumpTo(double duration, glm::vec3 destination, float height){
    ActionJumpTo* newJumpTo = new ActionJumpTo();
    newJumpTo->initActionJumpTo(duration, destination, height);
    return newJumpTo;
}

void ActionJumpTo::initActionJumpTo(double duration, glm::vec3 dest, float h){
    this->duration = duration;
    this->height = h;
    this->destPos = dest;
}

void ActionJumpTo::startAction(){
    ActionObject::startAction();

}

void ActionJumpTo::updateAction(double &remainedTime){
    
}

void ActionJumpTo::revive(){
    ActionObject::revive();
}

ActionObject* ActionJumpTo::clone(){
    ActionJumpTo* cloneJumpTo = new ActionJumpTo();
    cloneJumpTo->initActionJumpTo(this->duration, this->destPos, this->height);
    return cloneJumpTo;
}