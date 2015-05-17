//
//  ActionObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionObject.h"

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