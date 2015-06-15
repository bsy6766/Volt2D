//
//  ActionFadeBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionFadeBy.h"

ActionFadeBy::ActionFadeBy():
ActionObject(),
fadedOpacity(0),
finalOpacity(0){
    cout << "Creating action fade" << endl;
}

ActionFadeBy::ActionFadeBy(const ActionFadeBy& other):ActionObject(other){
    this->finalOpacity = other.finalOpacity;
    this->fadedOpacity = other.fadedOpacity;
    this->previousOpacity = other.previousOpacity;
}

ActionFadeBy::~ActionFadeBy(){
    cout << "Deleting action" << endl;
}

void ActionFadeBy::initFadeBy(float opacity, double duration){
    this->actionID = ActionID::ACTION_FADE_BY;
    this->duration = duration;
    this->finalOpacity = opacity;
    this->fadedOpacity = 0;
    this->previousOpacity = 0;
}

float ActionFadeBy::getFadedOpacity(){
    return fadedOpacity;
}

void ActionFadeBy::instantUpdate(){
    fadedOpacity = finalOpacity;
    alive = false;
}

void ActionFadeBy::intervalUpdate(double remainedTime){
    //get time in float
    float duration = (float)this->duration;
    
    if(totalElapsedTime == duration){
        fadedOpacity = finalOpacity - previousOpacity;
        alive = false;
        return;
    }
    else{
        float currentTime = (float)(this->totalElapsedTime + remainedTime);
        float curOpacity = finalOpacity * (currentTime / duration);
        float diff = curOpacity - previousOpacity;

        fadedOpacity = diff;
        previousOpacity += diff;
    }
}

void ActionFadeBy::updateAction(double remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionFadeBy::revive(){
    //revive. original and previous will be updated
    previousOpacity = 0;
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}