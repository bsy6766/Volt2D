//
//  SpriteManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "SpriteManager.h"

SpriteManager::SpriteManager(){
    globalVisible = true;
}

SpriteManager::~SpriteManager(){
    
}

void SpriteManager::render(){
    if(!globalVisible)
        return;
    
    for (std::list<SpriteObject *>::const_iterator ci = spriteList.begin(); ci != spriteList.end(); ++ci){
        (*ci)->render();
    }
}

void SpriteManager::update(){
    for (std::list<SpriteObject *>::const_iterator ci = spriteList.begin(); ci != spriteList.end(); ++ci){
        (*ci)->update();
    }
}

//sort compare function
bool compareZ(SpriteObject* lhs, SpriteObject* rhs){
    return lhs->getZ_Depth() < rhs->getZ_Depth();
}

//add sprtie and sort by z depth
void SpriteManager::addSprite(SpriteObject *pSpriteObj){
    spriteList.push_back(pSpriteObj);
    spriteList.sort(compareZ);
}

void SpriteManager::deleteSprite(){
    for (std::list<SpriteObject *>::const_iterator ci = spriteList.begin(); ci != spriteList.end(); ++ci){
        delete (*ci);
    }
    
    spriteList.clear();
}