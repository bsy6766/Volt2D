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
    
    void initFadeTo(float opacity, double duration);
    void update(double elapsedTime, double unusedTime);
    
    //get & set
    float getFadedOpacity();
    void setOriginalOpacity(float opacity);
    
    //virtual
    void clone(SpriteAction* dataPtr);
    void revive();
};

#endif /* defined(__CS364FinalProject__ActionFadeTo__) */
