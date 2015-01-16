//
//  ActionJumpBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/6/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "ActionJumpBy.h"

#include <iostream>
#include <math.h>

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

void ActionJumpBy::clone(SpriteAction* dataPtr){
    std::cout << "Cloning action jump by" << std::endl;
    ActionJumpBy *other = static_cast<ActionJumpBy*>(dataPtr);
    
    SpriteAction::clone(dataPtr);
    
    this->actionID = other->actionID;
    
    this->distance = other->distance;
    this->jumpingPosition = other->jumpingPosition;
    this->previousPosition = other->previousPosition;
    this->movedDistance = other->movedDistance;
}

void ActionJumpBy::update(double elapsedTime, double unusedTime){
    if(elapsedTime == -1){
        movedDistance += distance;
        alive = false;
        return;
    }
    
    float duration = (float)getDuration();
    float currentTime = (float)getCurrentTime();
    float time = (float)getElapsedTime() + (float)unusedTime;
    
    //    float ratio = sin(3*currentTime) / 6;
    float distX, distY;
    
    if(currentTime >= duration){
        
    }
    else{
        distY = distance.y / 5 * sin(currentTime * 1.9 / duration * M_PI);
        distX = distance.x * time / duration;
        movedDistance = glm::vec2(distX, distY);
    }
}