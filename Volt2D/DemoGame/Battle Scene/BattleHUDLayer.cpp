//
//  BattleHUDLayer.cpp
//  Volt2D
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
    StatusBar* testBar = new StatusBar("test", glm::vec3(-635, 415, 0));
    testBar->bindTo(this);
    statusBars.push_back(testBar);
}

void BattleHUDLayer::exit(){
    
}