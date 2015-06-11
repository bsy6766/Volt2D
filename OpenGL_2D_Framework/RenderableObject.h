//
//  RenderableObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__RenderableObject__
#define __OpenGL_2D_Framework__RenderableObject__

//#define GLM_FORCE_RADIANS

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
    
    BoundingBox* boundingBox;
    
private:
    //check the boundary of scale value and limit to -1.0~1.0
    void checkScale(glm::vec3& scale);
public:
    RenderableObject();
    virtual ~RenderableObject();
    
    virtual void setPosition(glm::vec3 position);
    virtual void addPosition(glm::vec3 position);
    
    //To transformation
    void rotateTo(GLfloat angle, glm::vec3 axis);
    void scaleTo(glm::vec3 scale);
    void translateTo(glm::vec3 position);
    
    //By transformation
    void rotateBy(GLfloat angle, glm::vec3 axis);
    void scaleBy(glm::vec3 scale);
    void translateBy(glm::vec3 distance);
    
    //Angle getter setter
    void setAngle(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1));
    void addAngle(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1));
    void wrapAngle(GLfloat& angle);
    GLfloat getAngle();
    
    //opacity getter setter
    void setOpacity(GLfloat opacity);
    GLfloat getOpacity();
    
    //scale
    GLfloat getScaleX();
    GLfloat getScaleY();
    GLfloat getScaleZ();
    glm::vec3 getScale();
    
    virtual void computeVertexData() = 0;
    virtual void loadVertexData() = 0;
    virtual void render() = 0;
    
    //clear vertex std::vectors and delete buffer.
    void deleteVertexData();
    void initBoundingBox(int w, int h);
};

#endif /* defined(__OpenGL_2D_Framework__RenderableObject__) */
