//
//  ActionFadeTo.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "ActionFadeTo.h"

#include <iostream>

using std::cout;
using std::endl;

ActionFadeTo::ActionFadeTo():totalOpacityToFade(0), fadedOpacity(0), finalOpacity(0){
    cout << "Creating action fade" << endl;
}

ActionFadeTo::~ActionFadeTo(){
    cout << "Deleting action" << endl;
}

void ActionFadeTo::initFadeTo(float opacity, double duration){
    if(opacity < 0)
        opacity = 0;
    else if(opacity > 255)
        opacity = 255;
    
    this->actionID = ACTION_FADE_TO;
    this->duration = duration;
    
    this->finalOpacity = opacity;
    this->fadedOpacity = 0;
//    this->previousOpacity = 0;
}

void ActionFadeTo::setOriginalOpacity(float opacity){
    this->originalOpacity = opacity;
//    this->previousOpacity = opacity;
    this->totalOpacityToFade = finalOpacity - originalOpacity;
}

float ActionFadeTo::getFadedOpacity(){
    return fadedOpacity;
}

void ActionFadeTo::instantUpdate(){
    fadedOpacity = totalOpacityToFade;
//    previousOpacity = finalOpacity;
    alive = false;
}

void ActionFadeTo::intervalUpdate(double remainedTime){
    //get time in float
    float duration = (float)this->duration;
    
    if(totalElapsedTime == duration){
        fadedOpacity = totalOpacityToFade + originalOpacity;
        alive = false;
        return;
    }
    else{
        float currentTime = (float)(this->totalElapsedTime + remainedTime);
        fadedOpacity = totalOpacityToFade * (currentTime / duration) + originalOpacity;
    }
}

void ActionFadeTo::updateAction(double remainedTime){
    if(!alive)
        return;
    
    if(duration == 0){
        instantUpdate();
    }
    else{
        intervalUpdate(remainedTime);
    }
}

void ActionFadeTo::revive(){
    //revive. original and previous will be updated
//    originalOpacity = 0;
//    previousOpacity = 0;
    fadedOpacity = 0;   //clear
    
    ActionObject::revive();
}