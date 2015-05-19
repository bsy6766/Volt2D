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
movedDistance(glm::vec3()),
previousPosition(glm::vec3()),
originalPosition(glm::vec3()),
destination(glm::vec3()),
totalDistance(glm::vec3())
{
    cout << "creating MoveTo action" << endl;
}

ActionMoveTo::~ActionMoveTo(){
    cout << "deleting MoveTo action" << endl;
}

void ActionMoveTo::initMoveTo(glm::vec3 destination, double duration){
    this->duration = duration;
    this->destination = destination;
    this->actionID = ACTION_MOVE_TO;
}

void ActionMoveTo::instantUpdate(){
    movedDistance = destination - originalPosition;
    previousPosition = destination;
    alive = false;
}

void ActionMoveTo::intervalUpdate(double remainedTime){
    float duration = (float)this->duration;
    
    if(totalElapsedTime == duration){
        movedDistance = totalDistance - previousPosition;
        alive = false;
        return;
    }
    else{
        float currentTime = (float)(this->totalElapsedTime + remainedTime);
        glm::vec3 curDist = totalDistance * (currentTime / duration);
        glm::vec3 diff = curDist - previousPosition;
        movedDistance = diff;
        previousPosition += diff;
    }
    
    
//    float duration = (float)this->duration;
//    float currentTime = (float)(this->totalElapsedTime + remainedTime);
//    
//    glm::vec3 curDist = totalDistance * (currentTime / duration);
//    glm::vec3 diff = curDist - previousPosition;
//    
//    //    movedDistance = diff;
//    
//    if(totalElapsedTime == duration){
//        movedDistance = totalDistance - curDist;
//        alive = false;
//        return;
//    }
//    else{
//        movedDistance = diff;
//    }
//    
//    previousPosition += diff;
}

void ActionMoveTo::updateAction(double remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionMoveTo::setOriginalPosition(glm::vec3 pos, bool fresh){
    //set original position
    originalPosition = pos;
    //if action is fresh, set previous position as well
    if(fresh){
        previousPosition = pos;
    }
    
    totalDistance = destination - originalPosition;
}

glm::vec3 ActionMoveTo::getMovedDistance(){
    return movedDistance;
}

void ActionMoveTo::revive(){
    previousPosition = glm::vec3();
    movedDistance = glm::vec3();
    
    ActionObject::revive();
}