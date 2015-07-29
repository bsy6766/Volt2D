//
//  StatusBar.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "StatusBar.h"

using namespace Volt2D;

StatusBar::StatusBar(std::string objName, glm::vec3 pos):
pos(pos)
{
    frame = Sprite::createSprite(objName + "Frame", "battle scene/status_frame.png");
    frame->setPosition(pos);
    frame->setZDepth(199);
    Volt2D::Director::getInstance().getRunningScene()->addChild(frame);
    
    pos.x += 26;
    
    hpBar = ProgressBar::createProgressBar(objName + "HpBar", "battle scene/hp_bar.png");
    hpBar->setPercentage(100);
    glm::vec3 hpBarPos = pos;
    hpBarPos.y += 17;
    hpBar->setPosition(hpBarPos);
    hpBar->setZDepth(200);
    Volt2D::Director::getInstance().getRunningScene()->addChild(hpBar);
    
    mpBar = ProgressBar::createProgressBar(objName + "MpBar", "battle scene/mp_bar.png");
    mpBar->setPercentage(100);
    mpBar->setPosition(pos);
    mpBar->setZDepth(200);
    Volt2D::Director::getInstance().getRunningScene()->addChild(mpBar);
    
    apBar = ProgressBar::createProgressBar(objName + "ApBar", "battle scene/ap_bar.png");
    apBar->setPercentage(100);
    glm::vec3 apBarPos = pos;
    apBarPos.y -= 17;
    apBar->setPosition(apBarPos);
    apBar->setZDepth(200);
    Volt2D::Director::getInstance().getRunningScene()->addChild(apBar);
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