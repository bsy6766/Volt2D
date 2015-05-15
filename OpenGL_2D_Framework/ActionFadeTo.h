//
//  ActionFadeTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionFadeTo__
#define __OpenGL_2D_Framework__ActionFadeTo__

#include "ActionObject.h"

class ActionFadeTo : public ActionObject{
private:
    float finalOpacity;
    float originalOpacity;
    float fadedOpacity;
    float previousOpacity;
    
public:
    ActionFadeTo();
    ~ActionFadeTo();
    
    void initFadeTo(float opacity, double duration);
    
    //get & set
    float getFadedOpacity();
    void setOriginalOpacity(float opacity);
    
    //virtual
    virtual void instantUpdate();
    virtual void update(double elapsedTime, double unusedTime);
    virtual void clone(ActionObject* dataPtr);
    
    //override
    void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionFadeTo__) */
