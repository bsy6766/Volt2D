//
//  StatusBar.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__StatusBar__
#define __OpenGL_2D_Framework__StatusBar__

#include "ProgressBar.h"
#include "Sprite.h"
#include "Director.h"

class StatusBar{
private:
    //    Hero* target;
    ProgressBar* hpBar; //hit point
    ProgressBar* mpBar; //mana point
    ProgressBar* apBar; //action point
    
    Volt2D::Sprite* frame;
    Volt2D::Sprite* portrait;
    
    glm::vec3 pos;
    
public:
    StatusBar(std::string objName, glm::vec3 pos);
    ~StatusBar();
    
    void updateHpBar(int hp);
    void updateMpBar(int mp);
    void updateApBar(int ap);
};

#endif /* defined(__OpenGL_2D_Framework__StatusBar__) */
