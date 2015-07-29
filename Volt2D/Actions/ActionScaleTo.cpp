//
//  ActionScaleTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionScaleTo.h"

using namespace Volt2D;

ActionScaleTo::ActionScaleTo():
ActionObject(),
destScale(glm::vec3()),
srcScale(glm::vec3()),
scaled(glm::vec3()),
totalScalingAmount(glm::vec3())
{
//    cout << "[SYSTEM::INFO] Creating ActionScaleTo" << endl;
}

ActionScaleTo::~ActionScaleTo(){
//    cout << "[SYSTEM::INFO] Releasing ActionScaleTo" << endl;
}

ActionScaleTo* ActionScaleTo::createScaleTo(double duration, glm::vec3 scale){
    ActionScaleTo* newScaleTo = new ActionScaleTo();
    newScaleTo->initScaleTo(scale, duration);
    return newScaleTo;
}

void ActionScaleTo::initScaleTo(glm::vec3 scale, double duration){
    this->duration = duration;
    this->destScale = scale;
    this->scaled = glm::vec3();
}

void ActionScaleTo::startAction(){
    ActionObject::startAction();
    glm::vec3 scale = this->target->getScale();
    this->srcScale = scale;
    this->totalScalingAmount = this->destScale - scale;
}

void ActionScaleTo::instantUpdate(){
    scaled = totalScalingAmount;
    this->target->setScale(scaled);
    alive = false;
}

void ActionScaleTo::intervalUpdate(double& remainedTime){
    //get time in float
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        scaled = totalScalingAmount + srcScale;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(totalScalingAmount.x == 0 && totalScalingAmount.y == 0 && totalScalingAmount.z == 0){
            scaled = totalScalingAmount;
        }
        else{
            scaled = totalScalingAmount * (currentTime / duration) + srcScale;
        }
    }
    this->target->setScale(scaled);
}

void ActionScaleTo::updateAction(double& remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionScaleTo::revive(){
    //revive. original and previous will be updated
    scaled = glm::vec3();
    
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}

ActionObject* ActionScaleTo::clone(){
    ActionScaleTo* cloneScaleTo = new ActionScaleTo();
    cloneScaleTo->initScaleTo(this->destScale, this->duration);
    return cloneScaleTo;
}