//
//  Layer.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Layer__
#define __OpenGL_2D_Framework__Layer__

/**
 *  Layer can be inherited by other class or be the class it self
 */

#include "SpriteManager.h"
#include "CommonInclude.h"

class Layer{
protected:
private:
    SpriteManager* spriteManager;
    int z;
    
public:
    Layer();
    ~Layer();
    
    virtual void init();
    virtual void update();
    virtual void render();
    virtual void exit();
    
    void setZorder(int z);
    int getZorder();
    
    void addSprite(SpriteObject* childSprite);
};

#endif /* defined(__OpenGL_2D_Framework__Layer__) */
