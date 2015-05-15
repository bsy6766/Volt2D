//
//  ActionScaleBy.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/19/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionScaleBy.h"

ActionScaleBy::ActionScaleBy(){
    cout << "Creating action scale by" << endl;
}

ActionScaleBy::~ActionScaleBy(){
    cout << "Deleting action scale by" << endl;
}

void ActionScaleBy::initScaleBy(float scale, double duration){
    this->duration = duration;
    this->actionID = ACTION_SCALE_BY;
    
    this->destScale = scale;
}

void ActionScaleBy::setOriginalScale(float scale){
    this->srcScale = scale;
    
}

float ActionScaleBy::getScaledScale(){
    return this->scaledScale;
}

void ActionScaleBy::update(double elapsedTime, double unusedTime){
    if(elapsedTime == -1){
        
        alive = false;
        return;
    }
    
    float duration = (float)getDuration();
    float currentTime = (float)getTotalElapsedTime();
    float time = (float)getElapsedTime() + (float)unusedTime;
    
    if(currentTime >= duration){
        cout << "ScaleBy action done" << endl;
    }
    else{
        
    }
}

void ActionScaleBy::clone(ActionObject *ptr){
    
}