//
//  Sprite.h
//  Volt2D
//
//  Created by Seung Youp Baek on 11/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Sprite__
#define __Volt2D__Sprite__

#include "RenderableObject.h"
#include "Texture.h"
#include "SpriteSheet.h"

namespace Volt2D{
/**
 *  @class Sprite
 *  @brief Simple sprite object loaded with single texture
 *  @note 4 Vertices, 4 UV vertices, 6 indices
 */
class Sprite : public Volt2D::RenderableObject{
private:
    //Temporary friend request from Director
    friend class Director;
    
    /**
     *  A texture.
     */
    Texture* texture;
    
    /**
     *  texture width
     */
    int textureWidth;
    
    /**
     * texture height
     */
    int textureHeight;
    
    /**
     *  Compute vertex and indices
     */
    void computeVertexData();
    
    /**
     *  Load computed vertex.
     */
    void loadVertexData();
    
    //Private constructor
    Sprite();
    
    /**
     *  Initialize texture
     */
    bool initTexture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D);
    
    /**
     *  Initialize custom sprite with texture and size provided.ß
     */
    void initCustom(Texture* texture, float width, float height);
    
    /**
     *  Initialize Sprite with Sprite Sheet
     */
    void initSpriteWithSpriteSheet(const ImageEntry* ie, Texture* texture);
    
    /**
     *  Compute vertices
     */
    void computeVertices();
    
    /**
     *  Compute uv
     */
    void computeTextureCoordinates(glm::vec2 origin = glm::vec2(0, 1), glm::vec2 end = glm::vec2(1, 0));
    
    /**
     *  compute indices
     */
    void computeIndices();
public:
    /**
     *  Create Sprite obejct
     *  @param objectName Name for Sprite object
     *  @param textureName Sprite's texture name
     *  @param textuerTarget = GL_TEXTURE_2D
     */
    static Sprite* create(std::string objectName, std::string textureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    /**
     *  Create sprite object with sprite sheet
     */
    static Sprite* createWithSpriteSheet(std::string objectName, std::string frameName, std::string imageFileName);
    
    /**
     *
     */
    static Sprite* createCustom(std::string objectName, Texture* texture, float width, float height);
    
    //destructor
    ~Sprite();
    
    /**
     *  Overrides's Object::render();
     *  Render object
     */
    virtual void render() override;
    
    /**
     *  Wrapper for Object::addChild.
     */
    void addChild(Object* child);
};
}   //namespace end

#endif /* defined(__Volt2D__Sprite__) */
