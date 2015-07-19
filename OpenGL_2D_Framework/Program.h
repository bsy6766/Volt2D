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

/**
 *  @class Program
 *  @brief OpenGL Program. Use std::string as a name.
 */
class Program{
private:
    /**
     *  OpenGL Program object
     */
    GLuint programObject;
    
public:
    Program();
    ~Program();
    
    /**
     *  Create OpenGL Program with Shader
     *  @param vertex
     */
    void createProgram(Shader *vShader, Shader *fShader);
    
    /**
     *  Get program object
     *  @return Program object
     */
    GLuint getObject();
    
    /**
     *  Get attribute location
     *  @param attribName Name of attribute to find in shaders.
     */
    GLint attrib(const GLchar* attribName) const;
};

#endif /* defined(__OpenGL_2D_Framework__Program__) */
