//
//  ProgressObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ProgressObject.h"

using std::cout;
using std::endl;

ProgressObject::ProgressObject(){
    cout << "Creating ProgressObject" << endl;
    
    this->duration = 0;
    this->totalElapsedTime =0;
    
    //initially percentage is set to full(100.0)
    this->percentage = 100.0;
}

ProgressObject::~ProgressObject(){
    cout << "Deleting ProgressObject" << endl;
}