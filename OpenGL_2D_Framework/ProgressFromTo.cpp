//
//  ProgressFromTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ProgressFromTo.h"

ProgressFromTo::ProgressFromTo():
ActionObject(),
from(0),
to(0),
totalPercentage(0),
previousPercentage(0),
changedPercentage(0)
{
    
}

ProgressFromTo::ProgressFromTo(const ProgressFromTo& other):ActionObject(other){
    this->from = other.from;
    this->to = other.to;
    this->totalPercentage = other.totalPercentage;
    this->changedPercentage = other.changedPercentage;
    this->previousPercentage = other.previousPercentage;
}

ProgressFromTo::~ProgressFromTo(){
    
}

void ProgressFromTo::initProgressFromTo(int from, int to, float duration){
    this->from = from;
    this->to = to;
    this->totalPercentage = to - from;
    this->duration = duration;
}

void ProgressFromTo::startAction(){
    //check if target can be casted to progressObject;
    //at this point, we don't know if target is Sprite, Text or something else.
    //I'm using dynamic cast because of that. May be I should add handler on adding action
    //at the first time.
    if(dynamic_cast<ProgressObject*>(this->target) != nullptr){
        //the target is progress object. proceed
        ActionObject::startAction();
        static_cast<ProgressObject*>(this->target)->setPercentage(this->from);
    }
    else{
        //the target isn't
        this->alive = false;
    }
}

void ProgressFromTo::instantUpdate(){
//    this->target->
    //need to cast to
    alive = false;
}

void ProgressFromTo::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        changedPercentage = totalPercentage - previousPercentage;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(totalPercentage == 0){
            changedPercentage = 0;
            previousPercentage = 0;
        }
        else{
            int diff = (totalPercentage * (currentTime / duration)) - previousPercentage;
            changedPercentage = diff;
            previousPercentage += diff;
        }
    }
    static_cast<ProgressObject*>(this->target)->addPercentage(changedPercentage);
    cout << "cur % = " << static_cast<ProgressObject*>(this->target)->getPercentage() << endl;
}

void ProgressFromTo::updateAction(double& remainedTime){
    //good point checking if action is alive at this moment.
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ProgressFromTo::revive(){
    //revive. original and previous will be updated
    this->previousPercentage = 0;
    
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}