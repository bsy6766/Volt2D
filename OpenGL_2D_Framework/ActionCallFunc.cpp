//
//  ActionCallFunc.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionCallFunc.h"

ActionCallFunc::ActionCallFunc():
ActionObject(),
func(0)
{
    
}

ActionCallFunc::~ActionCallFunc(){
    
}

ActionCallFunc* ActionCallFunc::createCallFunc(const std::function<void ()> func){
    ActionCallFunc* newCallFunc = new ActionCallFunc();
    newCallFunc->initActionCallFunc(func);
    return newCallFunc;
}

void ActionCallFunc::initActionCallFunc(const std::function<void()> func){
    this->func = func;
}

void ActionCallFunc::startAction(){
    ActionObject::startAction();
}

void ActionCallFunc::updateAction(double &remainedTime){
    //since this is instant, 
    remainedTime += this->totalElapsedTime;
    cout << "callfunc. this iter time = " << this->totalElapsedTime << ", adding to remained = " << remainedTime << endl;
    (this->func)();
    this->alive = false;
}

void ActionCallFunc::revive(){
    ActionObject::revive();
}

ActionObject* ActionCallFunc::clone(){
    ActionCallFunc* cloneCallFunc = new ActionCallFunc();
    cloneCallFunc->initActionCallFunc(this->func);
    return cloneCallFunc;
}