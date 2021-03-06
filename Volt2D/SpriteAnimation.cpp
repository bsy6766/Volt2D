//
//  SpriteAnimation.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteAnimation.h"
#include "Director.h"
#include "Timer.h"

using namespace Volt2D;

SpriteAnimation::SpriteAnimation():
RenderableObject(),
runningAnimationName("")
{
    this->progPtr = Volt2D::Director::getInstance().getProgramPtr("SpriteAnimation");
}

SpriteAnimation::~SpriteAnimation(){
    auto it = animationMap.begin();
    //First buffer object is released by Renderable Object
    //just delete texture array
    delete (it->second).textureAtlas;
    //next
    it++;
    
    for(; it != animationMap.end(); it++){
        glDeleteVertexArrays(1, &(it->second).bufferObject.vao);
        glDeleteBuffers(1, &(it->second).bufferObject.vbo);
        glDeleteBuffers(1, &(it->second).bufferObject.uvbo);
        glDeleteBuffers(1, &(it->second).bufferObject.ibo);
        
        delete (it->second).textureAtlas;
    }
}

SpriteAnimation* SpriteAnimation::create(string objectName){
    SpriteAnimation* newSpriteAnimation = new SpriteAnimation();
    newSpriteAnimation->setName(objectName);
    return newSpriteAnimation;
}

SpriteAnimation* SpriteAnimation::createWithAnimation(string objectName,
                                                      string animationName,
                                                      string textureName,
                                                      int frameSize,
                                                      double frameInterval)
{
    //check frame size. reject with
    if(frameSize <= 0){
        cout << "[SYSTEM::ERROR] SpriteAnimation must have at least one frame." << endl;
        return nullptr;
    }
    else{
        SpriteAnimation* newSpriteAnimation = new SpriteAnimation();
        if(frameInterval < 0){
            cout << "[SYSTEM::WARNING] SpriteAnimation can not have frame interval less than 0. Setting to minimum value 0.01f" << endl;
            frameInterval = 0.01f;
        }
        
        if(newSpriteAnimation->initWithAnimation(animationName, textureName, frameSize, frameInterval)){
            newSpriteAnimation->setName(objectName);
            return newSpriteAnimation;
        }
        else{
            cout << "[SYSTEM::ERROR] Failed to initialize SpriteAnimation \"" << objectName << "\"." << endl;
            return nullptr;
        }
    }
}

bool SpriteAnimation::initWithAnimation(string name, string textureName, int size, double interval){
    //create new animation data and initialize it.
    Animation na;
    na.name = name;
    na.size = size;
    na.currentFrameIndex = 0;
    na.interval = interval;
    na.bufferObject.vao = -1;
    na.bufferObject.vbo = -1;
    na.bufferObject.uvbo = -1;
    na.bufferObject.ibo = -1;
    na.textureAtlas = 0;
    na.intervalCounter = 0;
    na.vertexData.clear();
    na.uvVertexData.clear();
    na.indicesData.clear();
    
    //Create texture array.
    Texture* animationTextureAtlas = Texture::create2DTextureArrayWithFiles(textureName, size);
    int texW, texH;
    animationTextureAtlas->getTextureSize(texW, texH);
    
    //check
    assert(animationTextureAtlas != nullptr);
    
    //store texture
    na.textureAtlas = animationTextureAtlas;
    
    //get ImageSize. Texture class will return the size from most first image that was loaded for this animation (== <file name>_1's size)
    int imgW, imgH;
    animationTextureAtlas->getImageSize(imgW, imgH);
    //compute vertex data.
    computeVertexData((float)texW, (float)texH, (float)imgW, (float)imgH, na);
    
    //load vertex data to animation
    loadVertexData(na);
    
    this->boundingBox = new Volt2D::BoundingBox(-na.textureWidth/2, -na.textureHeight/2, na.textureWidth/2, na.textureHeight/2);
    
    //save animation data
    animationMap[name] = na;
    
    this->runningAnimationName = name;
    
    return true;
}

void SpriteAnimation::computeVertexData(float texW, float texH, float imgW, float imgH, Animation& ani){
    //compute vertex size that will be render in screen
    float width = imgW / Volt2D::SCREEN_TO_WORLD_SCALE;
    float height = imgH / Volt2D::SCREEN_TO_WORLD_SCALE;
    
    //store above size
    this->Object::scaledWidth = width;
    this->Object::scaledHeight = height;
    
    ani.textureHeight = texH;
    ani.textureWidth = texW;
    
    if(animationMap.empty()){
        vertexData.push_back(glm::vec3(-(width/2), -(height/2), Volt2D::GLOBAL_Z_VALUE));
        vertexData.push_back(glm::vec3(-(width/2), height/2, Volt2D::GLOBAL_Z_VALUE));
        vertexData.push_back(glm::vec3(width/2, -(height/2), Volt2D::GLOBAL_Z_VALUE));
        vertexData.push_back(glm::vec3(width/2, height/2, Volt2D::GLOBAL_Z_VALUE));
        
        uvVertexData.push_back(glm::vec2(0, (imgH / texH)));
        uvVertexData.push_back(glm::vec2(0, 0));
        uvVertexData.push_back(glm::vec2((imgW / texW), (imgH / texH)));
        uvVertexData.push_back(glm::vec2((imgW / texW), 0));
        
        indicesData.push_back(0);
        indicesData.push_back(1);
        indicesData.push_back(2);
        indicesData.push_back(1);
        indicesData.push_back(2);
        indicesData.push_back(3);
        
        ani.vertexData = vertexData;
        ani.uvVertexData = uvVertexData;
        ani.indicesData = indicesData;
    }
    else{
        ani.vertexData.push_back(glm::vec3(-(width/2), -(height/2), Volt2D::GLOBAL_Z_VALUE));
        ani.vertexData.push_back(glm::vec3(-(width/2), height/2, Volt2D::GLOBAL_Z_VALUE));
        ani.vertexData.push_back(glm::vec3(width/2, -(height/2), Volt2D::GLOBAL_Z_VALUE));
        ani.vertexData.push_back(glm::vec3(width/2, height/2, Volt2D::GLOBAL_Z_VALUE));
        
        ani.uvVertexData.push_back(glm::vec2(0, (imgH / texH)));
        ani.uvVertexData.push_back(glm::vec2(0, 0));
        ani.uvVertexData.push_back(glm::vec2((imgW / texW), (imgH / texH)));
        ani.uvVertexData.push_back(glm::vec2((imgW / texW), 0));
        
        ani.indicesData.push_back(0);
        ani.indicesData.push_back(1);
        ani.indicesData.push_back(2);
        ani.indicesData.push_back(1);
        ani.indicesData.push_back(2);
        ani.indicesData.push_back(3);
    }
}

void SpriteAnimation::addAnimation(std::string name, string textureName, int frameSize, double frameInterval){
    //new animation
    Animation na;
    na.name = name;
    na.size = frameSize;
    na.currentFrameIndex = 0;
    na.interval = frameInterval;
    na.bufferObject.vao = -1;
    na.bufferObject.vbo = -1;
    na.bufferObject.uvbo = -1;
    na.bufferObject.ibo = -1;
    na.textureAtlas = 0;
    na.intervalCounter = 0;
    
    //new texture
    Texture* animationTextureAtlas = Texture::create2DTextureArrayWithFiles(textureName, frameSize);
    int texW, texH;
    animationTextureAtlas->getTextureSize(texW, texH);
    
    //check
    assert(animationTextureAtlas != nullptr);
    
    //store texture
    na.textureAtlas = animationTextureAtlas;
    
    if(animationMap.empty()){
        this->runningAnimationName = name;
    }
    
    int imgW, imgH;
    animationTextureAtlas->getImageSize(imgW, imgH);
    //compute vertex data.
    computeVertexData((float)texW, (float)texH, (float)imgW, (float)imgH, na);
    
    //load vertex data to animation
    loadVertexData(na);
    
    //save animation data
    animationMap[name] = na;
}

void SpriteAnimation::loadVertexData(Animation& ani){
    //build pointer to objects
    GLuint* vao;
    GLuint* vbo;
    GLuint* uvbo;
    GLuint* ibo;
    bool empty = animationMap.empty();
    //if there is no animation yet, use RenderableObject's BufferObject and copy to here
    if(empty){
        vao = &(this->bufferObject.vao);
        vbo = &(this->bufferObject.vbo);
        uvbo = &(this->bufferObject.uvbo);
        ibo = &(this->bufferObject.ibo);
    }
    //else,
    else{
        vao = &(ani.bufferObject.vao);
        vbo = &(ani.bufferObject.vbo);
        uvbo = &(ani.bufferObject.uvbo);
        ibo = &(ani.bufferObject.ibo);
    }
    
    //generate vertex array object and bind it
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);
    
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * ani.vertexData.size(), &ani.vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glGenBuffers(1, uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, *uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * ani.uvVertexData.size(), &ani.uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glGenBuffers(1, ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * ani.indicesData.size(), &ani.indicesData[0], GL_STATIC_DRAW);
    
    ani.bufferObject = BufferObject({*vao, *vbo, *uvbo, *ibo});
    
    glBindVertexArray(0);
}

void SpriteAnimation::render(){
    if(!visible){
        return;
    }
    
    //return if object runs no animation
    if(runningAnimationName.empty()){
        return;
    }
    
    //find animation
    auto ani_it = animationMap.find(runningAnimationName);
    if(ani_it == animationMap.end()){
        //if can't find animation, return
        return;
    }
    
    //if texture doesn't exist for this animation, don't render
    if(!(ani_it->second).textureAtlas){
        return;
    }
    
    //bind program
    glUseProgram(progPtr->getObject());
    
    double elapsedTime = Volt2D::Timer::getInstance().getElapsedTime();
    (ani_it->second).intervalCounter += elapsedTime;
    
    int currentFrameIndex = (ani_it->second).currentFrameIndex;
    
    if((ani_it->second).intervalCounter >= (ani_it->second).interval){
        (ani_it->second).intervalCounter -= (ani_it->second).interval;
        currentFrameIndex++;
        (ani_it->second).currentFrameIndex = currentFrameIndex;
        if((ani_it->second).currentFrameIndex >= (ani_it->second).size){
            (ani_it->second).currentFrameIndex = 0;
        }
    }
    
    //check texture
    if((ani_it->second).textureAtlas->canBoundThisTexture()){
        (ani_it->second).textureAtlas->bindArray();
    }
    
    //camera
    const glm::mat4 cameraMat = Volt2D::Director::getInstance().getProjectiveViewMatrix();
    matrixUniformLocation("cameraMat", cameraMat);
    
    glm::mat4 parentMat = glm::mat4();
    if(this->parent)
        parentMat = this->parent->getTransformMat();
    
    matrixUniformLocation("parentMat", parentMat);
    matrixUniformLocation("modelMat", modelMat);
    matrixUniformLocation("rotateMat", rotateMat);
    matrixUniformLocation("translateMat", translateMat);
    matrixUniformLocation("scaleMat", scaleMat);
    floatUniformLocation("opacity", opacity);
    intUniformLocation("layer", currentFrameIndex);
    
    //bind vertex array.
    glBindVertexArray((ani_it->second).bufferObject.vao);
    
    //enable attribs
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
    
    //draw based on indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void SpriteAnimation::playAnimation(string name){
    this->stopAnimation();
    this->runningAnimationName = name;
}

std::string SpriteAnimation::getPlayingAnimationName(){
    return this->runningAnimationName;
}

void SpriteAnimation::stopAnimation(){
    auto animation = animationMap[this->runningAnimationName];
    animation.currentFrameIndex = 0;
    animation.intervalCounter = 0;
    this->runningAnimationName.clear();
}















// :)