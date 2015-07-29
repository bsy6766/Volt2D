//
//  ActionFadeBy.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionFadeBy.h"

using namespace Volt2D;

ActionFadeBy::ActionFadeBy():
ActionObject(),
fadedOpacity(0),
opacityToFade(0){
//    cout << "[SYSTEM::INFO] Creating ActionFadeBy" << endl;
}

ActionFadeBy::~ActionFadeBy(){
//    cout << "[SYSTEM::INFO] Releasing ActionFadeBy" << endl;
}

ActionFadeBy* ActionFadeBy::createFadeBy(double duration, float opacity){
    ActionFadeBy* newFadeBy = new ActionFadeBy();
    newFadeBy->initFadeBy(opacity, duration);
    return newFadeBy;
}

void ActionFadeBy::initFadeBy(float opacity, double duration){
    this->duration = duration;
    this->opacityToFade = opacity;
    this->fadedOpacity = 0;
    this->previousOpacity = 0;
}

void ActionFadeBy::instantUpdate(){
    fadedOpacity = opacityToFade;
    alive = false;
    this->target->addOpacity(fadedOpacity);
}

void ActionFadeBy::intervalUpdate(double& remainedTime){
    //get time in float
    float duration = (float)this->duration;
    float currentTime = (float)(this->totalElapsedTime + remainedTime);
    
    if(currentTime >= duration){
        fadedOpacity = opacityToFade - previousOpacity;
        alive = false;
        remainedTime = currentTime - duration;
    }
    else{
        remainedTime = 0;
        if(opacityToFade == 0){
            fadedOpacity = 0;
            previousOpacity = 0;
        }
        else{
            float diff = (opacityToFade * (currentTime / duration)) - previousOpacity;
            fadedOpacity = diff;
            previousOpacity += diff;
        }
    }
    this->target->addOpacity(fadedOpacity);
}

void ActionFadeBy::updateAction(double& remainedTime){
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
    this->previousOpacity = 0;
    this->alive = false;
    this->running = false;
    ActionObject::revive();
}

ActionObject* ActionFadeBy::clone(){
    ActionFadeBy* cloneFadeBy = new ActionFadeBy();
    cloneFadeBy->initFadeBy(this->opacityToFade, this->duration);
    return cloneFadeBy;
}