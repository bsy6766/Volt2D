//
//  StatusBar.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "StatusBar.h"
#include "Object.h"

using namespace Volt2D;

StatusBar::StatusBar(std::string objName, glm::vec3 pos):
pos(pos)
{
    frame = Sprite::createSprite(objName + "Frame", "battle scene/status_frame.png");
    frame->setPosition(pos);
    frame->setZDepth(199);
    
    pos.x += 26;
    
    hpBar = ProgressBar::create(objName + "HpBar", "battle scene/hp_bar.png");
    hpBar->setPercentage(100);
    glm::vec3 hpBarPos = pos;
    hpBarPos.y += 17;
    hpBar->setPosition(hpBarPos);
    hpBar->setZDepth(200);
    
    mpBar = ProgressBar::create(objName + "MpBar", "battle scene/mp_bar.png");
    mpBar->setPercentage(100);
    mpBar->setPosition(pos);
    mpBar->setZDepth(200);
    
    apBar = ProgressBar::create(objName + "ApBar", "battle scene/ap_bar.png");
    apBar->setPercentage(100);
    glm::vec3 apBarPos = pos;
    apBarPos.y -= 17;
    apBar->setPosition(apBarPos);
    apBar->setZDepth(200);
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

void StatusBar::bindTo(Volt2D::Object *obj){
    obj->addChild(frame, obj);
    obj->addChild(hpBar, obj);
    obj->addChild(mpBar, obj);
    obj->addChild(apBar, obj);
}








