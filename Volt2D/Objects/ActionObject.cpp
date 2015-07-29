//
//  ActionObject.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionObject.h"

using namespace Volt2D;

ActionObject::ActionObject():
running(false),
alive(true),
isProtected(false),
totalElapsedTime(0),
duration(0)
{
//    std::cout << "[SYSTEM::INFO] Creating ActionObject" << std::endl;
}

ActionObject::ActionObject(const ActionObject& other){
    this->duration = other.duration;
    this->totalElapsedTime = other.totalElapsedTime;
    this->target = other.target;
    this->running = other.running;
    this->alive = other.alive;
    this->isProtected = other.isProtected;
}

ActionObject::~ActionObject(){
//    std::cout << "[SYSTEM::INFO] Releasing ActionObject" << std::endl;
}

double ActionObject::getDuration(){
    return duration;
}

//returns unused time
double ActionObject::setCurrentTime(double elapsedTime){
    assert(duration >= -1);
    
    double tempTime = totalElapsedTime;
    tempTime += elapsedTime;
    
    if(tempTime >= duration) {
        totalElapsedTime = duration;
        return (tempTime - duration);
    }

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
    }
}

RenderableObject* ActionObject::getTarget(){
    return target;
}

void ActionObject::bindTarget(RenderableObject *target){
    this->target = target;
}