//
//  SpriteAnimation.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteAnimation.h"
#include <iostream>
#include "Director.h"

SpriteAnimation::SpriteAnimation():
SpriteObject()
{
//    this->frameInterval = 0;
//    this->currentTime = 0;
//    this->currentFrameIndex = 0;
//    this->frameListSize = 0;
//    this->totalElapsedTime = 0;
}

SpriteAnimation::~SpriteAnimation(){
    
}

SpriteAnimation* SpriteAnimation::createSpriteAnimation(std::string objectName, std::string textureName, int frameSize, double frameInterval){
    SpriteAnimation* newSpriteAnimation = new SpriteAnimation();
//
    return newSpriteAnimation;
    return 0;
}

void SpriteAnimation::init(std::string fileName, std::string stateName, int frameSize, double interval){
//    //file name format must be followed. Not going to check the file name format for now
//    //if frame size is 0, return. this isn't spriate animation
//    if(frameSize == 0)
//        return;
//    
//    for(int i = 0; i<frameSize; i++){
//        //set texture
//        std::string textureFileName = fileName + "_" + std::to_string(i+1) + ".png";
//        //defualt path. This is hard coded!!!!!!!!
//        std::string path = "../Texture/animation/run/" + textureFileName;
//        Texture *tex = new Texture(GL_TEXTURE_2D, path);
//        tex->load();
//        textureList.push_back(tex);
//    }
//    
//    this->frameInterval = interval;
//    this->visible = true;
//    this->frameListSize = frameSize;
//    
//    //all texture must be same size
//    textureList.at(0)->getImageSize(this->w, this->h);
//    
//    createVertexData();
//    loadVertexData();
}

void SpriteAnimation::computeVertexData(){
//    //note: scale redefined
//    float width = w / 10;
//    float height = h / 10;
//    
////    z = GLOBAL_Z_VALUE;
//    
//    vertexData.push_back(glm::vec3(-(width/2), -(height/2), GLOBAL_Z_VALUE));
//    vertexData.push_back(glm::vec3(-(width/2), height/2, GLOBAL_Z_VALUE));
//    vertexData.push_back(glm::vec3(width/2, -(height/2), GLOBAL_Z_VALUE));
//    vertexData.push_back(glm::vec3(width/2, height/2, GLOBAL_Z_VALUE));
//    
//    uvVertexData.push_back(glm::vec2(0, 0));
//    uvVertexData.push_back(glm::vec2(0, 1));
//    uvVertexData.push_back(glm::vec2(1, 0));
//    uvVertexData.push_back(glm::vec2(1, 1));
//    
//    indicesData.push_back(0);
//    indicesData.push_back(1);
//    indicesData.push_back(2);
//    indicesData.push_back(1);
//    indicesData.push_back(2);
//    indicesData.push_back(3);
}

void SpriteAnimation::loadVertexData(){
    //generate vertex array object and bind it
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

//void SpriteAnimation::updateFrame(){
//    double elapsedTime = Timer::getInstance().getElapsedTime();
//    double nextTime = currentTime + elapsedTime;
//    if(elapsedTime < 0)
//        return;
//    
//    if(nextTime > frameInterval){
//        //display next frame
//        currentFrameIndex++;
//
//        if(currentFrameIndex >= frameListSize){
//            currentFrameIndex = 0;
//        }
//        currentTime = nextTime;
//        currentTime -= frameInterval;
//    }
//    else{
//        currentTime = nextTime;
//    }
//}

void SpriteAnimation::render(){
//    textureList.at(currentFrameIndex)->bind(GL_TEXTURE0);
//    
//    GLint modelUniformLocation = glGetUniformLocation(progPtr->getObject(), "modelMat");
//    if(modelUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "modelMat");
//    
////    if(actionRunning)
////        updateFromSpriteAction();
//    
//    updateMatrix();
//    
//    translateMat = glm::translate(glm::mat4(), glm::vec3((position.x - 640) / 10, (position.y - 360) / 10, 0));
//    
//    glm::mat4 parentMat = glm::mat4();
//    if(this->parent)
//        parentMat = this->parent->getTransformMat();
////    glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, &parentMat[0][0]);
//    
//    matrixUniformLocation("parentMat", parentMat);
//    matrixUniformLocation("modelMat", modelMat);
//    
//    GLint opacityUniformLocation = glGetUniformLocation(progPtr->getObject(), "opacity");
//    if(opacityUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "opacity");
//    glUniform1fv(opacityUniformLocation, 1, &opacity);
//    
//    GLint particleUniformLocation = glGetUniformLocation(progPtr->getObject(), "particle");
//    if(particleUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "opacity");
//    glUniform1i(particleUniformLocation, 0);
//    
//    glBindVertexArray(vao);
//    glEnableVertexAttribArray(progPtr->attrib("vert"));
//    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}