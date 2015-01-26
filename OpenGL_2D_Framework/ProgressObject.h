//
//  ProgressObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressObject__
#define __OpenGL_2D_Framework__ProgressObject__

#include <iostream>
#include "Timer.h"
#include "Texture.h"

const float PRECENTAGE_MAX = 100.0;
const float PERCENTAGE_MIN = 0.0;

/*
    Base class to each type of progress objects
    BAR: Typical bar type 
    RADIAN: Clock-like type
    BLOCK: Stacking block type
 */

class ProgressObject{
protected:
    double duration;
    double totalElapsedTime;
    
    //0.0 ~ 100.0
    float percentage;
    
    enum ProgressType{
        BAR = 0,
        RADIAL,
        BLOCK
    };
    
    bool reverse;
    
private:
public:
    ProgressObject();
    virtual ~ProgressObject();
    
    bool isReverse();
    
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif /* defined(__OpenGL_2D_Framework__ProgressObject__) */
