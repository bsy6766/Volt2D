//
//  Sprite.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/7/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Sprite__
#define __OpenGL_2D_Framework__Sprite__

#include "SpriteObject.h"
#include "Texture.h"

class Sprite :  public SpriteObject{
private:
    Texture *texture;
    
    //pure virtual.
    void createVertexData();
    void loadVertexData();
    void render();
    
public:
    Sprite();
    Sprite(Program *ptr);   //create with specific program pointer
    ~Sprite();
    
    //inits
    void initSpriteWithTexture(GLenum _textureTarget, const std::string& _fileName);
    
    /**
     * updates matrix. 
     * calculate translation, rotation, scale matrix and compute model matrix
     */
    void updateMatrix();
};

#endif /* defined(__OpenGL_2D_Framework__Sprite__) */
