//
//  BattleHUDLayer.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "BattleHUDLayer.h"

BattleHUDLayer::BattleHUDLayer(){
    
}

BattleHUDLayer::~BattleHUDLayer(){
    delete statusBars.at(0);
}

void BattleHUDLayer::init(){
    StatusBar* testBar = new StatusBar("test", glm::vec3(-525, 321, 0));
    statusBars.push_back(testBar);
}

void BattleHUDLayer::exit(){
    
}