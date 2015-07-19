//
//  ActionRotateTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionRotateTo.h"

ActionRotateTo::ActionRotateTo():
ActionObject(),
startAngle(0),
destinationAngle(0),
movedAngle(0),
totalAngleToRotate(0){
    cout << "Creating action RotateBy" << endl;
}

ActionRotateTo::~ActionRotateTo(){
    cout << "Deleting action RotateBy" << endl;
}

ActionRotateTo* ActionRotateTo::createRotateTo(double duration, float angle){
    ActionRotateTo* newActionMoveTo = new ActionRotateTo();
    newActionMoveTo->initRotateTo(angle, duration);
    return newActionMoveTo;
}

void ActionRotateTo::initRotateTo(float angle, double duration){
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

    this->duration = duration;
    this->destinationAngle = angle * (-1);
    this->movedAngle = 0;
}

void ActionRotateTo::startAction(){
    ActionObject::startAction();
    startAngle = this->target->getAngle() * (-1);
    totalAngleToRotate = destinationAngle - startAngle;
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
    this->target->setAngle(movedAngle);
    alive = false;
}

void ActionRotateTo::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        movedAngle = totalAngleToRotate + startAngle;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(totalAngleToRotate == 0){
            movedAngle = totalAngleToRotate;
        }
        else{
            movedAngle = totalAngleToRotate * (currentTime / duration) + startAngle;
        }
    }
    this->target->setAngle(movedAngle);
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
    cloneRotateTo->initRotateTo(this->destinationAngle, this->duration);
    return cloneRotateTo;
}