//
//  Timer.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Timer.h"

Timer Timer::instance;

double Timer::getElapsedTime(){
    //if user hasn't record the time, return -
    if(currentTime == -1 || previousTime == -1)
        return 0;
    
    //return the elapsed time
    return currentTime - previousTime;
}

void Timer::recordTime(){
    //if previous time is -1
    if(previousTime == -1){
        //it's a fresh instance. set prev to initial(0) and record current time
        previousTime = 0;
        currentTime = glfwGetTime();
    }
    else{
        //save current time to prev and record current time
        previousTime = currentTime;
        currentTime = glfwGetTime();
    }
}

double Timer::getTotalElapsedTime(){
    //return current time(ms)
    return currentTime;
}