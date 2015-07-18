//
//  StatusBar.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "StatusBar.h"

StatusBar::StatusBar(std::string objName, glm::vec3 pos):
pos(pos)
{
    frame = Sprite::createSprite(objName + "Frame", "battle scene/status_frame.png");
    frame->setPosition(pos);
    frame->setZDepth(199);
    Director::getInstance().getRunningScene()->addChild(frame);
    
//    portrait = new Sprite();
    
    pos.x += 26;
    
    hpBar = new ProgressBar();
    hpBar->initProgressBar(GL_TEXTURE_2D, "battle scene/hp_bar.png");
    hpBar->setPercentage(100);
    glm::vec3 hpBarPos = pos;
    hpBarPos.y += 17;
    hpBar->setPosition(hpBarPos);
    hpBar->setZDepth(200);
//    Director::getInstance().getRunningScene()->addObject(objName + "HpBar", hpBar);
    
    mpBar = new ProgressBar();
    mpBar->initProgressBar(GL_TEXTURE_2D, "battle scene/mp_bar.png");
    mpBar->setPercentage(100);
    mpBar->setPosition(pos);
    mpBar->setZDepth(200);
//    Director::getInstance().getRunningScene()->addObject(objName + "MpBar", mpBar);
    
    apBar = new ProgressBar();
    apBar->initProgressBar(GL_TEXTURE_2D, "battle scene/ap_bar.png");
    apBar->setPercentage(100);
    glm::vec3 apBarPos = pos;
    apBarPos.y -= 17;
    apBar->setPosition(apBarPos);
    apBar->setZDepth(200);
//    Director::getInstance().getRunningScene()->addObject(objName + "ApBar", apBar);
}

StatusBar::~StatusBar(){
    
}

void StatusBar::updateHpBar(int hp){
    hpBar->setPercentage(hp);
}

void StatusBar::updateMpBar(int mp){
    mpBar->setPercentage(mp);
}

void StatusBar::updateApBar(int ap){
    apBar->setPercentage(ap);
}