//
//  ActionFadeTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "ActionFadeTo.h"

#include <iostream>

using std::cout;
using std::endl;

ActionFadeTo::ActionFadeTo(){
    cout << "Creating action fade" << endl;
}

ActionFadeTo::~ActionFadeTo(){
    cout << "Deleting action" << endl;
}

void ActionFadeTo::initFadeTo(float opacity, double duration){
    this->actionID = ACTION_FADE_TO;
    this->duration = duration;
    
    this->finalOpacity = opacity;
    this->fadedOpacity = 0;
    this->previousOpacity = 0;
}

void ActionFadeTo::setOriginalOpacity(float opacity){
    this->originalOpacity = opacity;
    this->previousOpacity = opacity;
}

float ActionFadeTo::getFadedOpacity(){
    return fadedOpacity;
}

void ActionFadeTo::update(double elapsedTime, double unusedTime){
    //if it's instant
    if(elapsedTime == -1){
        fadedOpacity = finalOpacity - originalOpacity;
        previousOpacity = finalOpacity;
        alive = false;
        return;
    }
    
    //get time in float
    float currentTime = (float)getTotalElapsedTime() + (float)unusedTime;
    float previousTime = (float)getPreviousTime();
    float duration = (float)getDuration();
    
    //if 
    if(currentTime == duration) {
        fadedOpacity = finalOpacity - previousOpacity;
    }
    else{
        fadedOpacity = (currentTime - previousTime) * (finalOpacity - originalOpacity) / duration;
        previousOpacity += fadedOpacity;
//        std::cout << "prev opacity = " << previousOpacity << std::endl;
    }
}

void ActionFadeTo::clone(SpriteAction* dataPtr){
    ActionFadeTo *other = static_cast<ActionFadeTo*>(dataPtr);
    
    std::cout << "Cloning action fade to" << std::endl;
    
    SpriteAction::clone(dataPtr);
    
    this->actionID = other->actionID;
    
    this->finalOpacity = other->finalOpacity;
    this->originalOpacity = other->originalOpacity;
    this->fadedOpacity = other->fadedOpacity;
    this->previousOpacity = other->previousOpacity;
}

//revive
void ActionFadeTo::revive(){
    //revive. original and previous will be updated
//    originalOpacity = 0;
    previousOpacity = 0;
    fadedOpacity = 0;   //clear
    
    SpriteAction::revive();
}