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

//int ProgressObject::getPercentage(){
//    return this->currentPercentage;
//}
//
void ProgressObject::setPercentage(int percentage){
    if(percentage > totalPercentage)
        percentage = totalPercentage;
    this->currentPercentage = percentage;
}

//void ProgressObject::setTotalPercentage(int totalPercentage){
//    this->totalPercentage
//}

//void ProgressObject::enableBg(){
//    this->bgEnabled = true;
//}
//
//void ProgressObject::disableBg(){
//    this->bgEnabled = false;
//}
//
//void ProgressObject::setBgOpacity(float opacity){
//    this->bgOpacity = opacity;
//}