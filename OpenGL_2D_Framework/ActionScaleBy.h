//
//  ActionScaleBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/19/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionScaleBy__
#define __OpenGL_2D_Framework__ActionScaleBy__

#include "ActionObject.h"
#include "CommonInclude.h"

class ActionScaleBy : public ActionObject{
private:
    float startScale;
    float destScale;
    float srcScale;
    float scaledScale;
    
public:
    ActionScaleBy();
    ~ActionScaleBy();
    
    //scale 0.0 ~ 1.0
    void initScaleBy(float scale, double duration);
    
    void setOriginalScale(float scale);
    float getScaledScale();
    
    virtual void instantUpdate();
    virtual void update(double elapsedTiem, double unusedTime);
    virtual void clone(ActionObject *ptr);
};

#endif /* defined(__OpenGL_2D_Framework__ActionScaleBy__) */
