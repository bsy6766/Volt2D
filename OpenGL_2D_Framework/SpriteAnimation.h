//
//  SpriteAnimation.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__SpriteAnimation__
#define __CS364FinalProject__SpriteAnimation__

#include "Texture.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SpriteObject.h"

#include "Timer.h"
#include "Program.h"

class SpriteAnimation : public SpriteObject{
private:
    std::vector<Texture *> textureList;
    
    double frameInterval;
    int frameListSize;
    int currentFrameIndex;
    double currentTime;
    double totalElapsedTime;
    
    //pure virtual
    void createVertexData();
    void loadVertexData();
    void release();
    void updateMatrix();
    void render();
    
public:
    SpriteAnimation();
    SpriteAnimation(Program *progPtr);
    ~SpriteAnimation();
    
    bool canJump;
    void updateFrame();

    
    void init(std::string fileName, std::string stateName, int frameSize, double interval);
};

#endif /* defined(__CS364FinalProject__SpriteAnimation__) */
