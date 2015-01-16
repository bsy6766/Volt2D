//
//  ActionFadeTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__ActionFadeTo__
#define __CS364FinalProject__ActionFadeTo__

#include "SpriteAction.h"

class ActionFadeTo : public SpriteAction{
private:
    float finalOpacity;
    float originalOpacity;
    float fadedOpacity;
    float previousOpacity;
    
public:
    ActionFadeTo();
    ~ActionFadeTo();
    void clone(SpriteAction* dataPtr);
    void initFadeTo(float opacity, double duration);
    void setOriginalOpacity(float opacity);
    void update(double elapsedTime, double unusedTime);
    float getFadedOpacity();
    void revive();
};

#endif /* defined(__CS364FinalProject__ActionFadeTo__) */
