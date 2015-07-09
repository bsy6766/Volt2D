//
//  ActionRotateBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/8/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionRotateBy.h"

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
    this->previousAngle = 0;
}

void ActionRotateBy::setOriginalAngle(float angle, bool fresh){
    startAngle = angle;
    if(fresh)
        previousAngle = angle;
}

void ActionRotateBy::updateAction(double remainedTime){
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
    alive = false;
}

void ActionRotateBy::intervalUpdate(double remainedTime){
    float duration = (float)this->duration;
    
    if(totalElapsedTime == duration){
        movedAngle = rotatingAngle - previousAngle;
        alive = false;
        return;
    }
    else{
        float currentTime = (float)(this->totalElapsedTime + remainedTime);
        float curAngle = rotatingAngle * (currentTime / duration);
        float diff = curAngle - previousAngle;
        movedAngle = diff;
        previousAngle += diff;
//        cout << "Duration = " << this->duration << endl;
//        cout << "total elapsed time = " << this->totalElapsedTime << endl;
//        cout << "movedAngle = " << movedAngle << endl;
//        cout << "previousAngle = " << previousAngle << endl;
    }
}

float ActionRotateBy::getMovedAngle(){
    return movedAngle;
}

void ActionRotateBy::revive(){
    //revive. original and previous will be updated
    this->previousAngle = 0;
    this->movedAngle = 0;
    
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}