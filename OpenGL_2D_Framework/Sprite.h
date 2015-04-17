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
#include "CommonInclude.h"


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
    
	static Sprite* createSprite();
	void initTexture(GLenum _textureTarget = GL_TEXTURE_2D, const std::string& _fileName = "../Texture/default.png");


    //inits
    void initSpriteWithTexture(GLenum _textureTarget = GL_TEXTURE_2D, const std::string& _fileName = "../Texture/default.png");
    
    /**
     * updates matrix. 
     * calculate translation, rotation, scale matrix and compute model matrix
     */
    void updateMatrix();
};

#endif /* defined(__OpenGL_2D_Framework__Sprite__) */
