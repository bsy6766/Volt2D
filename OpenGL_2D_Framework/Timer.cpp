//
//  Timer.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "Timer.h"

//Timer *Timer::instance = nullptr;
Timer Timer::instance;

double Timer::getElapsedTime(){
    if(currentTime == -1 || previousTime == -1)
        return 0;
    
    return currentTime - previousTime;
}

void Timer::recordTime(){
    if(previousTime == -1){
        previousTime = 0;
        currentTime = glfwGetTime();
    }
    else{
        previousTime = currentTime;
        currentTime = glfwGetTime();
    }
}

double Timer::getCurrentTime(){
    return currentTime;
}