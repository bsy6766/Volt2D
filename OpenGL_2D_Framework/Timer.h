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

/**
 *  @class Timer
 *  @brief Records time. Unit is ms.
 *  @note Singleton (b..but..Singleton is bad!)
 */
class Timer{
private:
    /**
     *  Current time of program
     */
    double currentTime;
    
    /**
     *  Previous time of program
     */
    double previousTime;
    
    /**
     *  Singleton instance
     */
    static Timer instance;
    
    /**
     *  Private Singleton constructor
     */
    Timer(){
        //on creation, set previous time to -1 so we know this is a fresh instance
        previousTime = -1;
    };
    
    //copy constructor not defined. Prevents copying instance
    Timer(Timer const&);
    //assign operator constructor not defined. Prevenets copying instance
    void operator=(Timer const&);
    
public:
    /**
     *  Singleton instance getter
     */
    static Timer& getInstance(){
        return instance;
    }
    
    /**
     *  Record and update time
     */
    void recordTime();
    
    /**
     *  Get elapsed time for current iteration
     *  @return Elapsed time in ms.
     */
    double getElapsedTime();
    
    /**
     *  Get total elapsed time since program started
     *  @return Total elapsed time
     */
    double getTotalElapsedTime();
};


#endif /* defined(__OpenGL_2D_Framework__Timer__) */
