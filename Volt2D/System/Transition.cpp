//
//  Transition.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 7/27/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Transition.h"
#include "Director.h"

using namespace Volt2D;

//----------------------------------------
#pragma mark Transition
//----------------------------------------
Transition::Transition():
duration(0),
currentScene(Director::getInstance().getRunningScene()),
nextScene(0)
{
    
}

Transition::~Transition(){
    
}

void Transition::setNextScene(Volt2D::Scene *nextScene){
    this->nextScene = nextScene;
}

//----------------------------------------
#pragma mark TransitionFade
//----------------------------------------

TransitionFade::TransitionFade(Color color):
Transition(),
color(color)
{
//    cout << "[SYSTEM::INFO] Creating TransitionFade" << endl;
}

TransitionFade::~TransitionFade(){
    
}

TransitionFade* TransitionFade::createWithColor(Volt2D::Color color, Scene* scene){
    TransitionFade* newTransition = new TransitionFade(color);
    newTransition->setNextScene(scene);
    return newTransition;
}