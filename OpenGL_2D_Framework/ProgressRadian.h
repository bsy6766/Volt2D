//
//  ProgressRadian.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/26/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressRadian__
#define __OpenGL_2D_Framework__ProgressRadian__


#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <cmath>
#endif
#include "ProgressObject.h"

class ProgressRadian: public ProgressObject{
private:
    
public:
    ProgressRadian();
    ~ProgressRadian();
    
    void initProgressRadian(GLenum textureTarget, const std::string barTextureName);
    //    void setProgressRate(int rate);
    
    //virtual
    virtual void computeVertexData();
    virtual void loadVertexData();
    virtual void render();
};

#endif /* defined(__OpenGL_2D_Framework__ProgressRadian__) */
