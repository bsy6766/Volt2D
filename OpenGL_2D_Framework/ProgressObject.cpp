//
//  ProgressObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ProgressObject.h"

ProgressObject::ProgressObject():
RenderableObject(),
totalPercentage(100),
percentageRate(1),
currentPercentage(100),
totalSteps(100),
texture(0),
w(-1),
h(-1)
{
    cout << "Creating ProgressObject" << endl;

}

ProgressObject::~ProgressObject(){
    cout << "Deleting ProgressObject" << endl;
    if (texture){
        delete texture;
        texture = nullptr;
    }
}

int ProgressObject::getPercentage(){
    return this->currentPercentage;
}

void ProgressObject::setPercentage(int percentage){
    if(percentage > totalPercentage)
        percentage = totalPercentage;
    this->currentPercentage = percentage;
}

void ProgressObject::addPercentage(int percentage){
    int sum = percentage + this->currentPercentage;
    if(sum > totalPercentage)
        sum = totalPercentage;
    currentPercentage = sum;
}

//void ProgressObject::addActions(std::initializer_list<ActionObject *> actions, int repeat){
//    //if 
////    std::initializer_list<ActionObject*>::iterator iter;
////    std::list<ActionObject*> newActionList;
////    for(iter = actions.begin(); iter != actions.end();){
////        //if it's
////        if(dynamic_cast<ProgressFromTo*>(*iter) == nullptr){
////            
////        }
////        iter++;
////    }
//}