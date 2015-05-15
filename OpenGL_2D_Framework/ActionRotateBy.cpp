//
//  ActionRotateBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/8/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionRotateBy.h"

#include <iostream>

using std::cout;
using std::endl;

ActionRotateBy::ActionRotateBy(){
    cout << "Creating action RotateBy" << endl;
}

ActionRotateBy::~ActionRotateBy(){
    cout << "Deleting action RotateBy" << endl;
}

void ActionRotateBy::initRotateBy(float angle, float duration){
    cout << "Initializing RotateBy with angle: " << angle << " and duration: " << duration << endl;
    this->duration = duration;
    this->actionID = ACTION_ROTATE_BY;
    
    this->rotatingAngle = angle;
    this->movedAngle = 0;
}

void ActionRotateBy::setOriginalAngle(float angle, bool fresh){
    startAngle = angle;
    if(fresh)
        previousAngle = angle;
}

float ActionRotateBy::getMovedAngle(){
    return movedAngle;
}

void ActionRotateBy::instantUpdate(){
    movedAngle = rotatingAngle - previousAngle;
    alive = false;
}

void ActionRotateBy::update(double elapsedTime, double unusedtime){
    float duration = (float)getDuration();
    float currentTime = (float)getTotalElapsedTime();
    float time = (float)getElapsedTime() + (float)unusedTime;
    
    if(currentTime >= duration){
        movedAngle = rotatingAngle - previousAngle;
        cout << "RotateBy action done." << endl;
    }
    else{
        movedAngle = time * rotatingAngle / duration;
        previousAngle += movedAngle;
    }
}

void ActionRotateBy::clone(ActionObject* dataPtr){
    std::cout << "Cloning action rotate by " << std::endl;
    
    ActionRotateBy *other = static_cast<ActionRotateBy*>(dataPtr);
    this->startAngle = other->startAngle;
    this->rotatingAngle = other->rotatingAngle;
    this->previousAngle = other->previousAngle;
    this->movedAngle = other->movedAngle;
    
    ActionObject::clone(dataPtr);
}

//revive
void ActionRotateBy::revive(){
    //revive. original and previous will be updated
    this->previousAngle = 0;
    this->movedAngle = 0;
    
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}