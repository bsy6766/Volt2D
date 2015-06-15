//
//  ActionEase.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionEase__
#define __OpenGL_2D_Framework__ActionEase__

#include <string>

class ActionEase{
protected:
    ActionEase();
    virtual ~ActionEase();
    
    //determines the rate of ease
    float rate;
public:
    virtual float update(float elapsedTime);
};

#endif /* defined(__OpenGL_2D_Framework__ActionEase__) */
