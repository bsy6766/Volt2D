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

ActionFadeTo::ActionFadeTo():
ActionObject(),
totalOpacityToFade(0),
fadedOpacity(0),
finalOpacity(0){
    cout << "Creating action fade" << endl;
}

ActionFadeTo::~ActionFadeTo(){
    cout << "Deleting action" << endl;
}

ActionFadeTo* ActionFadeTo::createFadeTo(double duration, float opacity){
    ActionFadeTo* newFadeTo = new ActionFadeTo();
    newFadeTo->initFadeTo(opacity, duration);
    return newFadeTo;
}

void ActionFadeTo::initFadeTo(float opacity, double duration){
    if(opacity < 0)
        opacity = 0;
    else if(opacity > 255)
        opacity = 255;
    
    this->duration = duration;
    this->finalOpacity = opacity;
    this->fadedOpacity = 0;
}

void ActionFadeTo::startAction(){
    ActionObject::startAction();
    this->originalOpacity = this->target->getOpacity();
    this->totalOpacityToFade = finalOpacity - originalOpacity;
}

void ActionFadeTo::instantUpdate(){
    fadedOpacity = totalOpacityToFade;
    this->target->setOpacity(fadedOpacity);
    alive = false;
}

void ActionFadeTo::intervalUpdate(double& remainedTime){
    //get time in float
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        fadedOpacity = totalOpacityToFade + originalOpacity;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(totalOpacityToFade == 0){
            fadedOpacity = totalOpacityToFade;
        }
        else{
            fadedOpacity = totalOpacityToFade * (currentTime / duration) + originalOpacity;
        }
    }
    this->target->setOpacity(fadedOpacity);
}

void ActionFadeTo::updateAction(double& remainedTime){
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
    fadedOpacity = 0;   //clear
    originalOpacity = 0;
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}

ActionObject* ActionFadeTo::clone(){
    ActionFadeTo* cloneFadeTo = new ActionFadeTo();
    cloneFadeTo->initFadeTo(this->finalOpacity, this->duration);
    return cloneFadeTo;
}