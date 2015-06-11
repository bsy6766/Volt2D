//
//  ActionRotateTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionRotateTo.h"

ActionRotateTo::ActionRotateTo(){
    cout << "Creating action RotateBy" << endl;
}

ActionRotateTo::~ActionRotateTo(){
    cout << "Deleting action RotateBy" << endl;
}

void ActionRotateTo::initRotateBy(float angle, float duration){
    cout << "Initializing RotateBy with angle: " << angle << " and duration: " << duration << endl;
    this->duration = duration;
    this->actionID = ACTION_ROTATE_BY;
    
    this->rotatingAngle = angle;
    this->movedAngle = 0;
    this->previousAngle = 0;
}

void ActionRotateTo::setOriginalAngle(float angle, bool fresh){
    startAngle = angle;
    if(fresh)
        previousAngle = angle;
}

void ActionRotateTo::updateAction(double remainedTime){
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
    movedAngle = rotatingAngle;
    alive = false;
}

void ActionRotateTo::intervalUpdate(double remainedTime){
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

float ActionRotateTo::getMovedAngle(){
    return movedAngle;
}

void ActionRotateTo::revive(){
    //revive. original and previous will be updated
    this->previousAngle = 0;
    this->movedAngle = 0;
    
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}