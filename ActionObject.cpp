//
//  ActionObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionObject.h"

ActionObject::ActionObject(){
    running = false;
    alive = true;
    previousTime = 0;
    isProtected = false;    //defualt
    
    totalElapsedTime = 0;
    unusedTime = 0;
    speed = 1;
    
    std::cout << "creating action" << std::endl;
}

ActionObject::~ActionObject(){
    std::cout << "deleting action" << std::endl;
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

//returns unused time
double ActionObject::setCurrentTime(double time){
    double tempTime = totalElapsedTime;
    tempTime += time;
    
    if(tempTime > duration) {
        previousTime = totalElapsedTime;
        totalElapsedTime = duration;
        alive = false;
        return (tempTime - duration);
    }
    
    previousTime = totalElapsedTime;
    totalElapsedTime += time;
    return 0;
}

//true = active, false = done
bool ActionObject::isRunning(){
    return running;
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
    if(!alive && !running){
        alive = true;
        running = false;
        
        totalElapsedTime = 0;
        previousTime = 0;
        unusedTime = 0;
        speed = 1;
    }
}

void ActionObject::clone(ActionObject *ptr){
    //check if pointer is null!!
    
    std::cout << "sprite action clone base" << std::endl;
    this->actionID = ptr->actionID;
    this->duration = ptr->duration;
    this->totalElapsedTime = ptr->totalElapsedTime;
    this->unusedTime = ptr->unusedTime;
    this->speed = ptr->speed;
    
    this->running = ptr->running;
    this->alive = ptr->alive;
    
    this->previousTime = ptr->previousTime;
    
    this->isProtected = ptr->isProtected;
}