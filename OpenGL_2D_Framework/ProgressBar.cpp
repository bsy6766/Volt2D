//
//  ProgressBar.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/23/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ProgressBar.h"

using std::cout;
using std::endl;

ProgressBar::ProgressBar(){
    cout << "Creating Progress Bar" << endl;
}

ProgressBar::~ProgressBar(){
    cout << "Deleting Progress Bar" << endl;
}

void ProgressBar::update(){
//    double elapsedTime = Timer::getInstance().getElapsedTime();
    
    //if progress bar is still alive
    if(totalElapsedTime < duration){
        //update
    }
}

void ProgressBar::render(){
    
}