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
    cout << "Creating ACTION_DELAY" << endl;
}

ActionDelay::~ActionDelay(){
    cout << "Deleting ACTION_DELAY" << endl;
}

ActionDelay::ActionDelay(const ActionDelay& other):ActionObject(other){
    cout << "copying ACTION_DELAY" << endl;
    this->totalDelayed = other.totalDelayed;
    this->delayTick = other.delayTick;
}

void ActionDelay::initDelay(double duration){
    this->duration = duration;
    this->actionID = ACTION_DELAY;
//    this->type = ActionType::ACTION_DELAY;
    
    this->totalDelayed = 0;
    this->delayTick = 0;
}

void ActionDelay::instantUpdate(){
    totalDelayed = duration;
    alive = false;
}

void ActionDelay::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    //currentTime will be total elapsed time (+ remained time)
    float currentTime = (float)this->totalElapsedTime + remainedTime;
    
    //if total elapsed time is equal(remainedTime == 0) or greater than(remainedTime >0) than duration,
    if(currentTime >= duration){
        //Delay ended
        delayTick = duration - totalDelayed;
        totalDelayed = duration;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        delayTick = (currentTime - this->previousTime);
        totalDelayed += delayTick;
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
    this->delayTick = 0;
    this->totalDelayed = 0;
    
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}