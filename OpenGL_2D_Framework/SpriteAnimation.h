//
//  SpriteAnimation.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteAnimation__
#define __OpenGL_2D_Framework__SpriteAnimation__

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
    
    //frame variable
    int frameListSize;
    int currentFrameIndex;
    
    //time
    double frameInterval;
    double currentTime;
    double totalElapsedTime;
    
    //pure virtual
    void createVertexData();
    void loadVertexData();
    void render();
    
    void updateMatrix();
    
public:
    SpriteAnimation();
    SpriteAnimation(Program *progPtr);
    ~SpriteAnimation();
    
    //temporary
    bool canJump;
    
    //use Timer class for elapsed time
    void updateFrame();
    
    void init(std::string fileName, std::string stateName, int frameSize, double interval);
};

#endif /* defined(__OpenGL_2D_Framework__SpriteAnimation__) */
