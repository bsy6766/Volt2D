//
//  RenderableObject.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "RenderableObject.h"
#include "Director.h"

using namespace Volt2D;

RenderableObject::RenderableObject():
Object(),
bufferObject({0, 0, 0, 0}),
visible(true),
progPtr(Volt2D::Director::getInstance().getProgramPtr()),   //get default program
useSpriteSheet(false)
{
//    cout << "[SYSTEM::INFO] Creating RednerableObject" << endl;
}

RenderableObject::~RenderableObject(){
    deleteVertexData();
//    cout << "[SYSTEM::INFO] Releasing RenderableObject" << endl;
    delete boundingBox;
}

void RenderableObject::deleteVertexData(){
    vertexData.clear();
    uvVertexData.clear();
    indicesData.clear();
    
    glDeleteVertexArrays(1, &bufferObject.vao);
    glDeleteBuffers(1, &bufferObject.vbo);
    glDeleteBuffers(1, &bufferObject.uvbo);
    glDeleteBuffers(1, &bufferObject.ibo);
    
    bufferObject.vao = 0;
    bufferObject.vbo = 0;
    bufferObject.uvbo = 0;
    bufferObject.ibo = 0;
}

void RenderableObject::bindProgram(std::string programName){
    progPtr = Volt2D::Director::getInstance().getProgramPtr(programName);
}

void RenderableObject::intUniformLocation(std::string name, int& i){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    glUniform1i(uniformLocation, i);
}

void RenderableObject::floatUniformLocation(std::string name, float& f){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    glUniform1fv(uniformLocation, 1, &f);
}

void RenderableObject::boolUniformLocation(std::string name, bool b){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    if(b)
        glUniform1i(uniformLocation, 1);
    else
        glUniform1i(uniformLocation, 0);
}

void RenderableObject::vec3UniformLocation(std::string name, glm::vec3 &vec){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    glUniform3fv(uniformLocation, 1, &vec[0]);
}

void RenderableObject::matrixUniformLocation(std::string name, glm::mat4 &matrix){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
}
