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
distance(glm::vec3()),
movedDistance(glm::vec3()),
previousDistance(glm::vec3())
{
    cout << "creating move by action" << endl;
}

ActionMoveBy::ActionMoveBy(const ActionMoveBy& other):ActionObject(other){
    this->distance = other.distance;
    this->movedDistance = other.movedDistance;
    this->previousDistance = other.previousDistance;
}

ActionMoveBy::~ActionMoveBy(){
    cout << "deleting move by action" << endl;
}

void ActionMoveBy::initMoveBy(glm::vec3 distance, double duration){
    this->distance = distance;
    this->duration = duration;
    this->actionID = ActionID::ACTION_MOVE_BY;
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
        if(distance.x == 0 && distance.y == 0 && distance.z == 0){
            movedDistance = distance;
            previousDistance = distance;
            return;
        }
        
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
    //confirm kill
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}