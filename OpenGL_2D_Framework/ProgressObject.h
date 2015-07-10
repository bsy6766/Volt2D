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

#define VOID_OFFSET(i) (GLvoid*)(i)

class ProgressObject : public RenderableObject{
protected:
    Texture* texture;
    
    int w;
    int h;
    
    int totalPercentage;    //total percentage. defautl 100%
    int percentageRate;     //rate of each step. default 1%
    int totalSteps;
    
    int currentPercentage;  //default 100%
    
private:
public:
    ProgressObject();
    virtual ~ProgressObject();
    
    //reset progress bar to initial state
//    void reset();
//    void enableBg();
//    void disableBg();
//    void setBgOpacity(float opacity);
    
//    void setTotalPercentage(int totalPercentage);
//    void setPercentageRate(int rate);
    void setPercentage(int percentage);
    void addPercentage(int percentage);
    int getPercentage();
    
};

#endif /* defined(__OpenGL_2D_Framework__ProgressObject__) */
