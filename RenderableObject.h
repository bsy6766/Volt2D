//
//  RenderableObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__RenderableObject__
#define __OpenGL_2D_Framework__RenderableObject__

#include "Object.h"
#include "BoundingBox.h"
#include <vector>
#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

class RenderableObject : public Object{
protected:
    GLuint vao;		//vertex array object
    GLuint vbo;		//vertex buffer object
    GLuint uvbo;	//uv vert buffer object
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
    
    //0 ~ 360 degree
    GLfloat angle;
    //x,y,z. -1.0 ~ 1.0
    glm::vec3 scale;
    //0~255
    GLfloat opacity;
    
    BoundingBox* bBox;
    
private:
    void setAngle(GLfloat angle);
    //check the boundary of scale value and limit to -1.0~1.0
    void checkScale(glm::vec3& scale);
public:
    RenderableObject();
    virtual ~RenderableObject();
    
    //To transformation
    void rotateTo(GLfloat angle, glm::vec3 axis);
    void scaleTo(glm::vec3 scale);
    void translateTo(glm::vec3 position);
    
    //By transformation
    void rotateBy(GLfloat angle, glm::vec3 axis);
    void scaleBy(glm::vec3 scale);
    void translateBy(glm::vec3 distance);
    
    //opacity
    void setOpacity(GLfloat opacity);
    GLfloat getOpacity();
    
    virtual void computeVertexData() = 0;
    virtual void loadVertexData() = 0;
    virtual void render() = 0;
    
    //clear vertex std::vectors and delete buffer.
    void deleteVertexData();
};

#endif /* defined(__OpenGL_2D_Framework__RenderableObject__) */
