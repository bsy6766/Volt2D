//
//  ActionMoveTo.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 12/5/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionMoveTo.h"

using namespace Volt2D;

ActionMoveTo::ActionMoveTo():
ActionObject(),
movedPosition(glm::vec3()),
originalPosition(glm::vec3()),
destination(glm::vec3()),
totalDistance(glm::vec3())
{
//    cout << "[SYSTEM::INFO] Creating ActionMoveTo" << endl;
}

ActionMoveTo::~ActionMoveTo(){
//    cout << "[SYSTEM::INFO] Releasing ActionMoveBy" << endl;
}

ActionMoveTo* ActionMoveTo::createMoveTo(double duration, glm::vec3 distance){
    ActionMoveTo* newActionMoveTo = new ActionMoveTo();
    newActionMoveTo->initMoveTo(distance, duration);
    return newActionMoveTo;
}

void ActionMoveTo::initMoveTo(glm::vec3 destination, double duration){
    this->duration = duration;
    this->destination = destination;
}

void ActionMoveTo::startAction(){
    ActionObject::startAction();
    //initialize position of sprite when action starts
    originalPosition = this->target->getPosition();
    totalDistance = destination - originalPosition;
}

void ActionMoveTo::instantUpdate(){
    movedPosition = totalDistance;
    this->target->setPosition(movedPosition);
    alive = false;
}

void ActionMoveTo::intervalUpdate(double& remainedTime){
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        movedPosition = destination;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        //Still running action. remained time is consumed here
        remainedTime = 0;
        
        //if total distance is 0, there's nothing to do
        if(totalDistance.x == 0 && totalDistance.y == 0 && totalDistance.z == 0){
            movedPosition = destination;
        }
        else{
            movedPosition = totalDistance * (currentTime / duration) + originalPosition;
        }
    }
    this->target->setPosition(movedPosition);
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

void ActionMoveTo::revive(){
    movedPosition = glm::vec3();
    //confirm kill
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}

ActionObject* ActionMoveTo::clone(){
    ActionMoveTo* cloneMoveTo = new ActionMoveTo;
    cloneMoveTo->initMoveTo(this->destination, this->duration);
    return cloneMoveTo;
}