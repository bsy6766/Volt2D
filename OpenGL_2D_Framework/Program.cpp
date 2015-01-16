//
//  Program.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/8/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "Program.h"

Program::Program(){
    programObject = 0;
}

Program::~Program(){
    programObject = 0;
}

void Program::createProgram(Shader *vertexShaderPtr, Shader *fragmentShaderPtr){
    programObject = glCreateProgram();
    
    if(programObject == 0)
        throw std::runtime_error("glCreateProgram failed");
    
    glAttachShader(programObject, vertexShaderPtr->getObject());
    glAttachShader(programObject, fragmentShaderPtr->getObject());
    
    glLinkProgram(programObject);
    
    //throw exception if linking failed
    GLint status;
    glGetProgramiv(programObject, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Program linking failure: ");
        
        GLint infoLogLength;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(programObject, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        
        glDeleteProgram(programObject);
        programObject = 0;
        throw std::runtime_error(msg);
    }
    
    //set attrib location
}

GLuint Program::getObject(){
    return programObject;
}

GLint Program::attrib(const GLchar* attribName) const {
    if(!attribName)
        throw std::runtime_error("attribName was NULL");
    
    GLint attrib = glGetAttribLocation(programObject, attribName);
    if(attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);
    
    return attrib;
}