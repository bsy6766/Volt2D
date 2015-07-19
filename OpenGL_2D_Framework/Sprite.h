//
//  Sprite.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Sprite__
#define __OpenGL_2D_Framework__Sprite__

#include "SpriteObject.h"
#include "Texture.h"

/**
 *  @class Sprite
 *  @brief Simple sprite object loaded with single texture
 *  @note 4 Vertices, 4 UV vertices, 6 indices
 *  \todo Give Sprite class option to search SpriteSheet on creation
 */
class Sprite :  public SpriteObject{
private:
    //Temporary friend request from Director
    friend class Director;
    
    /**
     *  A texture.
     */
    Texture *texture;
    
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
     *  Overrides's RenderableObject::render();
     *  Render object
     */
    virtual void render();
    
    //Private constructor
    Sprite();
    
    /**
     *  Initialize texture
     */
    void initTexture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D);
    
    /**
     *  Initialize Sprite with Sprite Sheet
     */
    void initSpriteWithSpriteSheet(const std::string spriteFileName);
public:
    /**
     *  Create Sprite obejct
     *  @param objectName Name for Sprite object
     *  @param textureName Sprite's texture name
     *  @param textuerTarget = GL_TEXTURE_2D
     */
    static Sprite* createSprite(std::string objectName, const char* textureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    //destructor
    ~Sprite();

    /**
     *  Set rendering type
     */
    void setType(SpriteType type);
};

#endif /* defined(__OpenGL_2D_Framework__Sprite__) */
