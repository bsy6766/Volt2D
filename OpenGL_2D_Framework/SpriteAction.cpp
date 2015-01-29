//
//  SpriteAction.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/11/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteAction.h"
#include <iostream>

SpriteAction::SpriteAction(){
    running = false;
    alive = true;
    previousTime = 0;
    isProtected = false;    //defualt
    
    totalElapsedTime = 0;
    unusedTime = 0;
    speed = 1;
    
    std::cout << "creating action" << std::endl;
}

SpriteAction::~SpriteAction(){
    std::cout << "deleting action" << std::endl;
}

ActionID SpriteAction::getActionID(){
    return actionID;
}

double SpriteAction::getTotalElapsedTime(){
    return totalElapsedTime;
}

double SpriteAction::getPreviousTime(){
    return previousTime;
}

double SpriteAction::getElapsedTime(){
    return totalElapsedTime - previousTime;
}

double SpriteAction::getDuration(){
    return duration;
}

//returns unused time
double SpriteAction::setCurrentTime(double time){
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
bool SpriteAction::isRunning(){
    return running;
}

bool SpriteAction::isAlive(){
    return alive;
}

void SpriteAction::startAction(){
    running = true;
}

void SpriteAction::kill(){
    if(alive && running){
        alive = false;
        running = false;
    }
}

void SpriteAction::revive(){
    if(!alive && !running){
        alive = true;
        running = false;
        
        totalElapsedTime = 0;
        previousTime = 0;
        unusedTime = 0;
        speed = 1;
    }
}

void SpriteAction::clone(SpriteAction *ptr){
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