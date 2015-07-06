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
totalSteps(100),
currentStep(0)
{
    cout << "Creating ProgressObject" << endl;

}

ProgressObject::~ProgressObject(){
    cout << "Deleting ProgressObject" << endl;
}