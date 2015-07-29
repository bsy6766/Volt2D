//
//  Camera.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 11/10/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Camera.h"
#include "Director.h"
#include <glm/gtx/transform.hpp>

using namespace Volt2D;

Camera::Camera() :
position(0, 0, 0),
verticalAngle(0),
horizontalAngle(0),
fovy(90.0f),
aspect(1.6f),
nears(35.0f),
fars(55.0f),
speed(0.5f)
{
    /*
        fov = 90.0f;
        aspect = 1.6f;
        nears = 35.0f;
        fars = 55.0f;
     */
    
    float screenWidth = Volt2D::Director::getInstance().getWindowSize().w;
    float screenHeight = Volt2D::Director::getInstance().getWindowSize().h;
    
    //Calculate dynamically based on screen size
    float offset = screenHeight / 2.0;
    
    this->position = glm::vec3(0, 0, -offset / Volt2D::SCREEN_TO_WORLD_SCALE);
    this->aspect = (screenWidth / screenHeight);
    
    //Since this is 2D engine, we don't need to view too close and too far
    float gap = 200.0f;
    float possibleNear = (offset - gap) / Volt2D::SCREEN_TO_WORLD_SCALE;
    
    if(possibleNear < 0.01f)
        possibleNear = 0.01f;
    
    this->nears = possibleNear;
    this->fars = (offset + gap) / Volt2D::SCREEN_TO_WORLD_SCALE;
    
    cout << "[SYSTEM::INFO] Creating Main Camera." << endl;
    cout << "[SYSTEM::INFO] Position = (" << this->position.x << ", " << this->position.y << ", " << this->position.z << ")" << endl;
    cout << "[SYSTEM::INFO] LookAt = (0, 0, 0)" << endl;
    cout << "[SYSTEM::INFO] fovy = 90.0f (Fixed)" << endl;
    cout << "[SYSTEM::INFO] aspect ratio = " << this->aspect << endl;
    cout << "[SYSTEM::INFO] near clip pane = " << this->nears << endl;
    cout << "[SYSTEM::INFO] far clip pane = " << this->fars << endl << endl;
}

Camera* Camera::createCamera(){
    //nothing really to initialize here.
    return new Camera();
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
}

GLfloat Camera::getVerticalAngle() const{
    return verticalAngle;
}

GLfloat Camera::getHorizontalAngle() const{
    return horizontalAngle;
}