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

/**
 *  @class ProgressBar
 *  @brief Textured progress bar
 */
class ProgressBar: public ProgressObject{
private:
    //private constructor
    ProgressBar();
    
    /**
     *  Initialize ProgressBar
     *  @param textureTarget GL_TEXTURE_2D
     */
    void initProgressBar(const std::string barTextureName, GLenum textureTarget = GL_TEXTURE_2D);
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
};

#endif /* defined(__OpenGL_2D_Framework__ProgressBar__) */
