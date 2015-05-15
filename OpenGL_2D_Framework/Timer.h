//
//  Timer.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Timer__
#define __OpenGL_2D_Framework__Timer__

#include <GLFW/glfw3.h>
#include <iostream>

//Singleton Timer class
class Timer{
private:
    double currentTime;
    double previousTime;
    
    //singleton instnace
    static Timer instance;
    
    //private constructor
    Timer(){
        //on creation, set previous time to -1 so we know this is a fresh instance
        previousTime = -1;
    };
    
    //copy constructor not defined. Prevents copying instance
    Timer(Timer const&);
    //assign operator constructor not defined. Prevenets copying instance
    void operator=(Timer const&);
    
public:
    //return static timer instance
    static Timer& getInstance(){
        return instance;
    }
    
    //record the time
    void recordTime();
    
    //time getter
    double getElapsedTime();
    double getTotalElapsedTime();
};


#endif /* defined(__OpenGL_2D_Framework__Timer__) */
