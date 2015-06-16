//
//  ActionMoveTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/5/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionMoveTo.h"

ActionMoveTo::ActionMoveTo():
ActionObject(),
movedPosition(glm::vec3()),
originalPosition(glm::vec3()),
destination(glm::vec3()),
totalDistance(glm::vec3())
{
    cout << "creating MoveTo action" << endl;
}

ActionMoveTo::ActionMoveTo(const ActionMoveTo& other):ActionObject(other){
    this->destination = other.destination;
    this->originalPosition = other.originalPosition;
    this->movedPosition = other.movedPosition;
    this->totalDistance = other.totalDistance;
}

ActionMoveTo::~ActionMoveTo(){
    cout << "deleting MoveTo action" << endl;
}

void ActionMoveTo::initMoveTo(glm::vec3 destination, double duration){
    this->duration = duration;
    this->destination = destination;
    this->actionID = ActionID::ACTION_MOVE_TO;
}

void ActionMoveTo::instantUpdate(){
    movedPosition = totalDistance;
    alive = false;
}

void ActionMoveTo::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        movedPosition = destination;
        alive = false;
        remainedTime = currentTime - duration;
        return;
    }
    else{
        //Still running action. remained time is consumed here
        remainedTime = 0;
        
        //if total distance is 0, there's nothing to do
        if(totalDistance.x == 0 && totalDistance.y == 0 && totalDistance.z == 0){
            movedPosition = destination;
            return;
        }
        
        movedPosition = totalDistance * (currentTime / duration) + originalPosition;
    }
}

void ActionMoveTo::updateAction(double& remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionMoveTo::setCurrentPos(glm::vec3 pos){
    originalPosition = pos;
    totalDistance = destination - originalPosition;
}

glm::vec3 ActionMoveTo::getMovedPosition(){
    return movedPosition;
}

void ActionMoveTo::revive(){
    movedPosition = glm::vec3();
    //confirm kill
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}