//
//  ActionRotateBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/8/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__ActionRotateBy__
#define __CS364FinalProject__ActionRotateBy__

#include "SpriteAction.h"

class ActionRotateBy :  public SpriteAction{
private:
    float startAngle;
    float rotatingAngle;
    float previousAngle;
    float movedAngle;
    
public:
    ActionRotateBy();
    ~ActionRotateBy();
    void initRoateBy(float angle, float duration);
    
    void update(double elapsedTime, double unusedTime);
    
    void setOriginalAngle(float angle, bool fresh);
    float getMovedAngle();
    
    //override
    void revive();
    void clone(SpriteAction* dataPtr);
};

#endif /* defined(__CS364FinalProject__ActionRotateBy__) */
