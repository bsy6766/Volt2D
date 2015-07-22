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
#include <glm/glm.hpp>
#include "CommonInclude.h"
#include "SpriteObject.h"

#include "Timer.h"
#include "Program.h"

class SpriteAnimation : public SpriteObject{
private:
    Texture* texture;
    
    //frame variable
    int frameListSize;
    int currentFrameIndex;
    
    //time
    double frameInterval;
    double currentTime;
    double totalElapsedTime;
    
    /**
     *  Override's RenderableObject::computerVertexData()
     *  Compute vertex and indices
     */
    virtual void computeVertexData();
    
    /**
     *  Override's RenderableObject::loadVertexData()
     *  Load computed vertex.
     */
    virtual void loadVertexData();
    
    /**
     *  Overrides's Object::render();
     *  Render object
     */
    virtual void render();
    
    //private structor
    SpriteAnimation();
    
    /**
     *
     */
    void init(std::string fileName, std::string stateName, int frameSize, double interval);
    
public:
    static SpriteAnimation* createSpriteAnimation(std::string objectName, std::string textureName, int frameSize, double frameInterval);
    
    //Destructor
    ~SpriteAnimation();
};

#endif /* defined(__OpenGL_2D_Framework__SpriteAnimation__) */
