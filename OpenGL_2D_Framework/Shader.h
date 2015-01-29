//
//  Shader.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Shader__
#define __OpenGL_2D_Framework__Shader__

#include <GL/glew.h>
#include <stdexcept>
#include <string>
#include <fstream>	//file
#include <sstream>	//string stream

/**
 * This Shader class was created during 2014 summer break.
 * It loads shader.
 */

class Shader{
private:
    GLuint shaderObject;
    
    /**
     * load the shader.
     * gets source code as string and compiles.
     * leaves error log if fails to compile shader
     * todo: change to exception.
     */
    void loadShader(const std::string& sourceCode, GLenum shaderType);
    
    /**
     * load shader code and return as string
     * get the file path
     */
    std::string shaderCodeFromFile(const std::string& filePath);
    
    
public:
    Shader();
    ~Shader();
    
    /**
     * create the shader
     * basically calls loadShader()...
     */
    void createShader(const std::string& filePath, GLenum shaderType);
    
    /**
     * shader object getter
     */
    GLuint getObject();
};

#endif /* defined(__OpenGL_2D_Framework__Shader__) */
