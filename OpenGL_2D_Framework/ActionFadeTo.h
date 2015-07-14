//
//  ActionFadeTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionFadeTo__
#define __OpenGL_2D_Framework__ActionFadeTo__

#include "SpriteObject.h"
#include "ActionObject.h"

class ActionFadeTo : public ActionObject{
private:
    float finalOpacity;
    float originalOpacity;
    float fadedOpacity;
    float totalOpacityToFade;
    
    void instantUpdate();
    void intervalUpdate(double& remainedTime);
    
public:
    ActionFadeTo();
    ActionFadeTo(const ActionFadeTo& other);
    ~ActionFadeTo();
    
    void initFadeTo(float opacity, double duration);

    //virtuals
    virtual void startAction();
    virtual void updateAction(double& remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionFadeTo__) */
