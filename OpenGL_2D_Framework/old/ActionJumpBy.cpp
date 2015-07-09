//
//  ActionJumpBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/6/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionJumpBy.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


using std::cout;
using std::endl;

ActionJumpBy::ActionJumpBy(){
    cout << "Creating action jump by" << endl;
}

ActionJumpBy::~ActionJumpBy(){
    cout << "Deleting action jump by" << endl;
}

void ActionJumpBy::initJumpBy(glm::vec2 distance, double duration){
    this->duration = duration;
    this->actionID = ACTION_JUMP_BY;
    
    this->distance = distance;
    this->jumpingPosition = glm::vec2();
    this->movedDistance = glm::vec2();
}

void ActionJumpBy::setJumpingPosition(glm::vec2 jumpingPosition, bool fresh){
    this->jumpingPosition = jumpingPosition;
    if(fresh)
        previousPosition = jumpingPosition;
}

glm::vec2& ActionJumpBy::getDistance(){
    return distance;
}

glm::vec2& ActionJumpBy::getMovedDistance(){
    return movedDistance;
}

void ActionJumpBy::instantUpdate(){
    movedDistance += distance;
    alive = false;
}

void ActionJumpBy::update(double elapsedTime, double unusedTime){
    float duration = (float)getDuration();
    float currentTime = (float)getTotalElapsedTime();
    float time = (float)getElapsedTime() + (float)unusedTime;
    
    //    float ratio = sin(3*currentTime) / 6;
    float distX, distY;
    
    if(currentTime >= duration){
        //todo. implement
    }
    else{
        distY = distance.y / 5 * sin(currentTime * 1.9 / duration * M_PI);
        distX = distance.x * time / duration;
        movedDistance = glm::vec2(distX, distY);
    }
}