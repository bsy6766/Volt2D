//
//  Program.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/8/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Program__
#define __OpenGL_2D_Framework__Program__

#include <GL/glew.h>
#include <stdexcept>
#include <vector>
#include "Shader.h"

using namespace std;

class Program{
private:
    GLuint programObject;
    
public:
    Program();
    ~Program();
    
    //init
    void createProgram(Shader *vertexShaderPtr, Shader *fragmentShaderPtr);
    
    //get
    GLuint getObject();
    GLint attrib(const GLchar* attribName) const;
};

#endif /* defined(__OpenGL_2D_Framework__Program__) */
