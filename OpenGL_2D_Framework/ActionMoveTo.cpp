//
//  ActionMoveTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/5/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "ActionMoveTo.h"
#include <iostream>

using std::cout;
using std::endl;

ActionMoveTo::ActionMoveTo():SpriteAction(){
    cout << "creating MoveTo action" << endl;
}

ActionMoveTo::~ActionMoveTo(){
    cout << "deleting MoveTo action" << endl;
}

ActionMoveTo::ActionMoveTo(const ActionMoveTo& other){
    cout << "copying MoveTo action" << endl;
}

void ActionMoveTo::initMoveTo(glm::vec2 destination, double duration){
    this->duration = duration;
    this->destination = destination;
    this->actionID = ACTION_MOVE_TO;

    this->movedDistance = glm::vec2();
    this->previousPosition = glm::vec2();
    this->originalPosition = glm::vec2();
}

void ActionMoveTo::update(double elapsedTime, double unusedTime){
	//if elapsed time is -1, means instant update
    if(elapsedTime == -1){
        //instant
        movedDistance = destination - originalPosition;
        previousPosition = destination;
        //set action as dead and done
        alive = false;
        return;
    }
    
    float currentTime = (float)getCurrentTime() + (float)unusedTime;
    float prevTime = (float)getPreviousTime();
    
    glm::vec2 dist = destination - originalPosition;
    
    float prevX, prevY;
    float curX, curY;
    float diffX, diffY;
    
    float dur = (float)duration;
    
    prevX = prevTime * dist.x / dur;
    prevY = prevTime * dist.y / dur;
    
    if(duration == currentTime){
        //action is about to end. force sprite's position to destination
        diffX = destination.x - previousPosition.x;
        diffY = destination.y - previousPosition.y;
    }
    else{
        curX = speed * currentTime * dist.x / dur;
        curY = speed * currentTime * dist.y / dur;
        
        diffX = curX - prevX;
        diffY = curY - prevY;
    }
    
    previousPosition += glm::vec2(diffX, diffY);
    movedDistance = glm::vec2(diffX, diffY);
}

void ActionMoveTo::setOriginalPosition(glm::vec2 pos, bool fresh){
    //set original position
    originalPosition = pos;
    //if action is fresh, set previous position as well
    if(fresh){
        previousPosition = pos;
    }
}

glm::vec2 ActionMoveTo::getMovedDistance(){
    return movedDistance;
}

void ActionMoveTo::clone(SpriteAction* dataPtr){
    ActionMoveTo *other = static_cast<ActionMoveTo*>(dataPtr);
    
    SpriteAction::clone(dataPtr);
    
    this->actionID = other->actionID;
    
    this->destination = other->destination;
    this->movedDistance = other->movedDistance;
    this->previousPosition = other->previousPosition;
    this->originalPosition = other->originalPosition;
}

void ActionMoveTo::revive(){
    previousPosition = glm::vec2();
    movedDistance = glm::vec2();
    
    SpriteAction::revive();
}