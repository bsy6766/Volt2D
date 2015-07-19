//
//  ProgressBar.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/23/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressBar__
#define __OpenGL_2D_Framework__ProgressBar__

#include "CommonInclude.h"
#include "ProgressObject.h"

class ProgressBar: public ProgressObject{
private:
    //private constructor
    ProgressBar();
    void initProgressBar(GLenum textureTarget, const std::string barTextureName);
public:
    /**
     *  Create ProgressBar
     *  @param objectName An object name for ProgressBar
     *  @param barTextureName Texture file name 
     *  @param textureTarget GL_TEXTURE_2D
     */
    static ProgressBar* createProgressBar(std::string objectName, const char* barTextureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    //Destructor
    ~ProgressBar();
    
    /**
     *  Override's RenderableObject::computerVertexData()
     */
    virtual void computeVertexData();
    
    /**
     *
     */
    virtual void loadVertexData();
    
    /**
     *
     */
    virtual void render();
};

#endif /* defined(__OpenGL_2D_Framework__ProgressBar__) */
