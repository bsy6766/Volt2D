//
//  Shader.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Shader.h"

using namespace Volt2D;

Shader::Shader(){
    shaderObject = 0;
}

Shader::~Shader(){
    shaderObject = 0;
}

Shader* Shader::createShader(const std::string filePath, GLenum shaderType){
    Shader* newShader = new Shader();
    newShader->loadShader(filePath, shaderType);
    return newShader;
}

void Shader::loadShader(const std::string filePath, GLenum shaderType){
    std::string sourceCode = shaderCodeFromFile(filePath);
    
    shaderObject = glCreateShader(shaderType);
    
    if(shaderObject == 0){
        throw std::runtime_error("glCreateShader failed");
    }
    
    //set source of shader
    const char* code = sourceCode.c_str();
    glShaderSource(shaderObject, 1, (const GLchar **) &code, NULL);
    
    //compile vertex shader
    glCompileShader(shaderObject);
    
    //get status of shader compiler(?)
    GLint status;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
    //if failed,
    if(status == GL_FALSE){
        std::string msg("Compile failure in vertex shader:\n");
        
        GLint infoLogLength;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(shaderObject, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        throw std::runtime_error(msg);
    }
}

std::string Shader::shaderCodeFromFile(const std::string filePath){
    std::ifstream fs;
    fs.open(filePath.c_str(), std::ios::in | std::ios::binary);
    
    if(!fs.is_open()){
        throw std::runtime_error(std::string("Failed to open file: ") + filePath);
    }
    
    std::stringstream buffer;
    buffer << fs.rdbuf();
    
    return buffer.str();
}

GLuint Shader::getObject(){
    return shaderObject;
}