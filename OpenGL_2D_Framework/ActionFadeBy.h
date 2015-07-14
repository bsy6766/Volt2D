//
//  ActionFadeBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionFadeBy__
#define __OpenGL_2D_Framework__ActionFadeBy__

#include "SpriteObject.h"
#include "ActionObject.h"

class ActionFadeBy : public ActionObject{
private:
    float opacityToFade;
    float fadedOpacity;
    float previousOpacity;
    
    void instantUpdate();
    void intervalUpdate(double& remainedTime);
    
public:
    ActionFadeBy();
    ActionFadeBy(const ActionFadeBy& other);
    ~ActionFadeBy();
    
    void initFadeBy(float opacity, double duration);
    
    //virtuals
    virtual void updateAction(double& remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionFadeBy__) */
