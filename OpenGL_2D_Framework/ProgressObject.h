//
//  ProgressObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressObject__
#define __OpenGL_2D_Framework__ProgressObject__

#include "CommonInclude.h"
#include "Texture.h"
#include "Timer.h"
#include "RenderableObject.h"

/**
 *  Ratio and Incrementation
 *  All progress type objects(bar, radian) has ratio for
 *  increments and total capacity.
 *
 *  Progress Sprite will be divided in to max 100 steps.
 */

class ProgressObject : public RenderableObject{
protected:
    int totalSteps; // total steps of progress bar. Can't exceed 100
    int currentStep;
    
private:
public:
    ProgressObject();
    virtual ~ProgressObject();
    
    //get current percentage of progress
    int getPercentage();
    //reset progress bar to initial state
    void reset();
};

#endif /* defined(__OpenGL_2D_Framework__ProgressObject__) */
