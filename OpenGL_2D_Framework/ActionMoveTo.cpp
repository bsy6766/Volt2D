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
//
//    this->movedDistance = glm::vec3();
//    this->previousPosition = glm::vec3();
//    this->originalPosition = glm::vec3();
    
//    this->totalDistance = destination - ori
}

void ActionMoveTo::instantUpdate(){
    movedDistance = destination - originalPosition;
    previousPosition = destination;
    alive = false;
}

void ActionMoveTo::intervalUpdate(double remainedTime){
    //cast to float
    float duration = (float)this->duration;
    float currentTime = (float)this->totalElapsedTime + remainedTime;
    float elapsedTime = (float)this->elapsedTime;
    float timeRatio = elapsedTime / duration;
    
    
    movedDistance = totalDistance * timeRatio;
    if(totalElapsedTime == duration){
        alive = false;
    }
    //if action is done, get remaining distance between destination and prev pos
//    if(totalElapsedTime == duration){
//        glm::vec3 diff = destination - previousPosition;
//        movedDistance += diff;
//    }
//    //else, get distance moved on current iteration
//    else{
//        glm::vec3 moved = totalDistance * timeRatio;
//        previousPosition += moved;
//        movedDistance += moved;
//    }
    
    //    float currentTime = (float)getTotalElapsedTime() + (float)unusedTime;
    //    float prevTime = (float)getPreviousTime();
    //
    //    glm::vec2 dist = destination - originalPosition;
    //
    //    float prevX, prevY;
    //    float curX, curY;
    //    float diffX, diffY;
    //
    //    float dur = (float)duration;
    //
    //    float ratioX = dist.x / dur;
    //    float ratioY = dist.y / dur;
    //
    //    prevX = prevTime * ratioX;
    //    prevY = prevTime * ratioY;
    //
    //    if(duration == currentTime){
    //        //action is about to end. force sprite's position to destination
    //        diffX = destination.x - previousPosition.x;
    //        diffY = destination.y - previousPosition.y;
    //    }
    //    else{
    //        curX = currentTime * dist.x / dur;
    //        curY = currentTime * dist.y / dur;
    //
    //        diffX = curX - prevX;
    //        diffY = curY - prevY;
    //    }
    //    
    //    previousPosition += glm::vec2(diffX, diffY);
    //    movedDistance = glm::vec2(diffX, diffY);
}

void ActionMoveTo::updateAction(double remainedTime){
    if(!alive)
        return;
    
    //delay doesn't need any update for initial state of action
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

//void ActionMoveTo::update(double elapsedTime, double unusedTime){
//    float currentTime = (float)getTotalElapsedTime() + (float)unusedTime;
//    float prevTime = (float)getPreviousTime();
//    
//    glm::vec2 dist = destination - originalPosition;
//    
//    float prevX, prevY;
//    float curX, curY;
//    float diffX, diffY;
//    
//    float dur = (float)duration;
//    
//    float ratioX = dist.x / dur;
//    float ratioY = dist.y / dur;
//    
//    prevX = prevTime * ratioX;
//    prevY = prevTime * ratioY;
//    
//    if(duration == currentTime){
//        //action is about to end. force sprite's position to destination
//        diffX = destination.x - previousPosition.x;
//        diffY = destination.y - previousPosition.y;
//    }
//    else{
//        curX = currentTime * dist.x / dur;
//        curY = currentTime * dist.y / dur;
//        
//        diffX = curX - prevX;
//        diffY = curY - prevY;
//    }
//    
//    previousPosition += glm::vec2(diffX, diffY);
//    movedDistance = glm::vec2(diffX, diffY);
//}

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