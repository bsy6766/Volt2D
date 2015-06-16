//
//  RenderableObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "RenderableObject.h"

RenderableObject::RenderableObject():
Object(),
vao(0),
vbo(0),
uvbo(0),
ibo(0),
translateMat(glm::mat4()),
rotateMat(glm::mat4()),
scaleMat(glm::mat4()),
modelMat(glm::mat4()),
angle(0),
scale(glm::vec3(1, 1, 1)),
opacity(255),
boundingBox(new BoundingBox())
{
    cout << "RenderableObject::RenderableObject()" << endl;
    translateTo(position);
    rotateTo(angle, glm::vec3(0, 0, 1));
    scaleTo(scale);
    setOpacity(opacity);
}

RenderableObject::~RenderableObject(){
    deleteVertexData();
    cout << "Deleting Renderable Object" << endl;
    delete boundingBox;
}

void RenderableObject::setPosition(glm::vec3 position){
    translateTo(position);
}

void RenderableObject::addPosition(glm::vec3 position){
    translateBy(position);
}

void RenderableObject::translateTo(glm::vec3 position){
    this->position = position;
    translateMat = glm::translate(glm::mat4(), position);
}

void RenderableObject::translateBy(glm::vec3 distance){
    this->position += distance;
    translateMat = glm::translate(translateMat, distance);
}

void RenderableObject::setAngle(GLfloat angle, glm::vec3 axis){
    angle *= (-1);
    rotateTo(angle, axis);
}

void RenderableObject::addAngle(GLfloat angle, glm::vec3 axis){
    angle *= (-1);
    rotateBy(angle, axis);
}

void RenderableObject::wrapAngle(GLfloat& angle){
    if(angle < 0)
        angle += 360;
    else if(angle > 360)
        angle -= 360;
    else if(angle == 360)
        angle = 0;
}

GLfloat RenderableObject::getAngle(){
    return this->angle;
}

void RenderableObject::rotateTo(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1)){
    //rotate in 2d space by default
    wrapAngle(angle);
    rotateMat = glm::rotate(glm::mat4(), angle, axis);
    this->angle = angle;
//    wrapAngle(this->angle);
}

void RenderableObject::rotateBy(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1)){
    //rotate in 2D space by default
    this->angle += angle;
    wrapAngle(this->angle);
    rotateMat = glm::rotate(rotateMat, angle, axis);
}

glm::vec3 RenderableObject::getScale(){
    return this->scale;
}

GLfloat RenderableObject::getScaleX(){
    return scale.x;
}

GLfloat RenderableObject::getScaleY(){
    return scale.y;
}

GLfloat RenderableObject::getScaleZ(){
    return scale.z;
}

void RenderableObject::setScale(glm::vec3 scale){
    scaleTo(scale);
}

void RenderableObject::addScale(glm::vec3 scale){
    scaleBy(scale);
}

void RenderableObject::scaleTo(glm::vec3 scale){
    this->scale = scale;
    scaleMat = glm::scale(glm::mat4(), scale);
}

void RenderableObject::scaleBy(glm::vec3 scale){
    this->scale += scale;
    scaleMat = glm::scale(glm::mat4(), this->scale);
}

void RenderableObject::setOpacity(GLfloat opacity){
    if(opacity < 0)
        opacity = 0;
    else if(opacity > 255)
        opacity = 255;
    
    this->opacity = opacity;
}

void RenderableObject::addOpacity(GLfloat opacity){
    this->opacity += opacity;
    
    if(this->opacity < 0)
        this->opacity = 0;
    else if(this->opacity > 255)
        this->opacity = 255;
}

GLfloat RenderableObject::getOpacity(){
    return this->opacity;
}

void RenderableObject::deleteVertexData(){
    vertexData.clear();
    uvVertexData.clear();
    indicesData.clear();
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uvbo);
    glDeleteBuffers(1, &ibo);
    
    vao = 0;
    vbo = 0;
    uvbo = 0;
    ibo = 0;
}

void RenderableObject::initBoundingBox(int w, int h){
    boundingBox->w = w;
    boundingBox->h = h;
    boundingBox->x = ((-1) * w) / 2;
    boundingBox->y = ((-1) * h) / 2;
}