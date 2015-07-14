//
//  ProgressFromTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressFromTo__
#define __OpenGL_2D_Framework__ProgressFromTo__

#include "ProgressObject.h"
#include "ActionObject.h"

//Similar to By action than To
class ProgressFromTo : public ActionObject{
private:
    int from;
    int to;
    int totalPercentage;
    int changedPercentage;
    int previousPercentage;
    
    void instantUpdate();
    void intervalUpdate(double& remainedTime);
    
public:
    ProgressFromTo();
    ProgressFromTo(const ProgressFromTo& other);
    ~ProgressFromTo();
    
    void initProgressFromTo(int from, int to, float duration);
    
    //override
    virtual void startAction();
    virtual void updateAction(double& remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ProgressFromTo__) */
