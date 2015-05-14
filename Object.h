//
//  Object.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Object__
#define __OpenGL_2D_Framework__Object__

#include <glm/glm.hpp>
#include "Director.h"

class Object{
protected:
    glm::vec3 position;
    bool visible;
    WinSize size;
private:
public:
    Object();
    virtual ~Object();
    
    //setters
    void setPosition(glm::vec3 position);
    void setVisible(bool visibility);
    
    //getters
    glm::vec3 getPosition();
    bool isVisible();
};

#endif /* defined(__OpenGL_2D_Framework__Object__) */
