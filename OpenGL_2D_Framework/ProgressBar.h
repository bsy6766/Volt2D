//
//  ProgressBar.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/23/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressBar__
#define __OpenGL_2D_Framework__ProgressBar__

#include <iostream>
#include "ProgressObject.h"

class ProgressBar: public ProgressObject{
private:
    
public:
    ProgressBar();
    ~ProgressBar();
    
    //virtual
    void update();
    void render();
};

#endif /* defined(__OpenGL_2D_Framework__ProgressBar__) */
