//
//  Camera.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/10/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Camera.h"
#include <glm/gtx/transform.hpp>

Camera::Camera() :
    position(0, 0, -77.25),
    verticalAngle(0),
    horizontalAngle(0),
    fovy(50.0f),
    aspect(1280.0f/720.0f),
    nears(0.01f),
    fars(500.0f),
    speed(0.1f)
{
    
}

Camera::~Camera(){
    
}

glm::mat4 Camera::getProjection() const{
    return glm::perspective(fovy, aspect, nears, fars);
}

glm::mat4 Camera::getView() const{
    //return getOrientation() * glm::translate(glm::mat4(), position);
    glm::mat4 orient = getOrientation();
    return glm::translate(orient, position);
}

glm::mat4 Camera::getOrientation() const {
    glm::mat4 orientation;
    orientation = glm::rotate(orientation, verticalAngle, glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, horizontalAngle, glm::vec3(0,1,0));
    return orientation;
}

glm::mat4 Camera::getMatrix() const{
    return getProjection() * getView();
}

glm::vec3 Camera::getPosition() const{
    return glm::vec3(-position.x, -position.y, -position.z);
}

void Camera::setPosition(glm::vec3 position){
    this->position = position;
}

void Camera::moveFoward(){
    //inverse?
    position += glm::vec3(glm::inverse(glm::rotate(glm::mat4(), horizontalAngle, glm::vec3(0,1,0))) * glm::vec4(0,0,speed,1) );
}

void Camera::moveBackward(){
    position += glm::vec3(glm::inverse(glm::rotate(glm::mat4(), horizontalAngle, glm::vec3(0,1,0))) * glm::vec4(0,0,-speed,1) );
}

void Camera::moveRight(){
    position += glm::vec3(glm::inverse(glm::rotate(glm::mat4(), horizontalAngle, glm::vec3(0,1,0))) * glm::vec4(-speed, 0, 0,1) );
}

void Camera::moveLeft(){
    position += glm::vec3(glm::inverse(glm::rotate(glm::mat4(), horizontalAngle, glm::vec3(0,1,0))) * glm::vec4(speed, 0, 0,1) );
}

void Camera::moveUp(){
    position += glm::vec3(0, -speed, 0);
}

void Camera::moveDown(){
    position += glm::vec3(0, speed, 0);
}

void Camera::increaseSpeed(){
    if(speed < 10.0f){
        //limit max speed to 10.0f
        speed += 0.1f;
    }
}

void Camera::decreaseSpeed(){
    if(speed > 0){
        //limit max speed to 10.0f
        speed -= 0.1f;
    }
}

void Camera::changeAngle(double verticalValue, double horizontalValue){
    verticalAngle += verticalValue;
    horizontalAngle += horizontalValue;
    //normalize
    if(verticalAngle < 0.0f)
        verticalAngle += 360.0f;
    else if(verticalAngle > 360.0f)
        verticalAngle -= 360.0f;
    
    if(horizontalAngle < 0.0f)
        horizontalAngle += 360.0f;
    else if(horizontalAngle > 360.0f)
        horizontalAngle -= 360.0f;
    
//    cout << "Camera::VerticalAngle = " << verticalAngle << endl;
//    cout << "Camera::HorizontalAngle = " << horizontalAngle << endl;
}

GLfloat Camera::getVerticalAngle() const{
    return verticalAngle;
}

GLfloat Camera::getHorizontalAngle() const{
    return horizontalAngle;
}