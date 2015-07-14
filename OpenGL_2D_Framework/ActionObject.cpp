//
//  ActionObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionObject.h"

//unsigned int ActionObject::ACTION_ID = 0;

ActionObject::ActionObject():
running(false),
alive(true),
previousTime(0),
isProtected(false),
totalElapsedTime(0),
speed(1),
duration(-1)
{
    std::cout << "ActionObject()" << std::endl;
}

ActionObject::ActionObject(const ActionObject& other){
    this->duration = other.duration;
    this->totalElapsedTime = other.totalElapsedTime;
    this->previousTime = other.previousTime;
    this->speed = other.speed;
    this->target = other.target;
    this->objID = other.objID;
    this->running = other.running;
    this->alive = other.alive;
    this->isProtected = other.isProtected;
}

ActionObject::~ActionObject(){
    std::cout << "~ActionObject()" << std::endl;
}

double ActionObject::getDuration(){
    return duration;
}

//returns unused time
double ActionObject::setCurrentTime(double elapsedTime){
    double tempTime = totalElapsedTime;
    tempTime += elapsedTime;
    
    if(tempTime >= duration) {
        previousTime = totalElapsedTime;
        totalElapsedTime = duration;
        return (tempTime - duration);
    }

    previousTime = totalElapsedTime;
    totalElapsedTime += elapsedTime;
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
        speed = 1;
    }
}

RenderableObject* ActionObject::getTarget(){
    return target;
}

void ActionObject::bindTarget(RenderableObject *target){
    this->target = target;
}