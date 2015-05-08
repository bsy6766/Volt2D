//
//  TextObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__TextObject__
#define __OpenGL_2D_Framework__TextObject__

#include <glm/glm.hpp>
#include "CommonInclude.h"
#include <GL/glew.h>
#include <vector>
#include <string>

class TextObject{
protected:
    //    int spriteID;
    //
    //    int w;
    //    int h;
    //
    //    glm::vec2 position;
    //    Program *progPtr;
    //
    //    bool actionRunning;
    //    float z;    //each sprite can set 0~100.
    //
    //    BoundingBox* boundingBox;
    bool visible;
    
    GLuint vao;		//vertex array object
    GLuint vbo;		//vertex buffer object
    GLuint uvbo;	//uv vert buffer object
    GLuint textbo;  //texture buffer object
    GLuint ibo;		//indices buffer object
    
    //OpenGL Matrix
    glm::mat4 translateMat;
    glm::mat4 rotateMat;
    glm::mat4 scaleMat;
    glm::mat4 modelMat;
    
    //vertex, texture coordinate and index data
    std::vector<glm::vec3> vertexData;
    std::vector<glm::vec2> uvVertexData;
    std::vector<GLushort> indicesData;
private:
public:
    TextObject();
    virtual ~TextObject();
};

#endif /* defined(__OpenGL_2D_Framework__TextObject__) */
