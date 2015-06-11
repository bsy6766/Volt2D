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

void ActionRotateTo::initRotateTo(float angle, float duration){
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
    
    cout << "Initializing RotateBy with angle: " << angle << " and duration: " << duration << endl;
    
    this->duration = duration;
    this->actionID = ACTION_ROTATE_TO;
    this->destinationAngle = angle;
    this->movedAngle = 0;
//    this->previousAngle = 0;
}

void ActionRotateTo::setOriginalAngle(float angle, bool fresh){
    startAngle = angle;
//    if(fresh)
//        previousAngle = angle;
    
    totalAngleToRotate = destinationAngle - startAngle;
    cout << "total angle to move = " << totalAngleToRotate << endl;
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
    movedAngle = totalAngleToRotate;
//    previousAngle = destinationAngle;
    alive = false;
}

void ActionRotateTo::intervalUpdate(double remainedTime){
    float duration = (float)this->duration;
    
    if(totalElapsedTime == duration){
        movedAngle = totalAngleToRotate + startAngle;
        alive = false;
        return;
    }
    else{
        float currentTime = (float)(this->totalElapsedTime + remainedTime);
        float curAngle = totalAngleToRotate * (currentTime / duration);
//        float diff = curAngle - previousAngle;
//        movedAngle = diff;
//        previousAngle += diff;
        movedAngle = curAngle + startAngle;
    }
}

float ActionRotateTo::getMovedAngle(){
    return movedAngle;
}

void ActionRotateTo::revive(){
    //revive. original and previous will be updated
//    this->previousAngle = 0;
    this->movedAngle = 0;
    
    this->alive = false;
    this->running = false;
    
    ActionObject::revive();
}