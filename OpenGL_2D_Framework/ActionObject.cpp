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
//unusedTime(0),
speed(1),
duration(-1)
//remainedTimeByDeath(0)
{
    std::cout << "ActionObject()" << std::endl;
    ACTION_ID++;
    objID = ACTION_ID;
}

ActionObject::ActionObject(const ActionObject& other){
    this->actionID = other.actionID;
    this->ACTION_ID = other.ACTION_ID;
    this->duration = other.duration;
    this->totalElapsedTime = other.totalElapsedTime;
    this->previousTime = other.previousTime;
//    this->elapsedTime = other.elapsedTime;
//    this->unusedTime = other.unusedTime;
//    this->remainedTimeByDeath = other.remainedTimeByDeath;
    this->speed = other.speed;
    this->owner = other.owner;
    this->objID = other.objID;
    this->running = other.running;
    this->alive = other.alive;
    this->isProtected = other.isProtected;
}

ActionObject::~ActionObject(){
    std::cout << "~ActionObject()" << std::endl;
}

ActionID ActionObject::getActionID(){
    return actionID;
}

double ActionObject::getDuration(){
    return duration;
}

//double ActionObject::getRemainedTime(){
//    return remainedTimeByDeath;
//}

//returns unused time
double ActionObject::setCurrentTime(double elapsedTime){
//    cout << "ElapsedTime = " << elapsedTime << endl;
    double tempTime = totalElapsedTime;
    tempTime += elapsedTime;
    
    if(tempTime >= duration) {
        cout << "Total elapsedTime exceeded duration" << endl;
        previousTime = totalElapsedTime;
        totalElapsedTime = duration;
//        this->elapsedTime = totalElapsedTime - previousTime;
//        cout << "previousTime = " << previousTime << endl;
//        cout << "totalElapsedTime = " << totalElapsedTime << endl;
        cout << "remaining Time = " << tempTime - duration << endl;
        return (tempTime - duration);
    }

    previousTime = totalElapsedTime;
    totalElapsedTime += elapsedTime;
//    this->elapsedTime = elapsedTime;
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
//        unusedTime = 0;
        speed = 1;
    }
}

RenderableObject* ActionObject::getOwner(){
    return owner;
}

void ActionObject::bindOwnerPtr(RenderableObject *ownerPtr){
    this->owner = ownerPtr;
}

//SpriteObject* ActionObject::getOwner(){
//    return owner;
//}
//
//void ActionObject::bindOwnerPtr(SpriteObject *ownerPtr){
//    this->owner = ownerPtr;
//}