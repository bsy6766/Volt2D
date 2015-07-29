//
//  Shader.h
//  Volt2D
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Shader__
#define __Volt2D__Shader__

#include <GL/glew.h>
#include <stdexcept>
#include <string>
#include <fstream>	//file
#include <sstream>	//string stream

namespace Volt2D{
/**
 *  @class Shader
 *  @brief Load shader and compile
 */
class Shader{
private:
    /**
     *  private constructor
     */
    Shader();
    
    /**
     *  OpenGL Shader object
     */
    GLuint shaderObject;
    
    /**
     * load the shader.
     * gets source code as string and compiles.
     * leaves error log if fails to compile shader
     * todo: change to exception.
     */
    void loadShader(const std::string filePath, GLenum shaderType);
    
    /**
     * load shader code and return as string
     * get the file path
     */
    std::string shaderCodeFromFile(const std::string filePath);
    
public:
    ~Shader();
    
    /**
     * create the shader
     */
    static Shader* createShader(const std::string filePath, GLenum shaderType);
    
    /**
     * shader object getter
     */
    GLuint getObject();
};
}   //namespace end

#endif /* defined(__Volt2D__Shader__) */
