//
//  ActionRotateBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/8/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionRotateBy__
#define __OpenGL_2D_Framework__ActionRotateBy__

#include "ActionObject.h"

class ActionRotateBy :  public ActionObject{
private:
    float startAngle;
    float rotatingAngle;
    float previousAngle;
    float movedAngle;
    
public:
    ActionRotateBy();
    ~ActionRotateBy();
    void initRotateBy(float angle, float duration);
    
    //set & get
    void setOriginalAngle(float angle, bool fresh);
    float getMovedAngle();
    
    //virtuals
    virtual void instantUpdate();
    virtual void update(double elapsedTime, double unusedTime);
    virtual void clone(ActionObject* dataPtr);
    
    //override
    void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionRotateBy__) */
