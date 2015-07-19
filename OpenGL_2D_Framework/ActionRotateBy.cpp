//
//  ActionRotateBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/8/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionRotateBy.h"

ActionRotateBy::ActionRotateBy():
ActionObject(),
rotatingAngle(0),
previousAngle(0),
movedAngle(0){
    cout << "Creating action RotateBy" << endl;
}

ActionRotateBy::~ActionRotateBy(){
    cout << "Deleting action RotateBy" << endl;
}

ActionRotateBy* ActionRotateBy::createRotateBy(double duration, float angle){
    ActionRotateBy* newActionMoveBy = new ActionRotateBy();
    newActionMoveBy->initRotateBy(angle, duration);
    return newActionMoveBy;
}

void ActionRotateBy::initRotateBy(float angle, double duration){
    this->duration = duration;
    this->rotatingAngle = angle;
    this->movedAngle = 0;
    this->previousAngle = 0;
}

void ActionRotateBy::updateAction(double& remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionRotateBy::instantUpdate(){
    movedAngle = rotatingAngle;
    this->target->addAngle(rotatingAngle);
    alive = false;
}

void ActionRotateBy::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        movedAngle = rotatingAngle - previousAngle;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(rotatingAngle == 0){
            movedAngle = rotatingAngle;
            previousAngle = rotatingAngle;
        }
        else{
            float diff = (rotatingAngle * (currentTime / duration)) - previousAngle;
            movedAngle = diff;
            previousAngle += diff;
        }
    }
    this->target->addAngle(movedAngle);
}

void ActionRotateBy::revive(){
    //revive. original and previous will be updated
    this->previousAngle = 0;
    this->movedAngle = 0;
    //make sure you kill it
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}

ActionObject* ActionRotateBy::clone(){
    ActionRotateBy* cloneRotateBy = new ActionRotateBy();
    cloneRotateBy->initRotateBy(this->rotatingAngle, this->duration);
    return cloneRotateBy;
}