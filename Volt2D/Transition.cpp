//
//  Transition.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 7/27/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Transition.h"
#include "Director.h"
#include "Scene.h"
#include "Timer.h"

using namespace Volt2D;

//----------------------------------------
#pragma mark Transition
//----------------------------------------
Transition::Transition():
duration(0),
nextScene(0),
done(false),
delayPad(ActionDelay::createDelay(0.2f)),
callEndFunc(ActionCallFunc::createCallFunc(std::bind(&Volt2D::Transition::end, this))),
callSwapSceneFunc(ActionCallFunc::createCallFunc(std::bind(&Volt2D::Transition::swapScene, this))),
callOnEnter(ActionCallFunc::createCallFunc(std::bind(&Volt2D::Transition::callEnterFunc, this)))
{
    
}

Transition::~Transition(){
    delete callEndFunc;
    delete callSwapSceneFunc;
    delete callOnEnter;
    delete delayPad;
}

void Transition::swapScene(){
    //This function is friend of Director.
    Volt2D::Director& directorRef = Volt2D::Director::getInstance();
    if(directorRef.runningScene){
        //delete dying scene
        directorRef.dyingScene = directorRef.runningScene;
        //assign new one. Transition class will init for us.
        directorRef.runningScene = this->nextScene;
        directorRef.dyingScene->exit();
        delete directorRef.dyingScene;
    }
}

bool Transition::isDone(){
    return this->done;
}

void Transition::end(){
    this->done = true;
}

void Transition::callEnterFunc(){
    //some transition need to enter after some other action
    Director::getInstance().getRunningScene()->onEnter();
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
    
    //store scene and init.
    this->nextScene = nextScene;
    //get time tick
    double t_start = Timer::getInstance().getCurrentTick();
    //intialize next scene on creation
    this->nextScene->init();
    
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
    delete [] data;
    
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
    
    //delay -> fade in -> swap scene -> delay -> fade out -> end -> delay
    auto fadeIn = ActionFadeTo::createFadeTo(this->duration/2.0, 255.0f);
    auto fadeOut = ActionFadeTo::createFadeTo(this->duration/2.0, 0.0f);
    
    //initializing transition done.
    //get time tick
    double t_end = Timer::getInstance().getCurrentTick();
    //calculate time spent.
    double initElapsedTime = t_end - t_start;
    
    //delay action by time spend on initializing next scene .
    auto delay = ActionDelay::createDelay(initElapsedTime + 0.5f);
    
    //Assign
    effect->addActions({delay, fadeIn, delayPad, callSwapSceneFunc, callOnEnter, fadeOut, callEndFunc, delayPad}, 0);
    
    //release
    delete fadeIn;
    delete fadeOut;
    delete delay;
    
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
    Volt2D::Director::getInstance().getRunningScene()->render();
    this->effect->render();
}

//----------------------------------------
#pragma mark TransitionMove
//----------------------------------------

TransitionMove::TransitionMove():
Transition(),
sceneSwapped(false)
{
    
}

TransitionMove::~TransitionMove(){
    
}

TransitionMove* TransitionMove::createWithDirection(double duration, Volt2D::TransitionDirection direction, Scene* nextScene){
    TransitionMove* newTransition = new TransitionMove();
    newTransition->initTransition(duration, direction, nextScene);
    return newTransition;
}

void TransitionMove::initTransition(double duration, Volt2D::TransitionDirection direction, Scene* nextScene){
    this->duration = duration;
    //store scene and init.
    this->nextScene = nextScene;
    //get time tick
    double t_start = Timer::getInstance().getCurrentTick();
    //intialize next scene on creation
    this->nextScene->init();
    
    ActionMoveBy* moveBy = nullptr;
    
    //get window size
    Volt2D::WinSize winSize = Director::getInstance().getWindowSize();
    
    switch (direction) {
        case Volt2D::TransitionDirection::UP:
        {
            //set position
            this->nextScene->setPosition(glm::vec3(0, -winSize.h, 0));
            //create move action to move next scene to up
            moveBy = ActionMoveBy::createMoveBy(duration/2.0f, glm::vec3(0, winSize.h, 0));
        }
            break;
        case Volt2D::TransitionDirection::DOWN:
        {
            this->nextScene->setPosition(glm::vec3(0, winSize.h, 0));
            moveBy = ActionMoveBy::createMoveBy(duration/2.0f, glm::vec3(0, -winSize.h, 0));
        }
            break;
        case Volt2D::TransitionDirection::RIGHT:
        {
            this->nextScene->setPosition(glm::vec3(-winSize.w, 0, 0));
            moveBy = ActionMoveBy::createMoveBy(duration/2.0f, glm::vec3(winSize.w, 0, 0));
        }
            break;
        case Volt2D::TransitionDirection::LEFT:
        {
            this->nextScene->setPosition(glm::vec3(winSize.w, 0, 0));
            moveBy = ActionMoveBy::createMoveBy(duration/2.0f, glm::vec3(-winSize.w, 0, 0));
        }
            break;
        default:
            break;
    }
    //check if it's valid
    assert(moveBy != nullptr);
    
    //get time tick
    double t_end = Timer::getInstance().getCurrentTick();
    //calculate time spent.
    double initElapsedTime = t_end - t_start;
    
    //delay action by time spend on initializing next scene .
    auto delay = ActionDelay::createDelay(initElapsedTime + 0.5f);
    
    //add action
    this->nextScene->addActions({delay, moveBy, callSwapSceneFunc, callOnEnter, delayPad, callEndFunc}, 0);
    //set actions to current scene too.
    Director::getInstance().getRunningScene()->addActions({delay, moveBy}, 0);
    
    delete moveBy;
    delete delay;
}

void TransitionMove::start(){
    this->nextScene->runAction();
    Director::getInstance().getRunningScene()->runAction();
}

void TransitionMove::update(double dt){
    this->nextScene->update(dt);
}

void TransitionMove::render(){
    //must render next scene first because next scene can have other sprites that are positioned off screen
    if(!sceneSwapped){
        this->nextScene->render();
    }
    Director::getInstance().getRunningScene()->render();
}

void TransitionMove::swapScene(){
    this->sceneSwapped = true;
    Transition::swapScene();
}

//----------------------------------------
#pragma mark TransitionFlip
//----------------------------------------

TransitionFlip::TransitionFlip():
Transition()
{
    
}

TransitionFlip::~TransitionFlip(){
    
}

TransitionFlip* TransitionFlip::createWithDirection(double duration, Volt2D::TransitionDirection direction, Scene* nextScene){
    TransitionFlip* newTransition = new TransitionFlip();
    newTransition->initTransition(duration, direction, nextScene);
    return newTransition;
}

void TransitionFlip::initTransition(double duration, Volt2D::TransitionDirection direction, Scene* nextScene){
    this->duration = duration;
    //store scene and init.
    this->nextScene = nextScene;
    //get time tick
    double t_start = Timer::getInstance().getCurrentTick();
    //intialize next scene on creation
    this->nextScene->init();
    
    ActionRotateBy* rotateBy = nullptr;
    
    switch (direction) {
        case Volt2D::TransitionDirection::UP:
        {
            //set starting angle for next scene
            this->nextScene->setAngle(-180, X_AXIS);
            rotateBy = ActionRotateBy::createRotateBy(duration/2.0f, 90.0f, X_AXIS);
        }
            break;
        case Volt2D::TransitionDirection::DOWN:
        {
            this->nextScene->setAngle(180, X_AXIS);
            rotateBy = ActionRotateBy::createRotateBy(duration/2.0f, -90.0f, X_AXIS);
        }
            break;
        case Volt2D::TransitionDirection::RIGHT:
        {
            this->nextScene->setAngle(-180, Y_AXIS);
            rotateBy = ActionRotateBy::createRotateBy(duration/2.0f, 90.0f, Y_AXIS);
        }
            break;
        case Volt2D::TransitionDirection::LEFT:
        {
            this->nextScene->setAngle(180, Y_AXIS);
            rotateBy = ActionRotateBy::createRotateBy(duration/2.0f, -90.0f, Y_AXIS);
        }
            break;
        default:
            break;
    }
    //check if it's valid
    assert(rotateBy != nullptr);
    
    //get time tick
    double t_end = Timer::getInstance().getCurrentTick();
    //calculate time spent.
    double initElapsedTime = t_end - t_start;
    
    //delay action by time spend on initializing next scene .
    auto delay = ActionDelay::createDelay(initElapsedTime + 0.5f);
    
    //add action
    this->nextScene->addActions({delay, rotateBy, callSwapSceneFunc, rotateBy, callOnEnter, delayPad, callEndFunc}, 0);
    //set actions to current scene too.
    Director::getInstance().getRunningScene()->addActions({delay, rotateBy}, 0);
    
    delete rotateBy;
    delete delay;
}

void TransitionFlip::start(){
    this->nextScene->runAction();
    Director::getInstance().getRunningScene()->runAction();
}

void TransitionFlip::update(double dt){
    this->nextScene->update(dt);
}

void TransitionFlip::render(){
    //must render next scene first because next scene can have other sprites that are positioned off screen
    Director::getInstance().getRunningScene()->render();
}