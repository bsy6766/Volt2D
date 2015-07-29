//
//  ActionCallFunc.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionCallFunc.h"

using namespace Volt2D;

ActionCallFunc::ActionCallFunc():
ActionObject(),
function(nullptr)
{
    
}

ActionCallFunc::~ActionCallFunc(){
    
}

ActionCallFunc* ActionCallFunc::createCallFunc(const std::function<void()>& func){
    ActionCallFunc* newCallFunc = new ActionCallFunc();
    newCallFunc->initActionCallFunc(func);
    return newCallFunc;
}

void ActionCallFunc::initActionCallFunc(const std::function<void()>& func){
	function = func;
}

void ActionCallFunc::startAction(){
    ActionObject::startAction();
}

void ActionCallFunc::updateAction(double &remainedTime){
    //since this is instant, 
    remainedTime += this->totalElapsedTime;
    cout << "callfunc. this iter time = " << this->totalElapsedTime << ", adding to remained = " << remainedTime << endl;
	(function)();
    this->alive = false;
}

void ActionCallFunc::revive(){
    ActionObject::revive();
}

ActionObject* ActionCallFunc::clone(){
    ActionCallFunc* cloneCallFunc = new ActionCallFunc();
	cloneCallFunc->initActionCallFunc(function);
    return cloneCallFunc;
}