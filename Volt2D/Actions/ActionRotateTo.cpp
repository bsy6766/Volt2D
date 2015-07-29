//
//  ActionRotateTo.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionRotateTo.h"

using namespace Volt2D;

ActionRotateTo::ActionRotateTo():
ActionObject(),
type(RotationType::RIGHT),
startAngle(0),
destinationAngle(0),
movedAngle(0),
totalAngleToRotate(0)
{
//    cout << "[SYSTEM::INFO] Creating ActionRotateTo" << endl;
}

ActionRotateTo::~ActionRotateTo(){
//    cout << "[SYSTEM::INFO] Releasing ActionRotateTo" << endl;
}

ActionRotateTo* ActionRotateTo::createRotateTo(double duration, float angle, RotationType type){
    ActionRotateTo* newActionMoveTo = new ActionRotateTo();
    newActionMoveTo->initRotateTo(angle, duration, type);
    return newActionMoveTo;
}

void ActionRotateTo::initRotateTo(float angle, double duration, RotationType type){
    //wrap angle
    if(angle >= 360){
        while(angle >= 360){
            angle -= 360.0;
        }
    }
    else if(angle < 0){
        while(angle < 0){
            angle += 360;
        }
    }
    
    //Right by default
    this->type = type;
    //init variables
    this->duration = duration;
    this->destinationAngle = angle;
    this->movedAngle = 0;
}

void ActionRotateTo::startAction(){
    ActionObject::startAction();
    startAngle = this->target->getAngle();
    if(this->type == RotationType::RIGHT){
        if(destinationAngle < startAngle)
            totalAngleToRotate = 360 - std::abs(destinationAngle - startAngle);
        else
            totalAngleToRotate = destinationAngle - startAngle;
    }
    else if(this->type == RotationType::LEFT){
        if(destinationAngle < startAngle)
            totalAngleToRotate = std::abs(destinationAngle - startAngle);
        else
            totalAngleToRotate = 360 - std::abs(destinationAngle - startAngle);
    }
}

void ActionRotateTo::updateAction(double& remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionRotateTo::instantUpdate(){
    movedAngle = totalAngleToRotate;
    if(this->type == RotationType::RIGHT)
        this->target->setAngle(movedAngle);
    else if(this->type == RotationType::LEFT)
        this->target->setAngle(-movedAngle);
    alive = false;
}

void ActionRotateTo::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        if(this->type == RotationType::RIGHT)
            movedAngle = totalAngleToRotate + startAngle;
        else if(this->type == RotationType::LEFT)
            movedAngle = startAngle - totalAngleToRotate;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(totalAngleToRotate == 0){
            //nothing to update
            movedAngle = totalAngleToRotate;
            return;
        }
        else{
            if(this->type == RotationType::RIGHT)
                movedAngle = totalAngleToRotate * (currentTime / duration) + startAngle;
            else if(this->type == RotationType::LEFT)
                movedAngle = startAngle - totalAngleToRotate * (currentTime / duration);
        }
    }
//    cout << "moved angle = " << movedAngle << endl;
    this->target->setAngle(movedAngle);
//    float curAngle = this->target->getAngle();
//    cout << "target angle = " << curAngle << endl;
}

void ActionRotateTo::revive(){
    this->movedAngle = 0;
    //make sure you kill it
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}

ActionObject* ActionRotateTo::clone(){
    ActionRotateTo* cloneRotateTo = new ActionRotateTo();
    cloneRotateTo->initRotateTo(this->destinationAngle, this->duration, this->type);
    return cloneRotateTo;
}