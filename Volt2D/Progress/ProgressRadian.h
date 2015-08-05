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

namespace Volt2D{
/**
 *  @class ProgressRadian
 *  @brief A progress radian
 */
class ProgressRadian: public Volt2D::ProgressObject{
private:
    //private constructor
    ProgressRadian();
    
    /**
     *  Compute vertex and indices
     */
    void computeVertexData(glm::vec2 origin, glm::vec2 end);
    
    /**
     *  Load computed vertex.
     */
    void loadVertexData();
    
    /**
     *  Initialize ProgressRadian
     *  @param radianTextureName Texture name for progress radian
     *  @param textureTarget GL_TEXTURE_2D
     */
    void init(const std::string radianTextureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    void initWithSpriteSheet(const ImageEntry* ie, Texture* texture);
public:
    /**
     *  Create ProgressRadian
     *  @param objectName Name for ProgressRadian object
     *  @param radianTextureName Texture name for progress radian
     *  @param textureTarget GL_TEXTURE_2D
     */
    static ProgressRadian* create(std::string objectName, const char* radianTextureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    static ProgressRadian* createWithSpriteSheet(std::string objectName, std::string frameName, std::string textureName);
    
    //Destructor
    ~ProgressRadian();
    
    /**
     *  Overrides's Object::render();
     *  Render object
     */
    virtual void render() override;
};
}

#endif /* defined(__Volt2D__ProgressRadian__) */
