//
//  ActionRotateTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionRotateTo__
#define __OpenGL_2D_Framework__ActionRotateTo__

#include "ActionObject.h"

class ActionRotateTo :  public ActionObject{
private:
    float startAngle;
    float destinationAngle;
//    float previousAngle;
    float movedAngle;   //amount of angle moved in single iteration
    float totalAngleToRotate;
    
public:
    ActionRotateTo();
    ~ActionRotateTo();
    void initRotateTo(float angle, float duration);
    
    //set & get
    void setOriginalAngle(float angle, bool fresh);
    float getMovedAngle();
    
    //virtuals
    virtual void updateAction(double remainedTime);
    virtual void instantUpdate();
    virtual void intervalUpdate(double remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionRotateTo__) */