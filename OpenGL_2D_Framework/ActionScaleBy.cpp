//
//  ActionScaleBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/19/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionScaleBy.h"

ActionScaleBy::ActionScaleBy():
ActionObject(),
totalScalingAmount(0),
prevScale(0),
scaled(0)
{
    cout << "Creating action scale by" << endl;
}

ActionScaleBy::~ActionScaleBy(){
    cout << "Deleting action scale by" << endl;
}

ActionScaleBy* ActionScaleBy::createScaleBy(double duration, glm::vec3 scale){
    ActionScaleBy* newScaleBy = new ActionScaleBy();
    newScaleBy->initScaleBy(scale, duration);
    return newScaleBy;
}

void ActionScaleBy::initScaleBy(glm::vec3 scale, double duration){
    this->duration = duration;
    this->totalScalingAmount = scale;
    this->prevScale = glm::vec3();
    this->scaled = glm::vec3();
}

void ActionScaleBy::instantUpdate(){
    scaled = totalScalingAmount;
    this->target->addScale(scaled);
    alive = false;
}

void ActionScaleBy::intervalUpdate(double& remainedTime){
    //get time in float
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        scaled = totalScalingAmount - prevScale;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(totalScalingAmount.x == 0 && totalScalingAmount.y == 0 && totalScalingAmount.z == 0){
            scaled = totalScalingAmount;
            prevScale = totalScalingAmount;
        }
        else{
            glm::vec3 diff = (totalScalingAmount * (currentTime / duration)) - prevScale;
            scaled = diff;
            prevScale += diff;
        }
    }
    this->target->addScale(scaled);
}

void ActionScaleBy::updateAction(double& remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionScaleBy::revive(){
    //revive. original and previous will be updated
    prevScale = glm::vec3();
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}

ActionObject* ActionScaleBy::clone(){
    ActionScaleBy* cloneScaleBy = new ActionScaleBy();
    cloneScaleBy->initScaleBy(this->totalScalingAmount, this->duration);
    return cloneScaleBy;
}