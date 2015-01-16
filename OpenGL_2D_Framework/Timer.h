//
//  Timer.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__Timer__
#define __CS364FinalProject__Timer__

#include <GLFW/glfw3.h>

//Singleton Timer
class Timer{
private:
    double currentTime;
    double previousTime;
    
    static Timer instance;
    
    //private constructor
    Timer(){
        previousTime = -1;
    };
    //copy constructor not defined. Prevents copying instance
    Timer(Timer const&);
    //assign operator constructor not defined. Prevenets copying instance
    void operator=(Timer const&);
    
public:
    //return static timer instance
    static Timer& getInstance(){
        //if timer never been created
//        if(!instance){
//            //create new instance
//            instance = new Timer();
//        }
        //return instance
        return instance;
    }
    
    void recordTime();
    
    double getElapsedTime();
    double getCurrentTime();
};


#endif /* defined(__CS364FinalProject__Timer__) */
