//
//  Camera.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/10/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__Camera__
#define __CS364FinalProject__Camera__

#include <GL/glew.h>
#include <glm/glm.hpp>

class Camera{
private:
    glm::vec3 position;
    
    GLfloat fovy;
    GLfloat aspect;
    GLfloat nears;
    GLfloat fars;
    GLfloat verticalAngle, horizontalAngle;
    GLfloat speed;
    
public:
    //Camera's default data is set to screen size of 1280 x 800
    Camera();
    Camera(glm::vec3 position, float vAngle, float hAngle, float fovy, float aspect, float nears, float fars, float speed);
    ~Camera();
    
    glm::mat4 getProjection() const;
    glm::mat4 getMatrix() const;
    glm::mat4 getView() const;
    glm::mat4 getOrientation() const;
    glm::vec3 getPosition() const;
    void setPosition(glm::vec3 position);
    void moveFoward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void changeAngle(double verticalValue, double horizontalValue);
    void increaseSpeed();
    void decreaseSpeed();
};

#endif /* defined(__CS364FinalProject__Camera__) */
