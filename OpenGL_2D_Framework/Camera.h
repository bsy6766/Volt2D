//
//  Camera.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/10/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Camera__
#define __OpenGL_2D_Framework__Camera__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CommonInclude.h"

/**
 * This Camera class was created during 2014 summer break.
 */

class Camera{
private:
    glm::vec3 position;
    
    //camera variables
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
    
    //getters
    glm::mat4 getProjection() const;
    glm::mat4 getMatrix() const;
    glm::mat4 getView() const;
    glm::mat4 getOrientation() const;
    glm::vec3 getPosition() const;
    GLfloat getVerticalAngle() const;
    GLfloat getHorizontalAngle() const;
    
    void setPosition(glm::vec3 position);
    
    //movement functions
    void moveFoward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    
    void changeAngle(double verticalValue, double horizontalValue);
    
    //speed
    void increaseSpeed();
    void decreaseSpeed();
};

#endif /* defined(__OpenGL_2D_Framework__Camera__) */
