//
//  Sprite.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Sprite__
#define __OpenGL_2D_Framework__Sprite__

//#include <GL/glew.h>

#include "SpriteObject.h"
#include "Texture.h"
//#include "Scene.h"
//#include "CommonInclude.h"


class Sprite :  public SpriteObject{
private:
    Texture *texture;
    
    //pure virtual.
    virtual void computeVertexData();
    virtual void loadVertexData();
    virtual void render();
    
    Sprite();
    
    void initTexture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D);
    void initSpriteWithSpriteSheet(const std::string spriteFileName);
public:
    static Sprite* createSprite(std::string objectName, const char* fileName, GLenum textureTarget = GL_TEXTURE_2D);
    ~Sprite();

    //inits
    void setType(SpriteType type);
    
    void updateMatrix();
    void updateBillboardMatrix(GLfloat verticalAngle, GLfloat horizontalAngle);
};

#endif /* defined(__OpenGL_2D_Framework__Sprite__) */
