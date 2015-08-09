//
//  Program.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 11/8/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Program.h"

using namespace Volt2D;

Program::Program(Shader* vShader, Shader* fShader):
programObject(0)
{
    //create opengl program and get object id
    programObject = glCreateProgram();
    
    //throw error if failes
    if(programObject == 0)
        throw std::runtime_error("glCreateProgram failed");
    
    //attch vshader and fshader
    glAttachShader(programObject, vShader->getObject());
    glAttachShader(programObject, fShader->getObject());
    
    //link the program. error check at below
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
}

Program::~Program(){
    programObject = 0;
}

Program* Program::createProgram(Volt2D::Shader *vShader, Volt2D::Shader *fShader){
    //pre check
    assert(vShader != nullptr);
    assert(fShader != nullptr);
    return new Program(vShader, fShader);
}

GLuint Program::getObject(){
    //return object
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