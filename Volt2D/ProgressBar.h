//
//  ProgressBar.h
//  Volt2D
//
//  Created by Seung Youp Baek on 1/23/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ProgressBar__
#define __Volt2D__ProgressBar__

#include "ProgressObject.h"

namespace Volt2D{
/**
 *  @class ProgressBar
 *  @brief Textured progress bar
 */
class ProgressBar: public Volt2D::ProgressObject{
private:
    //private constructor
    ProgressBar();
    
    void computeVertices();
    void computeTextureCoordinates(glm::vec2, glm::vec2);
    void computeIndices();
    
    /**
     *  Compute vertex and indices
     */
    void computeVertexData();
    
    /**
     *  Load computed vertex.
     */
    void loadVertexData();
    
    /**
     *  Initialize ProgressBar
     *  @param textureTarget GL_TEXTURE_2D
     */
    void init(const std::string barTextureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    void initWithSpriteSheet(const ImageEntry* ie, Texture* texture);
public:
    /**
     *  Create ProgressBar
     *  @param objectName An object name for ProgressBar
     *  @param barTextureName Texture file name 
     *  @param textureTarget GL_TEXTURE_2D
     */
    static ProgressBar* create(std::string objectName, const char* barTextureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    static ProgressBar* createWithSpriteSheet(std::string objectName, std::string frameName, std::string textureName);
    
    //Destructor
    ~ProgressBar();
    
    /**
     *  Overrides's Object::render();
     *  Render object
     */
    virtual void render() override;
};
}

#endif /* defined(__Volt2D__ProgressBar__) */
