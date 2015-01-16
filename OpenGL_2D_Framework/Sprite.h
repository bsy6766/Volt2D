//
//  Sprite.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/7/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__Sprite__
#define __CS364FinalProject__Sprite__

#include "SpriteObject.h"
#include "Texture.h"

class Sprite :  public SpriteObject{
private:
    Texture *texture;
    
    //pure virtual
    void createVertexData();
    void loadVertexData();
    
    void render();
//    void update();
    
public:
    Sprite();
    Sprite(Program *ptr);
    ~Sprite();
    
    //inits
    void initSpriteWithTexture(GLenum _textureTarget, const std::string& _fileName);
    
    glm::mat4 getModelMat();
    
    void updateMatrix();
//    void updateFromAction();
    void removeDeadAction();
};

#endif /* defined(__CS364FinalProject__Sprite__) */
