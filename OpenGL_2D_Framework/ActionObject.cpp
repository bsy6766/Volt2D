//
//  ActionObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionObject.h"

unsigned int ActionObject::ACTION_ID = 0;

ActionObject::ActionObject():
running(false),
alive(true),
previousTime(0),
isProtected(false),
totalElapsedTime(0),
unusedTime(0),
speed(1),
duration(-1),
remainedTimeByDeath(0)
{
    std::cout << "ActionObject()" << std::endl;
    ACTION_ID++;
    objID = ACTION_ID;
}

ActionObject::~ActionObject(){
    std::cout << "~ActionObject()" << std::endl;
}

ActionID ActionObject::getActionID(){
    return actionID;
}

double ActionObject::getTotalElapsedTime(){
    return totalElapsedTime;
}

double ActionObject::getPreviousTime(){
    return previousTime;
}

double ActionObject::getElapsedTime(){
    return totalElapsedTime - previousTime;
}

double ActionObject::getDuration(){
    return duration;
}

double ActionObject::getRemainedTime(){
    return remainedTimeByDeath;
}

//returns unused time
double ActionObject::setCurrentTime(double elapsedTime){
//    cout << "ElapsedTime = " << elapsedTime << endl;
    double tempTime = totalElapsedTime;
    tempTime += elapsedTime;
    
    if(tempTime >= duration) {
        cout << "Total elapsedTime exceeded duration" << endl;
        previousTime = totalElapsedTime;
        totalElapsedTime = duration;
        this->elapsedTime = totalElapsedTime - previousTime;
//        cout << "previousTime = " << previousTime << endl;
//        cout << "totalElapsedTime = " << totalElapsedTime << endl;
        cout << "remaining Time = " << tempTime - duration << endl;
        return (tempTime - duration);
    }

    previousTime = totalElapsedTime;
    totalElapsedTime += elapsedTime;
    this->elapsedTime = elapsedTime;
//    cout << "previousTime = " << previousTime << endl;
//    cout << "totalElapsedTime = " << totalElapsedTime << endl;
    return 0;
}

bool ActionObject::isRunning(){
    if(alive)
        return running;
    return false;
}

bool ActionObject::isAlive(){
    return alive;
}

void ActionObject::startAction(){
    running = true;
}

void ActionObject::kill(){
    if(alive && running){
        alive = false;
        running = false;
    }
}

void ActionObject::revive(){
    if(!alive){
        alive = true;
        running = false;
        
        totalElapsedTime = 0;
        previousTime = 0;
        unusedTime = 0;
        speed = 1;
    }
}

SpriteObject* ActionObject::getOwner(){
    return owner;
}

void ActionObject::bindOwnerPtr(SpriteObject *ownerPtr){
    this->owner = ownerPtr;
}