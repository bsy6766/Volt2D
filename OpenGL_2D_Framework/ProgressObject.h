//
//  ProgressObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressObject__
#define __OpenGL_2D_Framework__ProgressObject__

#include <iostream>
#include "Texture.h"

class ProgressObject{
protected:
    double duration;
    double totalElapsedTime;
    
    //0.0 ~ 100.0
    float percentage;
    
private:
public:
    ProgressObject();
    ~ProgressObject();
    
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif /* defined(__OpenGL_2D_Framework__ProgressObject__) */
