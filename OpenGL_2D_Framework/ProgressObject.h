//
//  ProgressObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressObject__
#define __OpenGL_2D_Framework__ProgressObject__

#include "Texture.h"
#include "RenderableObject.h"
#include "ProgressFromTo.h"
#include "CommonInclude.h"
#include "Timer.h"

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

    void setPercentage(int percentage);
    void addPercentage(int percentage);
    int getPercentage();
    
//    virtual void addActions(std::initializer_list<ActionObject*> actions, int repeat);
};

#endif /* defined(__OpenGL_2D_Framework__ProgressObject__) */
