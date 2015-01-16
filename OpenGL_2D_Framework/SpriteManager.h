//
//  SpriteManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__SpriteManager__
#define __CS364FinalProject__SpriteManager__

#include <list>
#include "SpriteObject.h"

//This class group up, sort, and handles multiple sprites. 

class SpriteManager{
private:
    std::list<SpriteObject*> spriteList;
    
public:
    SpriteManager();
    ~SpriteManager();
    void render();
    void update();
    void addSprite(SpriteObject *pSpriteObj);
    void deleteSprite();
    bool globalVisible;
};

#endif /* defined(__CS364FinalProject__SpriteManager__) */
