//
//  ActionDelay.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionDelay.h"

ActionDelay::ActionDelay():
ActionObject()
{
//    cout << "[SYSTEM::INFO] Creating ActionDelay" << endl;
}

ActionDelay::~ActionDelay(){
//    cout << "[SYSTEM::INFO] Releasing ActionDelay" << endl;
}

void ActionDelay::initDelay(double duration){
    this->duration = duration;
}

ActionDelay* ActionDelay::createDelay(double duration){
    ActionDelay* newDelayAction = new ActionDelay();
    newDelayAction->initDelay(duration);
    return newDelayAction;
}

void ActionDelay::instantUpdate(){
    alive = false;
}

void ActionDelay::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    //currentTime will be total elapsed time (+ remained time)
    float totalDelayTime = (float)this->totalElapsedTime + remainedTime;
    
    //if total elapsed time is equal(remainedTime == 0) or greater than(remainedTime >0) than duration,
    if(totalDelayTime >= duration){
        alive = false;
        remainedTime = totalDelayTime - duration;
    }
    else{
        remainedTime = 0;
    }
}

void ActionDelay::updateAction(double& remainedTime){
    if(!alive)
        return;
    
    //delay doesn't need any update for initial state of action
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionDelay::revive(){
    //revive. original and previous will be updated
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}

ActionObject* ActionDelay::clone(){
    ActionDelay* cloneDelay = new ActionDelay();
    cloneDelay->initDelay(this->duration);
    return cloneDelay;
}