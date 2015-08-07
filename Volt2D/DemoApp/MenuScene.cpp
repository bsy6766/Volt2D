//
//  MenuScene.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 7/25/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "MenuScene.h"

MenuScene::MenuScene():
Scene(),
waitingExit(false),
curState(s_none),
defaultBtnOpacity(160.0f),
sampleActioning(false),
sampleSprite(0),
sampleAnimation(0),
sampleProgBarBg(0),
sampleProgBar(0),
sampleProgRadBg(0),
sampleProgRad(0),
sampleParticleSystem(0),
sampleText(0),
mouseClicked(false),
prevMousePos(0),
mouseDragged(false),
ctrlPressed(false)
{
    
}

MenuScene::~MenuScene(){
    
}

void MenuScene::init(){
    std::string frameName = "demoMenu";
    //create sprite sheet
    Volt2D::
    SpriteSheet::
    createSpriteSheet(frameName, "DemoApp/MenuScene/", "menu_scene_spritesheet");
    
    //init sprites from sprite sheet
    menuBg = Volt2D::Sprite::createSpriteWithFrameName("menuBg",
                                                       frameName,
                                                       "menu_bg.png");
    menuBg->setZDepth(z_bg);
    this->addChild(menuBg);    
    
    float x = -700.0f - 428;
    float yGap = 42.0f;
    glm::vec2 anchor = glm::vec2(-0.5f, 0);
    
    auto delay = Volt2D::ActionDelay::createDelay(0.5f);
    auto moveRight = Volt2D::ActionMoveBy::createMoveBy(1.0f, glm::vec3(428, 0, 0));
    
    spriteBtn = Volt2D::Sprite::createSpriteWithFrameName("spriteBtn",
                                                          frameName,
                                                          "sprite_btn.png");
    spriteBtn->setPosition(glm::vec3(x, 420 - yGap * 0, 0));
    spriteBtn->setAnchorPoint(anchor);
    spriteBtn->setZDepth(z_btn);
    spriteBtn->addActions({delay, moveRight}, 0);
    spriteBtn->setOpacity(defaultBtnOpacity);
    this->addChild(spriteBtn);
    
    spriteAnimationBtn = Volt2D::Sprite::createSpriteWithFrameName("spriteAnimationBtn",
                                                                   frameName,
                                                                   "spriteanimation_btn.png");
    spriteAnimationBtn->setPosition(glm::vec3(x, 420 - yGap * 1, 0));
    spriteAnimationBtn->setAnchorPoint(anchor);
    spriteAnimationBtn->setZDepth(z_btn);
    spriteAnimationBtn->addActions({delay, moveRight}, 0);
    spriteAnimationBtn->setOpacity(defaultBtnOpacity);
    this->addChild(spriteAnimationBtn);
    
    progressBtn = Volt2D::Sprite::createSpriteWithFrameName("progressBtn",
                                                            frameName,
                                                            "progress_btn.png");
    progressBtn->setPosition(glm::vec3(x, 420 - yGap * 2, 0));
    progressBtn->setAnchorPoint(anchor);
    progressBtn->setZDepth(z_btn);
    progressBtn->addActions({delay, moveRight}, 0);
    progressBtn->setOpacity(defaultBtnOpacity);
    this->addChild(progressBtn);
    
    particleSysBtn = Volt2D::Sprite::createSpriteWithFrameName("particleSysBtn",
                                                               frameName,
                                                               "particlesystem_btn.png");
    particleSysBtn->setPosition(glm::vec3(x, 420 - yGap * 3, 0));
    particleSysBtn->setAnchorPoint(anchor);
    particleSysBtn->setZDepth(z_btn);
    particleSysBtn->addActions({delay, moveRight}, 0);
    particleSysBtn->setOpacity(defaultBtnOpacity);
    this->addChild(particleSysBtn);
    
    textBtn = Volt2D::Sprite::createSpriteWithFrameName("textBtn",
                                                        frameName,
                                                        "text_btn.png");
    textBtn->setPosition(glm::vec3(x, 420 - yGap * 4, 0));
    textBtn->setAnchorPoint(anchor);
    textBtn->setZDepth(z_btn);
    textBtn->addActions({delay, moveRight}, 0);
    textBtn->setOpacity(defaultBtnOpacity);
    this->addChild(textBtn);
    
    sceneTransitionFadeBtn = Volt2D::Sprite::createSpriteWithFrameName("sceneTransitionFadeBtn",
                                                                       frameName,
                                                                       "scenetransitionfade_btn.png");
    sceneTransitionFadeBtn->setPosition(glm::vec3(x, 420 - yGap * 5, 0));
    sceneTransitionFadeBtn->setAnchorPoint(anchor);
    sceneTransitionFadeBtn->setZDepth(z_btn);
    sceneTransitionFadeBtn->addActions({delay, moveRight}, 0);
    sceneTransitionFadeBtn->setOpacity(defaultBtnOpacity);
    this->addChild(sceneTransitionFadeBtn);
    
    sceneTransitionMoveBtn = Volt2D::Sprite::createSpriteWithFrameName("sceneTransitionMoveBtn",
                                                                       frameName,
                                                                       "scenetransitionmove_btn.png");
    sceneTransitionMoveBtn->setPosition(glm::vec3(x, 420 - yGap * 6, 0));
    sceneTransitionMoveBtn->setAnchorPoint(anchor);
    sceneTransitionMoveBtn->setZDepth(z_btn);
    sceneTransitionMoveBtn->addActions({delay, moveRight}, 0);
    sceneTransitionMoveBtn->setOpacity(defaultBtnOpacity);
    this->addChild(sceneTransitionMoveBtn);

    sceneTransitionFlipBtn = Volt2D::Sprite::createSpriteWithFrameName("sceneTransitionFlipBtn",
                                                                       frameName,
                                                                       "scenetransitionflip_btn.png");
    sceneTransitionFlipBtn->setPosition(glm::vec3(x, 420 - yGap * 7, 0));
    sceneTransitionFlipBtn->setAnchorPoint(anchor);
    sceneTransitionFlipBtn->setZDepth(z_btn);
    sceneTransitionFlipBtn->addActions({delay, moveRight}, 0);
    sceneTransitionFlipBtn->setOpacity(defaultBtnOpacity);
    this->addChild(sceneTransitionFlipBtn);
    
    displayBorderline = Volt2D::Sprite::createSpriteWithFrameName("displayFrame",
                                                                  frameName,
                                                                  "display_borderline.png");
    displayBorderline->setPosition(glm::vec3(227, 89, 0));
    displayBorderline->setZDepth(z_dispaly_frame);
    displayBorderline->setOpacity(0);
    auto fadeIn = Volt2D::ActionFadeTo::createFadeTo(1.0f, 255.0f);
    displayBorderline->addActions({delay, fadeIn}, 0);
    this->addChild(displayBorderline);
    
    instructionBox = Volt2D::Sprite::createSpriteWithFrameName("instructionBox",
                                                               frameName,
                                                               "instruction_box.png");
    instructionBox->setPosition(glm::vec3(0, -550, 0));
    auto moveUp = Volt2D::ActionMoveBy::createMoveBy(1.0f, glm::vec3(0, 200.0f, 0));
    instructionBox->addActions({delay, moveUp}, 0);
    this->addChild(instructionBox);
    
    delete delay;
    delete moveUp;
    delete fadeIn;
    
    //add font
    Volt2D::FontManager::getInstance().addFont("UhBee Kang-Ja.ttf", 50);
    
    waitingTransitionMsg = Volt2D::Sprite::createSpriteWithFrameName("waitingTransition", frameName, "waiting_transition.png");
    waitingTransitionMsg->setZDepth(z_samples);
    waitingTransitionMsg->setPosition(glm::vec3(227, 89, 0));
    waitingTransitionMsg->setOpacity(0);
    this->addChild(waitingTransitionMsg);
}

void MenuScene::onEnter(){
    spriteBtn->runAction();
    spriteAnimationBtn->runAction();
    progressBtn->runAction();
    particleSysBtn->runAction();
    textBtn->runAction();
    sceneTransitionMoveBtn->runAction();
    sceneTransitionFadeBtn->runAction();
    sceneTransitionFlipBtn->runAction();
    displayBorderline->runAction();
    instructionBox->runAction();
}

void MenuScene::update(double dt){
    //empty?
    Scene::update(dt);
}

void MenuScene::keyPressed(int key, int mods){
    if(key == GLFW_KEY_LEFT_CONTROL){
        this->ctrlPressed = true;
    }
    
    if(key == GLFW_KEY_R){
        switch (curState) {
            case s_sprite:
                if(sampleSprite != nullptr){
                    sampleSprite->stopAllActions();
                    sampleActioning = false;
                    sampleSprite->setPosition(glm::vec3(227, 89, 0));
                    sampleSprite->setAngle(0);
                    sampleSprite->setScale(glm::vec3(1.0f));
                }
                break;
            case s_sprite_animation:
                if(sampleAnimation != nullptr){
                    sampleAnimation->stopAllActions();
                    sampleActioning = false;
                    sampleAnimation->setPosition(glm::vec3(227, 89, 0));
                    sampleAnimation->setAngle(0);
                    sampleAnimation->setScale(glm::vec3(1.0f));
                }
                break;
            default:
                break;
        }
    }
    
    if(key == GLFW_KEY_ESCAPE){
        if(this->waitingExit){
            //cancel waiting
            this->waitingExit = false;
        }
        else{
            //show exit prompt
            this->waitingExit = true;
        }
    }
    else if(key == GLFW_KEY_ENTER) {
        if(this->waitingExit){
            //exit program
            Volt2D::Director::getInstance().terminateApp();
        }
    }
    
    if(key == GLFW_KEY_W){
        switch (curState) {
            case s_none:
                break;
            case s_sprite:
                break;
            case s_sprite_animation:
                break;
            default:
                break;
        }
    }
    else if(key == GLFW_KEY_A){
        switch (curState) {
            case s_none:
                break;
            case s_sprite:
                break;
            case s_sprite_animation:
                break;
            default:
                break;
        }
    }
    else if(key == GLFW_KEY_S){
        switch (curState) {
            case s_none:
                break;
            case s_sprite:
                break;
            case s_sprite_animation:
                break;
            default:
                break;
        }
    }
    else if(key == GLFW_KEY_D){
        switch (curState) {
            case s_none:
                break;
            case s_sprite:
                break;
            case s_sprite_animation:
                break;
            default:
                break;
        }
    }
    
    
    //Key 1, 2, 3, 4, ...
    if(key == GLFW_KEY_1){
        switch (curState) {
            case s_none:
                break;
            case s_sprite_animation:
                if(sampleAnimation != nullptr){
                    std::string runningAniName = sampleAnimation->getPlayingAnimationName();
                    if(runningAniName != "run"){
                        sampleAnimation->playAnimation("run");
                    }
                }
                break;
            case s_progress:
                if(sampleProgBar != nullptr){
                    if(!sampleActioning){
                        sampleActioning = true;
                        auto fromTo = Volt2D::ProgressFromTo::createFromTo(0.5f, sampleProgBar->getPercentage(), sampleProgBar->getPercentage() - 10.0f);
                        auto toggleFunc = Volt2D::ActionCallFunc::createCallFunc(std::bind(&MenuScene::toggleActionFlag, this));
                        sampleProgBar->addActions({fromTo, toggleFunc}, 0);
                        sampleProgBar->runAction();
                        delete fromTo;
                        delete toggleFunc;
                    }
                }
                break;
            case s_particle_system:
                if(sampleParticleSystem->getName() != "sampleParticleSystem_magicalOribts"){
                    this->removechild(sampleParticleSystem, true);
                    sampleParticleSystem = Volt2D::ParticleSystem::createWithLuaConfig("sampleParticleSystem_magicalOrbits", "Particle/magicalOrbits.lua");
                    sampleParticleSystem->setZDepth(z_samples);
                    sampleParticleSystem->setPosition(glm::vec3(227, 89, 0));
                    this->addChild(sampleParticleSystem);
                }
                break;
            case s_st_move:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionMove::createWithDirection(1.0f, Volt2D::TransitionDirection::UP, new MenuScene()));
                }
                break;
            case s_st_fade:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionFade::createWithColor(1.0f, Volt2D::Color::BLACK, new MenuScene()));
                }
                break;
            case s_st_flip:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionFlip::createWithDirection(1.0f, Volt2D::TransitionDirection::UP, new MenuScene()));
                }
                break;
            default:
                break;
        }
    }
    else if(key == GLFW_KEY_2){
        switch (curState) {
            case s_none:
                break;
            case s_sprite_animation:
                if(sampleAnimation != nullptr){
                    std::string runningAniName = sampleAnimation->getPlayingAnimationName();
                    if(runningAniName != "idle"){
                        sampleAnimation->playAnimation("idle");
                    }
                }
                break;
            case s_progress:
                if(sampleProgBar != nullptr){
                    if(!sampleActioning){
                        sampleActioning = true;
                        auto fromTo = Volt2D::ProgressFromTo::createFromTo(0.5f, sampleProgBar->getPercentage(), sampleProgBar->getPercentage() + 10.0f);
                        auto toggleFunc = Volt2D::ActionCallFunc::createCallFunc(std::bind(&MenuScene::toggleActionFlag, this));
                        sampleProgBar->addActions({fromTo, toggleFunc}, 0);
                        sampleProgBar->runAction();
                        delete fromTo;
                        delete toggleFunc;
                    }
                }
                break;
            case s_particle_system:
                if(sampleParticleSystem->getName() != "sampleParticleSystem_flame"){
                    this->removechild(sampleParticleSystem, true);
                    sampleParticleSystem = Volt2D::ParticleSystem::createWithLuaConfig("sampleParticleSystem_flame", "Particle/flame.lua");
                    sampleParticleSystem->setZDepth(z_samples);
                    sampleParticleSystem->setPosition(glm::vec3(227, 89, 0));
                    this->addChild(sampleParticleSystem);
                }
                break;
            case s_st_move:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionMove::createWithDirection(1.0f, Volt2D::TransitionDirection::DOWN, new MenuScene()));
                }
                break;
            case s_st_fade:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionFade::createWithColor(1.0f, Volt2D::Color::RED, new MenuScene()));
                }
                break;
            case s_st_flip:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionFlip::createWithDirection(1.0f, Volt2D::TransitionDirection::DOWN, new MenuScene()));
                }
                break;
            default:
                break;
        }
    }
    else if(key == GLFW_KEY_3){
        switch (curState) {
            case s_none:
                break;
            case s_sprite_animation:
                if(sampleAnimation != nullptr){
                    std::string runningAniName = sampleAnimation->getPlayingAnimationName();
                    if(runningAniName != "block"){
                        sampleAnimation->playAnimation("block");
                    }
                }
                break;
            case s_progress:
                if(sampleProgRad != nullptr){
                    if(!sampleActioning){
                        sampleActioning = true;
                        auto fromTo = Volt2D::ProgressFromTo::createFromTo(0.5f, sampleProgRad->getPercentage(), sampleProgRad->getPercentage() - 10.0f);
                        auto toggleFunc = Volt2D::ActionCallFunc::createCallFunc(std::bind(&MenuScene::toggleActionFlag, this));
                        sampleProgRad->addActions({fromTo, toggleFunc}, 0);
                        sampleProgRad->runAction();
                        delete fromTo;
                        delete toggleFunc;
                    }
                }
                break;
            case s_particle_system:
                if(sampleParticleSystem->getName() != "sampleParticleSystem_blueMeteor"){
                    this->removechild(sampleParticleSystem, true);
                    sampleParticleSystem = Volt2D::ParticleSystem::createWithLuaConfig("sampleParticleSystem_blueMeteor", "Particle/blueMeteor.lua");
                    sampleParticleSystem->setZDepth(z_samples);
                    sampleParticleSystem->setPosition(glm::vec3(227, 89, 0));
                    this->addChild(sampleParticleSystem);
                }
                break;
            case s_st_move:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionMove::createWithDirection(1.0f, Volt2D::TransitionDirection::LEFT, new MenuScene()));
                }
                break;
            case s_st_fade:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionFade::createWithColor(1.0f, Volt2D::Color::NAVY, new MenuScene()));
                }
                break;
            case s_st_flip:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionFlip::createWithDirection(1.0f, Volt2D::TransitionDirection::LEFT, new MenuScene()));
                }
                break;
            default:
                break;
        }
    }
    else if(key == GLFW_KEY_4){
        switch (curState) {
            case s_none:
                break;
            case s_progress:
                if(sampleProgRad != nullptr){
                    if(!sampleActioning){
                        sampleActioning = true;
                        auto fromTo = Volt2D::ProgressFromTo::createFromTo(0.5f, sampleProgRad->getPercentage(), sampleProgRad->getPercentage() + 10.0f);
                        auto toggleFunc = Volt2D::ActionCallFunc::createCallFunc(std::bind(&MenuScene::toggleActionFlag, this));
                        sampleProgRad->addActions({fromTo, toggleFunc}, 0);
                        sampleProgRad->runAction();
                        delete fromTo;
                        delete toggleFunc;
                    }
                }
                break;
            case s_st_move:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionMove::createWithDirection(1.0f, Volt2D::TransitionDirection::RIGHT, new MenuScene()));
                }
                break;
            case s_st_fade:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionFade::createWithColor(1.0f, Volt2D::Color::WHITE, new MenuScene()));
                }
                break;
            case s_st_flip:
                if(this->waitingTransition){
                    Volt2D::Director::getInstance().transitionToNextScene(Volt2D::TransitionFlip::createWithDirection(1.0f, Volt2D::TransitionDirection::RIGHT, new MenuScene()));
                }
                break;
            default:
                break;
        }
    }
    
    Scene::keyPressed(key, mods);
}

void MenuScene::keyReleased(int key, int mods){
    if(key == GLFW_KEY_LEFT_CONTROL){
        ctrlPressed = false;
    }
    Scene::keyReleased(key, mods);
}

void MenuScene::mouseButton(double x, double y, int button, int action, int mods){
    glm::vec2 point(x, y);
    
    if(button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS){
            this->mouseClicked = true;
            this->prevMousePos = glm::vec2(x, y);
            if(this->displayBorderline->getBoundingBox()->containsPoint(point)){
                this->displayBoxClicked = true;
            }
        }
        else if(action == GLFW_RELEASE){
            this->mouseClicked = false;
            if(this->mouseDragged){
                this->mouseDragged = false;
            }
            else{
                //if left button clicked
                if(this->displayBoxClicked){
                    cout << "display box" << endl;
                    switch (curState) {
                        case s_sprite:
                            if(sampleSprite != nullptr){
                                if(!sampleActioning){
                                    sampleActioning = true;
                                    auto moveTo = Volt2D::ActionMoveTo::createMoveTo(0.5f, glm::vec3(point, Volt2D::GLOBAL_Z_VALUE));
                                    auto toggleFunc = Volt2D::ActionCallFunc::createCallFunc(std::bind(&MenuScene::toggleActionFlag, this));
                                    sampleSprite->addActions({moveTo, toggleFunc}, 0);
                                    sampleSprite->runAction();
                                    delete moveTo;
                                    delete toggleFunc;
                                }
                            }
                            break;
                        case s_sprite_animation:
                            if(sampleAnimation != nullptr){
                                if(!sampleActioning){
                                    sampleActioning = true;
                                    auto moveTo = Volt2D::ActionMoveTo::createMoveTo(0.5f, glm::vec3(point, Volt2D::GLOBAL_Z_VALUE));
                                    auto toggleFunc = Volt2D::ActionCallFunc::createCallFunc(std::bind(&MenuScene::toggleActionFlag, this));
                                    sampleAnimation->addActions({moveTo, toggleFunc}, 0);
                                    sampleAnimation->runAction();
                                    delete moveTo;
                                    delete toggleFunc;
                                }
                            }
                            break;
                        case s_particle_system:
                            if(sampleParticleSystem != nullptr){
                                if(!sampleActioning){
                                    sampleActioning = true;
                                    auto moveTo = Volt2D::ActionMoveTo::createMoveTo(0.5f, glm::vec3(point, Volt2D::GLOBAL_Z_VALUE));
                                    auto toggleFunc = Volt2D::ActionCallFunc::createCallFunc(std::bind(&MenuScene::toggleActionFlag, this));
                                    sampleParticleSystem->addActions({moveTo, toggleFunc}, 0);
                                    sampleParticleSystem->runAction();
                                    delete moveTo;
                                    delete toggleFunc;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
                else{
                    //not display box. then buttons?
                    if(this->spriteBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_sprite){
                            resetPrevBtn();
                            this->curState = s_sprite;
                            this->spriteBtn->setOpacity(255.0f);
                            if(sampleSprite != nullptr){
                                this->removechild(sampleSprite, true);
                            }
                            sampleSprite = Volt2D::Sprite::createSpriteWithFrameName("sampleSprite", "demoMenu", "sample_sprite.png");
                            sampleSprite->setZDepth(z_samples);
                            sampleSprite->setPosition(glm::vec3(227, 89, 0));
                            this->addChild(sampleSprite);
                        }
                        
                    }
                    else if(this->spriteAnimationBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_sprite_animation){
                            resetPrevBtn();
                            this->curState = s_sprite_animation;
                            this->spriteAnimationBtn->setOpacity(255.0f);
                            if(sampleAnimation != nullptr){
                                this->removechild(sampleAnimation, true);
                            }
                            sampleAnimation = Volt2D::SpriteAnimation::createWithAnimation("sampleAnimation", "run", "DemoApp/MenuScene/run.png", 8, 0.125f);
                            sampleAnimation->addAnimation("idle", "DemoApp/MenuScene/idle.png", 4, 0.25f);
                            sampleAnimation->addAnimation("block", "DemoApp/MenuScene/block.png", 4, 0.25f);
                            sampleAnimation->setPosition(glm::vec3(227, 89, 0));
                            sampleAnimation->setZDepth(z_samples);
                            this->addChild(sampleAnimation);
                        }
                    }
                    else if(this->progressBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_progress){
                            resetPrevBtn();
                            
                            //prog bar bg
                            if(sampleProgBarBg != nullptr){
                                this->removechild(sampleProgBar, true);
                            }
                            //create sample prog bar bg
                            sampleProgBarBg = Volt2D::Sprite::createSpriteWithFrameName("sampleProgBarBg", "demoMenu", "sample_progress_bar_bg.png");
                            sampleProgBarBg->setPosition(glm::vec3(50, 87, 0));
                            sampleProgBarBg->setZDepth(z_samples_bg);
                            this->addChild(sampleProgBarBg);
                            
                            //prog bar
                            if(sampleProgBar != nullptr){
                                this->removechild(sampleProgBar, true);
                            }
                            //create sample prog bar
                            sampleProgBar = Volt2D::ProgressBar::createWithSpriteSheet("sampleProgBar", "demoMenu", "sample_progress_bar.png");
                            sampleProgBar->setPosition(glm::vec3(50, 87, 0));
                            sampleProgBar->setZDepth(z_samples);
                            this->addChild(sampleProgBar);
                            
                            //prog rad bg
                            if(sampleProgRadBg != nullptr){
                                this->removechild(sampleProgRadBg, true);
                            }
                            sampleProgRadBg = Volt2D::Sprite::createSpriteWithFrameName("sampleProgRadBg", "demoMenu", "sample_progress_radian_bg.png");
                            sampleProgRadBg->setOpacity(180.0f);
                            sampleProgRadBg->setPosition(glm::vec3(404, 89, 0));
                            sampleProgRadBg->setZDepth(z_samples_bg);
                            this->addChild(sampleProgRadBg);
                            
                            //create sample prog bar bg
                            if(sampleProgRad != nullptr){
                                this->removechild(sampleProgRad, true);
                            }
                            sampleProgRad = Volt2D::ProgressRadian::createWithSpriteSheet("sampleProgRad", "demoMenu", "sample_progress_radian.png");
                            sampleProgRad->setPosition(glm::vec3(404, 89, 0));
                            sampleProgRad->setZDepth(z_samples);
                            this->addChild(sampleProgRad);
                            
                            this->curState = s_progress;
                            this->progressBtn->setOpacity(255.0f);
                        }
                    }
                    else if(this->particleSysBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_particle_system){
                            resetPrevBtn();
                            this->curState = s_particle_system;
                            this->particleSysBtn->setOpacity(255.0f);
                            if(sampleParticleSystem != nullptr){
                                this->removechild(sampleParticleSystem, true);
                            }
                            sampleParticleSystem = Volt2D::ParticleSystem::createWithLuaConfig("sampleParticleSystem_magicalOrbits", "Particle/magicalOrbits.lua");
                            sampleParticleSystem->setZDepth(z_samples);
                            sampleParticleSystem->setPosition(glm::vec3(227, 89, 0));
                            this->addChild(sampleParticleSystem);
                        }
                    }
                    else if(this->textBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_text){
                            resetPrevBtn();
                            this->curState = s_text;
                            this->textBtn->setOpacity(255.0f);
                            if(sampleText != nullptr){
                                this->removechild(sampleText, true);
                            }
                            sampleText = Volt2D::Text::createText("titleText", "Lorem ipsum dolor sit amet, consectetur adipiscing elit, \nsed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris \nnisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in \nreprehenderit in voluptate velit esse cillum dolore eu fugiat \nnulla pariatur. Excepteur sint occaecat cupidatat non proident,\nsunt in culpa qui officia deserunt mollit anim id est laborum.", "UhBee Kang-Ja.ttf");
                            sampleText->setZDepth(z_samples);
                            sampleText->setScale(glm::vec3(0.5f, 0.5f, 1.0f));
                            sampleText->setPosition(glm::vec3(227, 89, 0));
                            sampleText->setColor(Volt2D::Color::WHITE);
                            this->addChild(sampleText);
                        }
                    }
                    else if(this->sceneTransitionMoveBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_st_move){
                            resetPrevBtn();
                            this->curState = s_st_move;
                            this->sceneTransitionMoveBtn->setOpacity(255.0f);
                            this->waitingTransitionMsg->setOpacity(255);
                            this->waitingTransition = true;
                        }
                    }
                    else if(this->sceneTransitionFadeBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_st_fade){
                            resetPrevBtn();
                            this->curState = s_st_fade;
                            this->sceneTransitionFadeBtn->setOpacity(255.0f);
                            this->waitingTransitionMsg->setOpacity(255);
                            this->waitingTransition = true;
                        }
                    }
                    else if(this->sceneTransitionFlipBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_st_flip){
                            resetPrevBtn();
                            this->curState = s_st_flip;
                            this->sceneTransitionFlipBtn->setOpacity(255.0f);
                            this->waitingTransitionMsg->setOpacity(255);
                            this->waitingTransition = true;
                        }
                    }
                }
            }//if mouse drag
            this->displayBoxClicked = false;
        }//if press or release
    }
    Scene::mouseButton(x, y, button, action, mods);
}

void MenuScene::mouseMove(double x, double y){
    if(this->mouseClicked){
        //dragging
        this->mouseDragged = true;
        if(this->displayBoxClicked){
            float diff_x = x - prevMousePos.x;
            float diff_y = y - prevMousePos.y;
            if(ctrlPressed){
                //scale
                switch (curState) {
                    case s_sprite:
                        sampleSprite->addScale(glm::vec3(diff_x/100.0f, diff_y/100.0f, 0));
                        break;
                    case s_sprite_animation:
                        sampleAnimation->addScale(glm::vec3(diff_x/100.0f, diff_y/100.0f, 0));
                        break;
                    case s_particle_system:
                        sampleParticleSystem->addScale(glm::vec3(diff_x/100.0f, diff_y/100.0f, 0));
                        break;
                    case s_text:
                        sampleText->addScale(glm::vec3(diff_x/100.0f, diff_y/100.0f, 0));
                        break;
                    default:
                        break;
                }
            }
            else{
                //rotate
                switch (curState) {
                    case s_sprite:
                        sampleSprite->addAngle(diff_x);
                        break;
                    case s_sprite_animation:
                        sampleAnimation->addAngle(diff_x);
                        break;
                    case s_particle_system:
                        sampleParticleSystem->addAngle(diff_x);
                        break;
                    case s_text:
                        sampleText->addAngle(diff_x);
                        break;
                    default:
                        break;
                }
            }
            prevMousePos = glm::vec2(static_cast<float>(x), static_cast<float>(y));
        }
    }
    Scene::mouseMove(x, y);
}

void MenuScene::resetPrevBtn(){
    switch (curState) {
        case s_none:
            break;
        case s_sprite:
            spriteBtn->setOpacity(defaultBtnOpacity);
            this->removechild(sampleSprite, true);
            break;
        case s_sprite_animation:
            spriteAnimationBtn->setOpacity(defaultBtnOpacity);
            this->removechild(sampleAnimation, true);
            break;
        case s_progress:
            progressBtn->setOpacity(defaultBtnOpacity);
            //prog bar
            this->removechild(sampleProgBar, true);
            this->removechild(sampleProgBarBg, true);
            //prog radian
            this->removechild(sampleProgRad, true);
            this->removechild(sampleProgRadBg, true);
            break;
        case s_particle_system:
            particleSysBtn->setOpacity(defaultBtnOpacity);
            this->removechild(sampleParticleSystem, true);
            break;
        case s_text:
            textBtn->setOpacity(defaultBtnOpacity);
            this->removechild(sampleText, true);
            break;
        case s_st_fade:
            sceneTransitionFadeBtn->setOpacity(defaultBtnOpacity);
            waitingTransition = false;
            waitingTransitionMsg->setOpacity(0);
            break;
        case s_st_move:
            sceneTransitionMoveBtn->setOpacity(defaultBtnOpacity);
            waitingTransition = false;
            waitingTransitionMsg->setOpacity(0);
            break;
        case s_st_flip:
            sceneTransitionFlipBtn->setOpacity(defaultBtnOpacity);
            waitingTransition = false;
            waitingTransitionMsg->setOpacity(0);
            break;
        default:
            break;
    }
}

void MenuScene::exit(){

}