//
//  SpriteManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteManager__
#define __OpenGL_2D_Framework__SpriteManager__

#include <list>
#include <assert.h>
#include <iostream>

#include "SpriteObject.h"

/**
 * Sprite Manager Class
 * This class manages sprites. 
 *
 */

class SpriteManager{
private:
    std::list<SpriteObject*> spriteList;
    
public:
    SpriteManager();
    ~SpriteManager();
    
    void render();
    void update();
    
    void addSprite(SpriteObject *pSpriteObj);
    //void deleteSprite(const std::string spriteName);
    
    bool globalVisible;
};

#endif /* defined(__OpenGL_2D_Framework__SpriteManager__) */
