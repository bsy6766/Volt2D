//
//  Object.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Object__
#define __OpenGL_2D_Framework__Object__

//#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Director.h"
#include "CommonInclude.h"

class Object{
protected:
    glm::vec3 position;
    WinSize size;
private:
public:
    Object();
    virtual ~Object();
    
    //position
    void setPosition(glm::vec3 position);
    void addPosition(glm::vec3 position);
    glm::vec3 getPosition();
};

#endif /* defined(__OpenGL_2D_Framework__Object__) */
