//
//  ProgressRadian.h
//  Volt2D
//
//  Created by Seung Youp Baek on 1/26/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ProgressRadian__
#define __Volt2D__ProgressRadian__

#include "ProgressObject.h"

/**
 *  @class ProgressRadian
 *  @brief A progress radian
 */
class ProgressRadian: public Volt2D::ProgressObject{
private:
    //private constructor
    ProgressRadian();
    
    /**
     *  Initialize ProgressRadian
     *  @param radianTextureName Texture name for progress radian
     *  @param textureTarget GL_TEXTURE_2D
     */
    void initProgressRadian(const std::string radianTextureName, GLenum textureTarget = GL_TEXTURE_2D);
public:
    /**
     *  Create ProgressRadian
     *  @param objectName Name for ProgressRadian object
     *  @param radianTextureName Texture name for progress radian
     *  @param textureTarget GL_TEXTURE_2D
     */
    static ProgressRadian* createProgressRadian(std::string objectName, const char* radianTextureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    //Destructor
    ~ProgressRadian();
    
    /**
     *  Compute vertex and indices
     */
    void computeVertexData();
    
    /**
     *  Load computed vertex.
     */
    void loadVertexData();
    
    /**
     *  Overrides's Object::render();
     *  Render object
     */
    virtual void render() override;
};

#endif /* defined(__Volt2D__ProgressRadian__) */