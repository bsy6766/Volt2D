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
#include "Utility.hpp"

namespace Volt2D{
/**
 *  @class Program
 *  @brief OpenGL Program. Use std::string as a name.
 */
class Program{
private:
    //private constructor
    Program(Shader* vShader, Shader* fShader);
    
    /**
     *  OpenGL Program object
     */
    GLuint programObject;
    
public:
    //Destructor
    ~Program();
    
    /**
     *  Create OpenGL Program with Shader
     *  @param vShader Vertex shader
     *  @param fShader Fragment shader
     *  @return New program object attached with shaders.
     */
    static Program* createProgram(Volt2D::Shader *vShader, Volt2D::Shader *fShader);
    
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
}   //namespace end

#endif /* defined(__OpenGL_2D_Framework__Program__) */
