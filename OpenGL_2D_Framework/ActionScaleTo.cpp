//
//  ActionScaleTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionScaleTo.h"

ActionScaleTo::ActionScaleTo():
ActionObject(),
destScale(glm::vec3()),
srcScale(glm::vec3()),
scaled(glm::vec3()),
totalScalingAmount(glm::vec3())
{
    cout << "Creating action scale to" << endl;
}

ActionScaleTo::ActionScaleTo(const ActionScaleTo& other):ActionObject(other){
    cout << "Copying action scale to" << endl;
    this->destScale = other.destScale;
    this->srcScale = other.srcScale;
    this->totalScalingAmount = other.totalScalingAmount;
    this->scaled = other.scaled;
}

ActionScaleTo::~ActionScaleTo(){
    cout << "Deleting action scale to" << endl;
}

void ActionScaleTo::initScaleTo(glm::vec3 scale, double duration){
    this->duration = duration;
    this->actionID = ACTION_SCALE_TO;
    this->destScale = scale;
    this->scaled = glm::vec3();
}

void ActionScaleTo::setCurrentScale(glm::vec3 scale){
    this->srcScale = scale;
    this->totalScalingAmount = this->destScale - scale;
}

glm::vec3 ActionScaleTo::getScaledScale(){
    return this->scaled;
}

void ActionScaleTo::instantUpdate(){
    scaled = totalScalingAmount;
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
        return;
    }
    else{
        remainedTime = 0;
        if(totalScalingAmount.x == 0 && totalScalingAmount.y == 0 && totalScalingAmount.z == 0){
            scaled = totalScalingAmount;
            return;
        }
        
        scaled = totalScalingAmount * (currentTime / duration) + srcScale;
    }
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