//
//  Transition.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 7/27/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Transition.h"
#include "Director.h"
#include "ActionFadeTo.h"
#include "ActionCallFunc.h"

using namespace Volt2D;

//----------------------------------------
#pragma mark Transition
//----------------------------------------
Transition::Transition():
duration(0),
totalElapsedTime(0),
currentScene(Director::getInstance().getRunningScene()),
nextScene(0),
running(false){
    
}

Transition::~Transition(){
    
}

void Transition::setNextScene(Volt2D::Scene *nextScene){
    this->nextScene = nextScene;
}

Scene* Transition::getNextScene(){
    return this->nextScene;
}

//----------------------------------------
#pragma mark TransitionFade
//----------------------------------------

TransitionFade::TransitionFade():
Transition(),
color(Color::NONE),
texture(0),
effect(0)
{
    
}

TransitionFade::~TransitionFade(){
    if(this->effect)
        delete this->effect;
}

TransitionFade* TransitionFade::createWithColor(Volt2D::Color color, Scene* scene){
    TransitionFade* newTransition = new TransitionFade();
    newTransition->initTransition(color, scene);
    return newTransition;
}

bool TransitionFade::initTransition(Color color, Volt2D::Scene *nextScene){
    unsigned char* data = new unsigned char[2 * 2 * 4];
    //generate custom texture data.
    for(int i = 0; i<4; i++){
        data[i*4] = color.getR();
        data[i*4+1] = color.getG();
        data[i*4+2] = color.getB();
        data[i*4+3] = color.getA();
    }
    this->color = color;
    texture->createCustom2DTexture(2, 2, data, 4);
    delete data;
    
    if(!texture)
        return false;
    
    this->effect = Volt2D::Sprite::createWith2DTexture("FadeTransition", this->texture);
    if(!effect)
        return false;
    
    effect->setOpacity(0);
    
    auto fadeIn = ActionFadeTo::createFadeTo(this->duration/2.0, 255.0f);
    auto funcBind = std::bind(&Volt2D::TransitionFade::swapScene, this);
    auto swapScene = ActionCallFunc::createCallFunc(funcBind);
    auto fadeOut = ActionFadeTo::createFadeTo(this->duration/2.0, 0.0f);
    
    effect->addActions({fadeIn, swapScene, fadeOut}, 0);
    
    delete fadeIn;
    delete swapScene;
    delete fadeOut;
    
    return true;
}

void TransitionFade::run(){
    if(!this->running){
        effect->runAction();
    }
}

void TransitionFade::swapScene(){
    if(currentScene && nextScene){
        currentScene->exit();
        Scene* dyingScene = currentScene;
        
    }
}







