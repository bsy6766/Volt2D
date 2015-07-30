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
#include "ActionDelay.h"

using namespace Volt2D;

//----------------------------------------
#pragma mark Transition
//----------------------------------------
Transition::Transition():
duration(0),
nextScene(0),
done(false)
{
    
}

Transition::~Transition(){
    
}

void Transition::swapScene(){
    Director::getInstance().getRunningScene()->exit();
    nextScene->init();
    Director::getInstance().replaceScene(nextScene);
}

bool Transition::isDone(){
    return this->done;
}

//----------------------------------------
#pragma mark TransitionFade
//----------------------------------------

TransitionFade::TransitionFade():
Transition(),
texture(0),
effect(0)
{
    
}

TransitionFade::~TransitionFade(){
    //release effect. This will delete texture for us.
    if(this->effect)
        delete this->effect;
}

TransitionFade* TransitionFade::createWithColor(double duration, Volt2D::Color color, Scene* scene){
    //create new transition instance.
    TransitionFade* newTransition = new TransitionFade();
    newTransition->initTransition(duration, color, scene);
    return newTransition;
}

bool TransitionFade::initTransition(double duration, Color color, Volt2D::Scene *nextScene){
    //store variables
    this->duration = duration;
    this->nextScene = nextScene;
    
    //allocate empty texture data.
    unsigned char* data = new unsigned char[2/*width*/ *
                                            2/*height*/ *
                                            4/*RGBA*/];
    //generate custom texture data sized 2x2 pixels with solid color
    for(int i = 0; i<4; i++){
        data[i*4] = static_cast<unsigned char>(color.getR());
        data[i*4+1] = static_cast<unsigned char>(color.getG());
        data[i*4+2] = static_cast<unsigned char>(color.getB());
        data[i*4+3] = static_cast<unsigned char>(color.getA());
    }
    //create teture with custom data
    this->texture = Texture::createCustom2DTexture(2, 2, data, 4);
    //delete allocated data.
    delete data;
    
    //return false if failed to generate texture
    if(this->texture == nullptr)
        return false;
    
    //initialize sprite for fade effect.
    this->effect = Volt2D::Sprite::createCustom("FadeTransition", this->texture, Director::getInstance().getWindowSize().w, Director::getInstance().getWindowSize().h);
    
    //return false if failed to generate fade effect sprite
    if(this->effect == nullptr)
        return false;
    
    //effect starts from 0 opacity.
    effect->setOpacity(0);
    
    //Make actions.
    //delay -> fade in -> swap scene -> delay -> fade out -> end -> delay
    auto fadeIn = ActionFadeTo::createFadeTo(this->duration/2.0, 255.0f);
    auto swapScene = ActionCallFunc::createCallFunc(std::bind(&Volt2D::Transition::swapScene, this));
    auto fadeOut = ActionFadeTo::createFadeTo(this->duration/2.0, 0.0f);
    auto end = ActionCallFunc::createCallFunc(std::bind(&Volt2D::TransitionFade::end, this));
    //extra delay padding fornt and in between actions to prevent graphical glitches.
    auto delay = ActionDelay::createDelay(0.2f);
    
    //Assign
    effect->addActions({delay, fadeIn, swapScene, delay, fadeOut, end, delay}, 0);
    
    //release
    delete fadeIn;
    delete swapScene;
    delete fadeOut;
    delete delay;
    delete end;
    
    //success
    return true;
}

void TransitionFade::start(){
    this->effect->runAction();
}

void TransitionFade::update(double dt){
    this->effect->update(dt);
}

void TransitionFade::render(){
    this->effect->render();
}

void TransitionFade::end(){
    this->done = true;
}


