//
//  Color.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Color__
#define __OpenGL_2D_Framework__Color__

#include <glm/glm.hpp>

class Color{
private:
    void wrapColorBoundary(float& color);
    
    //0~255
    float r;
    float g;
    float b;
    //0.0~1.0
    float a;
    
    Color(float r, float g, float b, float a);
    
public:
    float getR();
    float getG();
    float getB();
    float getA();
    
    void setR(float r);
    void setG(float g);
    void setB(float b);
    void setA(float a);
    
    glm::vec3 getColor();
    
    static const Color RED;
    static const Color WHITE;
};

#endif /* defined(__OpenGL_2D_Framework__Color__) */
