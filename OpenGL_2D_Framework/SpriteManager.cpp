//
//  SpriteManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteManager.h"
#include "SpriteObject.h"

SpriteManager::SpriteManager():globalVisible(true){
    cout << "SpriteManager" << endl;
}

SpriteManager::~SpriteManager(){
    cout << "~SpriteManager" << endl;
    //clear remaining sprites on list
    for (std::list<SpriteObject *>::const_iterator ci = spriteList.begin(); ci != spriteList.end(); ++ci){
        delete (*ci);
    }
    //clear the list. But wouldn't the program release it anyway?
    spriteList.clear();
}

void SpriteManager::render(){
    if(!globalVisible)
        return;
    
    for (std::list<SpriteObject *>::const_iterator ci = spriteList.begin(); ci != spriteList.end(); ++ci){
        (*ci)->render();
    }
}

void SpriteManager::update(){
    //iterating through list. update and delete nulls(0)
    for (std::list<SpriteObject *>::const_iterator ci = spriteList.begin(); ci != spriteList.end();){
        //if pointer is null, delete pointer and remove from the list.
        if((*ci) == 0){
            delete (*ci);
            ci = spriteList.erase(ci);  //returns next element
        }
        else{
            (*ci)->update();
            ++ci;
        }
    }
}

//sort compare function
//bool compareZ(SpriteObject* lhs, SpriteObject* rhs){
//    return lhs->getZ_Depth() < rhs->getZ_Depth();
//}

//add sprtie and sort by z depth
void SpriteManager::addSprite(SpriteObject *pSpriteObj){
    assert(pSpriteObj != 0);
    
    spriteList.push_back(pSpriteObj);
//    spriteList.sort(compareZ);
}