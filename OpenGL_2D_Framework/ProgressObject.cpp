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
texture(0),
bgTexture(0),
bgEnabled(false),
bgOpacity(255)
{
    cout << "Creating ProgressObject" << endl;

}

ProgressObject::~ProgressObject(){
    cout << "Deleting ProgressObject" << endl;
    if (texture){
        delete texture;
        texture = nullptr;
    }
    
    if(bgTexture){
        delete bgTexture;
        bgTexture = 0;
    }
}

int ProgressObject::getPercentage(){
    return this->currentPercentage;
}

void ProgressObject::enableBg(){
    this->bgEnabled = true;
}

void ProgressObject::disableBg(){
    this->bgEnabled = false;
}

void ProgressObject::setBgOpacity(float opacity){
    this->bgOpacity = opacity;
}