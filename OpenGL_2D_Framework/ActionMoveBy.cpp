//
//  ActionMoveBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionMoveBy.h"

ActionMoveBy::ActionMoveBy():
ActionObject(),
startingPos(glm::vec3()),
distance(glm::vec3()),
movedDistance(glm::vec3()),
previousDistance(glm::vec3())
{
    
}

ActionMoveBy::~ActionMoveBy(){
    
}

void ActionMoveBy::initMoveBy(glm::vec3 distance, double duration){
    this->distance = distance;
    this->duration = duration;
    this->actionID = ACTION_MOVE_BY;
}

void ActionMoveBy::setStartingPos(glm::vec3 pos){
    this->startingPos = pos;
//    this->previousDistance = pos;
}

glm::vec3 ActionMoveBy::getMovedDistance(){
    return this->movedDistance;
}

void ActionMoveBy::updateAction(double remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionMoveBy::instantUpdate(){
    movedDistance = distance;
    alive = false;
}

void ActionMoveBy::intervalUpdate(double remainedTime){
    float duration = (float)this->duration;
    
    if(totalElapsedTime == duration){
        movedDistance = distance - previousDistance;
        alive = false;
        return;
    }
    else{
        float currentTime = (float)(this->totalElapsedTime + remainedTime);
        glm::vec3 curDist = distance * (currentTime / duration);
        glm::vec3 diff = curDist - previousDistance;
        movedDistance = diff;
        previousDistance += diff;
    }
}

void ActionMoveBy::revive(){
    movedDistance = glm::vec3();
    previousDistance = glm::vec3();
    ActionObject::revive();
}