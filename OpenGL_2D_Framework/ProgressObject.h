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

class ProgressObject : public RenderableObject{
protected:
    Texture* texture;
    Texture* bgTexture;
    
    int totalPercentage;    //total percentage. defautl 100%
    int percentageRate;     //rate of each step. default 1%
    
    int currentPercentage;  //default 100%
    
    bool bgEnabled;
    float bgOpacity;    //defautl 255(1)
    
private:
public:
    ProgressObject();
    virtual ~ProgressObject();
    
    //get current percentage of progress
    int getPercentage();
    //reset progress bar to initial state
    void reset();
    void enableBg();
    void disableBg();
    void setBgOpacity(float opacity);
};

#endif /* defined(__OpenGL_2D_Framework__ProgressObject__) */
