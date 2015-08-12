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
sampleBody(0),
sampleArm1(0),
sampleArm2(0),
sampleArm3(0),
armPS(0),
level(0),
instructionMsg(0),
mouseClicked(false),
prevMousePos(0),
mouseDragged(false),
ctrlPressed(false),
bgmVol(1.0f),
sfxVol(1.0f)
{
    
}

MenuScene::~MenuScene(){
    
}

void MenuScene::init(){
    //add sounds
    Volt2D::SoundManager* sm = Volt2D::Director::getInstance().getSoundManager();
    sm->createBGM("main_bgm", "title bgm.mp3");
    sm->createSFX("browse_sfx", "title_scene_menu_browse.mp3");
    sm->createSFX("select_sfx", "title_scene_menu_select.mp3");
    sm->createSFX("1up_sfx", "1up.mp3");
    
    std::string frameName = "demoMenu";
    //create sprite sheet
    Volt2D::
    SpriteSheet::
    createSpriteSheet(frameName, "DemoApp/MenuScene/", "menu_scene_spritesheet");
    
    //init sprites from sprite sheet
    menuBg = Volt2D::Sprite::createWithSpriteSheet("menuBg",
                                                       frameName,
                                                       "menu_bg.png");
    menuBg->setZDepth(z_bg);
    this->addChild(menuBg);    
    
    float x = -700.0f - 428;
    float yGap = 42.0f;
    glm::vec2 anchor = glm::vec2(-0.5f, 0);
    
    auto delay = Volt2D::ActionDelay::createDelay(0.5f);
    auto moveRight = Volt2D::ActionMoveBy::createMoveBy(1.0f, glm::vec3(428, 0, 0));
    
    spriteBtn = Volt2D::Sprite::createWithSpriteSheet("spriteBtn",
                                                          frameName,
                                                          "sprite_btn.png");
    spriteBtn->setPosition(glm::vec3(x, 420 - yGap * 0, 0));
    spriteBtn->setAnchorPoint(anchor);
    spriteBtn->setZDepth(z_btn);
    spriteBtn->addActions({delay, moveRight}, 0);
    spriteBtn->setOpacity(defaultBtnOpacity);
    this->addChild(spriteBtn);
    
    spriteAnimationBtn = Volt2D::Sprite::createWithSpriteSheet("spriteAnimationBtn",
                                                                   frameName,
                                                                   "spriteanimation_btn.png");
    spriteAnimationBtn->setPosition(glm::vec3(x, 420 - yGap * 1, 0));
    spriteAnimationBtn->setAnchorPoint(anchor);
    spriteAnimationBtn->setZDepth(z_btn);
    spriteAnimationBtn->addActions({delay, moveRight}, 0);
    spriteAnimationBtn->setOpacity(defaultBtnOpacity);
    this->addChild(spriteAnimationBtn);
    
    progressBtn = Volt2D::Sprite::createWithSpriteSheet("progressBtn",
                                                            frameName,
                                                            "progress_btn.png");
    progressBtn->setPosition(glm::vec3(x, 420 - yGap * 2, 0));
    progressBtn->setAnchorPoint(anchor);
    progressBtn->setZDepth(z_btn);
    progressBtn->addActions({delay, moveRight}, 0);
    progressBtn->setOpacity(defaultBtnOpacity);
    this->addChild(progressBtn);
    
    particleSysBtn = Volt2D::Sprite::createWithSpriteSheet("particleSysBtn",
                                                               frameName,
                                                               "particlesystem_btn.png");
    particleSysBtn->setPosition(glm::vec3(x, 420 - yGap * 3, 0));
    particleSysBtn->setAnchorPoint(anchor);
    particleSysBtn->setZDepth(z_btn);
    particleSysBtn->addActions({delay, moveRight}, 0);
    particleSysBtn->setOpacity(defaultBtnOpacity);
    this->addChild(particleSysBtn);
    
    textBtn = Volt2D::Sprite::createWithSpriteSheet("textBtn",
                                                        frameName,
                                                        "text_btn.png");
    textBtn->setPosition(glm::vec3(x, 420 - yGap * 4, 0));
    textBtn->setAnchorPoint(anchor);
    textBtn->setZDepth(z_btn);
    textBtn->addActions({delay, moveRight}, 0);
    textBtn->setOpacity(defaultBtnOpacity);
    this->addChild(textBtn);
    
    sceneTransitionFadeBtn = Volt2D::Sprite::createWithSpriteSheet("sceneTransitionFadeBtn",
                                                                       frameName,
                                                                       "scenetransitionfade_btn.png");
    sceneTransitionFadeBtn->setPosition(glm::vec3(x, 420 - yGap * 5, 0));
    sceneTransitionFadeBtn->setAnchorPoint(anchor);
    sceneTransitionFadeBtn->setZDepth(z_btn);
    sceneTransitionFadeBtn->addActions({delay, moveRight}, 0);
    sceneTransitionFadeBtn->setOpacity(defaultBtnOpacity);
    this->addChild(sceneTransitionFadeBtn);
    
    sceneTransitionMoveBtn = Volt2D::Sprite::createWithSpriteSheet("sceneTransitionMoveBtn",
                                                                       frameName,
                                                                       "scenetransitionmove_btn.png");
    sceneTransitionMoveBtn->setPosition(glm::vec3(x, 420 - yGap * 6, 0));
    sceneTransitionMoveBtn->setAnchorPoint(anchor);
    sceneTransitionMoveBtn->setZDepth(z_btn);
    sceneTransitionMoveBtn->addActions({delay, moveRight}, 0);
    sceneTransitionMoveBtn->setOpacity(defaultBtnOpacity);
    this->addChild(sceneTransitionMoveBtn);

    sceneTransitionFlipBtn = Volt2D::Sprite::createWithSpriteSheet("sceneTransitionFlipBtn",
                                                                       frameName,
                                                                       "scenetransitionflip_btn.png");
    sceneTransitionFlipBtn->setPosition(glm::vec3(x, 420 - yGap * 7, 0));
    sceneTransitionFlipBtn->setAnchorPoint(anchor);
    sceneTransitionFlipBtn->setZDepth(z_btn);
    sceneTransitionFlipBtn->addActions({delay, moveRight}, 0);
    sceneTransitionFlipBtn->setOpacity(defaultBtnOpacity);
    this->addChild(sceneTransitionFlipBtn);
    
    soundBtn = Volt2D::Sprite::createWithSpriteSheet("soundBtn",
                                                         frameName,
                                                         "sounds_btn.png");
    soundBtn->setPosition(glm::vec3(x, 420 - yGap * 8, 0));
    soundBtn->setAnchorPoint(anchor);
    soundBtn->setZDepth(z_btn);
    soundBtn->addActions({delay, moveRight}, 0);
    soundBtn->setOpacity(defaultBtnOpacity);
    this->addChild(soundBtn);
    
    objectHierarchyBtn = Volt2D::Sprite::createWithSpriteSheet("objectHierarchyBtn",
                                                               frameName,
                                                               "object_hierarchy_btn.png");
    objectHierarchyBtn->setPosition(glm::vec3(x, 420 - yGap * 9, 0));
    objectHierarchyBtn->setAnchorPoint(anchor);
    objectHierarchyBtn->setZDepth(z_btn);
    objectHierarchyBtn->addActions({delay, moveRight}, 0);
    objectHierarchyBtn->setOpacity(defaultBtnOpacity);
    this->addChild(objectHierarchyBtn);
    
    displayBorderline = Volt2D::Sprite::createWithSpriteSheet("displayFrame",
                                                                  frameName,
                                                                  "display_borderline.png");
    displayBorderline->setPosition(glm::vec3(227, 89, 0));
    displayBorderline->setZDepth(z_dispaly_frame);
    displayBorderline->setOpacity(0);
    auto fadeIn = Volt2D::ActionFadeTo::createFadeTo(1.0f, 255.0f);
    displayBorderline->addActions({delay, fadeIn}, 0);
    this->addChild(displayBorderline);
    
    volumeLabel = Volt2D::Sprite::createWithSpriteSheet("volumeLabel",
                                                            frameName,
                                                            "sound_volume_display.png");
    volumeLabel->setPosition(glm::vec3(227, 173, 0));
    volumeLabel->setZDepth(z_samples);
    volumeLabel->setOpacity(0);
    this->addChild(volumeLabel);
    
    bgmVolBar = Volt2D::ProgressBar::createWithSpriteSheet("bgmVolBar",
                                                           frameName,
                                                           "sound_bar.png");
    bgmVolBar->setPosition(glm::vec3(39, 27, 0));
    bgmVolBar->setZDepth(z_samples);
    bgmVolBar->setOpacity(0);
    this->addChild(bgmVolBar);
    
    sfxVolBar = Volt2D::ProgressBar::createWithSpriteSheet("sfxVolBar",
                                                           frameName,
                                                           "sound_bar.png");
    sfxVolBar->setPosition(glm::vec3(424, 27, 0));
    sfxVolBar->setZDepth(z_samples);
    sfxVolBar->setOpacity(0);
    this->addChild(sfxVolBar);
    
    instructionBox = Volt2D::Sprite::createWithSpriteSheet("instructionBox",
                                                               frameName,
                                                               "instruction_box.png");
    instructionBox->setPosition(glm::vec3(0, -550, 0));
    auto moveUp = Volt2D::ActionMoveBy::createMoveBy(1.0f, glm::vec3(0, 200.0f, 0));
    instructionBox->addActions({delay, moveUp}, 0);
    this->addChild(instructionBox);
    
    delete delay;
    delete moveUp;
    delete fadeIn;
    delete moveRight;
    
    //add font
    Volt2D::FontManager::getInstance().addFont("UhBee Kang-Ja.ttf", 50);
    
    waitingTransitionMsg = Volt2D::Sprite::createWithSpriteSheet("waitingTransition", frameName, "waiting_transition.png");
    waitingTransitionMsg->setZDepth(z_samples);
    waitingTransitionMsg->setPosition(glm::vec3(227, 89, 0));
    waitingTransitionMsg->setOpacity(0);
    this->addChild(waitingTransitionMsg);
    
    exitMsgWindow = Volt2D::Sprite::createWithSpriteSheet("exitMsgWindow", frameName, "exit_msg_window.png");
    exitMsgWindow->setZDepth(z_exit);
    exitMsgWindow->setOpacity(0);
    this->addChild(exitMsgWindow);
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
    soundBtn->runAction();
    objectHierarchyBtn->runAction();
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
            exitMsgWindow->setOpacity(0);
        }
        else{
            //show exit prompt
            this->waitingExit = true;
            exitMsgWindow->setOpacity(255.0f);

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
            case s_sound:
                Volt2D::Director::getInstance().getSoundManager()->playBGM("main_bgm");
                break;
            case s_text:
                sampleText->setColor(Volt2D::Color::VIOLET);
                break;
            case s_object_hierarchy:
                //add level
                switch (level) {
                    case 0:
                    {
                        level = 1;
                        if(sampleArm1 != nullptr){
                            this->removechild(sampleArm1, true);
                        }
                        sampleArm1 = Volt2D::Sprite::createWithSpriteSheet("sampleArm1", "demoMenu", "sample_arm.png");
                        sampleArm1->setAnchorPoint(glm::vec2(-0.5, 0));
                        sampleArm1->setPosition(glm::vec3(39, 0, 0));
                        sampleArm1->setZDepth(z_samples+1);
                        auto rotateToLeft = Volt2D::ActionRotateTo::createRotateTo(1.0f, -45.0f, RotationType::LEFT);
                        auto rotateToRight = Volt2D::ActionRotateTo::createRotateTo(1.0f, 45.0f);
                        
                        sampleArm1->addActions({rotateToLeft, rotateToRight}, -1);
                        this->sampleBody->addChild(sampleArm1);
                        sampleArm1->runAction();
                        delete rotateToLeft;
                        delete rotateToRight;
                    }
                        break;
                    case 1:
                    {
                        level = 2;
                        if(sampleArm2 != nullptr){
                            this->removechild(sampleArm2, true);
                        }
                        sampleArm2 = Volt2D::Sprite::createWithSpriteSheet("sampleArm2", "demoMenu", "sample_arm.png");
                        sampleArm2->setAnchorPoint(glm::vec2(-0.5, 0));
                        sampleArm2->setPosition(glm::vec3(78, 0, 0));
                        sampleArm2->setZDepth(z_samples+2);
                        auto rotateToLeft = Volt2D::ActionRotateTo::createRotateTo(1.0f, -45.0f, RotationType::LEFT);
                        auto rotateToRight = Volt2D::ActionRotateTo::createRotateTo(1.0f, 45.0f);
                        
                        sampleArm2->addActions({rotateToLeft, rotateToRight}, -1);
                        sampleArm1->addChild(sampleArm2);
                        delete rotateToLeft;
                        delete rotateToRight;
                        sampleArm2->runAction();
                    }
                        break;
                    case 2:
                    {
                        level = 3;
                        if(sampleArm3 != nullptr){
                            this->removechild(sampleArm3, true);
                        }
                        sampleArm3 = Volt2D::Sprite::createWithSpriteSheet("sampleArm3", "demoMenu", "sample_arm.png");
                        sampleArm3->setAnchorPoint(glm::vec2(-0.5, 0));
                        sampleArm3->setPosition(glm::vec3(78, 0, 0));
                        sampleArm3->setZDepth(z_samples+3);
                        auto rotateToLeft = Volt2D::ActionRotateTo::createRotateTo(1.0f, -45.0f, RotationType::LEFT);
                        auto rotateToRight = Volt2D::ActionRotateTo::createRotateTo(1.0f, 45.0f);
                        
                        sampleArm3->addActions({rotateToLeft, rotateToRight}, -1);
                        sampleArm2->addChild(sampleArm3);
                        delete rotateToLeft;
                        delete rotateToRight;
                        sampleArm3->runAction();
                    }
                        break;
                        
                    default:
                        break;
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
            case s_sound:
                Volt2D::Director::getInstance().getSoundManager()->stopSound("main_bgm");
                break;
            case s_text:
                sampleText->setColor(Volt2D::Color::MIDNIGHTBLUE);
                break;
            case s_object_hierarchy:
                switch (level) {
                    case 1:
                    {
                        sampleBody->removechild(sampleArm1, true);
                        sampleArm1 = nullptr;
                        level = 0;
                    }
                        break;
                    case 2:
                    {
                        sampleArm1->removechild(sampleArm2, true);
                        sampleArm2 = nullptr;
                        level = 1;
                    }
                        break;
                    case 3:
                    {
                        if(armPS != nullptr) {
                            sampleArm3->removechild(armPS, true);
                            armPS = nullptr;
                        }
                        sampleArm2->removechild(sampleArm3, true);
                        sampleArm3 = nullptr;
                        level = 2;
                    }
                        break;
                    default:
                        break;
                }
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
            case s_sound:
                Volt2D::Director::getInstance().getSoundManager()->pauseBGM("main_bgm");
                break;
            case s_text:
                sampleText->setColor(Volt2D::Color::LIME);
                break;
            case s_object_hierarchy:
                if(level == 3){
                    if(armPS != nullptr){
                        this->removechild(armPS, true);
                    }
                    armPS = Volt2D::ParticleSystem::createWithLuaConfig("armPS", "Particle/magicalOrbits.lua");
                    armPS->setZDepth(z_samples+4);
                    armPS->setPosition(glm::vec3(78, 0, 0));
                    sampleArm3->addChild(armPS);
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
            case s_sound:
                this->bgmVol -= 0.2f;
                if(bgmVol < 0)
                    bgmVol = 0;
                else if(bgmVol > 1.0f)
                    bgmVol = 1.0f;
                Volt2D::Director::getInstance().getSoundManager()->setSoundVolume("main_bgm", bgmVol);
                bgmVolBar->setPercentage(bgmVol * 100.0f);
                break;
            case s_text:
                sampleText->setLabel("1234567890");
                break;
            default:
                break;
        }
    }
    else if(key == GLFW_KEY_5){
        if(curState == s_sound){
            this->bgmVol += 0.2f;
            if(bgmVol < 0)
                bgmVol = 0;
            else if(bgmVol > 1.0f)
                bgmVol = 1.0f;
            Volt2D::Director::getInstance().getSoundManager()->setSoundVolume("main_bgm", bgmVol);
            bgmVolBar->setPercentage(bgmVol * 100.0f);
        }
        else if(curState == s_text){
            sampleText->setLabel("Lorem ipsum dolor sit amet, consectetur adipiscing elit, \nsed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris \nnisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in \nreprehenderit in voluptate velit esse cillum dolore eu fugiat \nnulla pariatur. Excepteur sint occaecat cupidatat non proident,\nsunt in culpa qui officia deserunt mollit anim id est laborum.");
        }
    }
    else if(key == GLFW_KEY_6){
        if(curState == s_sound){
            Volt2D::Director::getInstance().getSoundManager()->playSFX("select_sfx", sfxVol);
        }
        else if(curState == s_text){
            sampleText->setAlign(Volt2D::TEXT_ALIGN::ALIGN_LEFT);
        }
    }
    else if(key == GLFW_KEY_7){
        if(curState == s_sound){
            Volt2D::Director::getInstance().getSoundManager()->playSFX("1up_sfx", sfxVol);
        }
        else if(curState == s_text){
            sampleText->setAlign(Volt2D::TEXT_ALIGN::ALIGN_CENTER);
        }
    }
    else if(key == GLFW_KEY_8){
        if(curState == s_sound){
            this->sfxVol -= 0.2f;
            if (this->sfxVol < 0)
                this->sfxVol = 0;
            else if(this->sfxVol > 1.0f)
                this->sfxVol = 1.0f;
            sfxVolBar->setPercentage(sfxVol * 100.0f);
        }
        else if(curState == s_text){
            sampleText->setAlign(Volt2D::TEXT_ALIGN::ALIGN_RIGHT);
        }
    }
    else if(key == GLFW_KEY_9){
        if(curState == s_sound){
            this->sfxVol += 0.2f;
            if (this->sfxVol < 0)
                this->sfxVol = 0;
            else if(this->sfxVol > 1.0f)
                this->sfxVol = 1.0f;
            sfxVolBar->setPercentage(sfxVol * 100.0f);
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
                    //display box clicked
                    auto moveTo = Volt2D::ActionMoveTo::createMoveTo(0.5f, glm::vec3(point, Volt2D::GLOBAL_Z_VALUE));
                    auto toggleFunc = Volt2D::ActionCallFunc::createCallFunc(std::bind(&MenuScene::toggleActionFlag, this));
                    switch (curState) {
                        case s_sprite:
                            if(sampleSprite != nullptr){
                                if(!sampleActioning){
                                    sampleActioning = true;
                                    sampleSprite->addActions({moveTo, toggleFunc}, 0);
                                    sampleSprite->runAction();
                                }
                            }
                            break;
                        case s_sprite_animation:
                            if(sampleAnimation != nullptr){
                                if(!sampleActioning){
                                    sampleActioning = true;
                                    sampleAnimation->addActions({moveTo, toggleFunc}, 0);
                                    sampleAnimation->runAction();
                                }
                            }
                            break;
                        case s_particle_system:
                            if(sampleParticleSystem != nullptr){
                                if(!sampleActioning){
                                    sampleActioning = true;
                                    sampleParticleSystem->addActions({moveTo, toggleFunc}, 0);
                                    sampleParticleSystem->runAction();
                                }
                            }
                            break;
                        case s_text:
                            if(sampleText != nullptr){
                                if(!sampleActioning){
                                    sampleActioning = true;
                                    sampleText->addActions({moveTo, toggleFunc}, 0);
                                    sampleText->runAction();
                                }
                            }
                            break;
                        case s_object_hierarchy:
                            if(sampleBody != nullptr){
                                if(!sampleActioning){
                                    sampleActioning = true;
                                    sampleBody->addActions({moveTo, toggleFunc}, 0);
                                    sampleBody->runAction();
                                }
                            }
                        default:
                            break;
                    }
                    delete moveTo;
                    delete toggleFunc;
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
                            sampleSprite = Volt2D::Sprite::createWithSpriteSheet("sampleSprite", "demoMenu", "sample_sprite.png");
                            sampleSprite->setZDepth(z_samples);
                            sampleSprite->setPosition(glm::vec3(227, 89, 0));
                            this->addChild(sampleSprite);
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "sprite_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -350, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
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
                            
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "spriteanimation_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -350, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
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
                            sampleProgBarBg = Volt2D::Sprite::createWithSpriteSheet("sampleProgBarBg", "demoMenu", "sample_progress_bar_bg.png");
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
                            sampleProgRadBg = Volt2D::Sprite::createWithSpriteSheet("sampleProgRadBg", "demoMenu", "sample_progress_radian_bg.png");
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
                            
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "progress_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -350, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
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
                            
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "particlesystem_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -350, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
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
                            sampleText = Volt2D::Text::create("sampleText", "Lorem ipsum dolor sit amet, consectetur adipiscing elit, \nsed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris \nnisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in \nreprehenderit in voluptate velit esse cillum dolore eu fugiat \nnulla pariatur. Excepteur sint occaecat cupidatat non proident,\nsunt in culpa qui officia deserunt mollit anim id est laborum.", "UhBee Kang-Ja.ttf", Volt2D::TEXT_ALIGN::ALIGN_RIGHT, Volt2D::Color::WHITE, Volt2D::TEXT_TYPE::DYNAMIC);
                            sampleText->setZDepth(z_samples);
                            sampleText->setScale(glm::vec3(0.5f, 0.5f, 1.0f));
                            sampleText->setPosition(glm::vec3(227, 89, 0));
                            sampleText->setColor(Volt2D::Color::WHITE);
                            this->addChild(sampleText);
                            
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "text_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -374, 0));
                            this->addChild(instructionMsg);
                        }
                    }
                    else if(this->sceneTransitionMoveBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_st_move){
                            resetPrevBtn();
                            this->curState = s_st_move;
                            this->sceneTransitionMoveBtn->setOpacity(255.0f);
                            this->waitingTransitionMsg->setOpacity(255);
                            this->waitingTransition = true;
                            
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "transition_direction_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -350, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
                        }
                    }
                    else if(this->sceneTransitionFadeBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_st_fade){
                            resetPrevBtn();
                            this->curState = s_st_fade;
                            this->sceneTransitionFadeBtn->setOpacity(255.0f);
                            this->waitingTransitionMsg->setOpacity(255);
                            this->waitingTransition = true;
                            
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "transition_color_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -350, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
                        }
                    }
                    else if(this->sceneTransitionFlipBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_st_flip){
                            resetPrevBtn();
                            this->curState = s_st_flip;
                            this->sceneTransitionFlipBtn->setOpacity(255.0f);
                            this->waitingTransitionMsg->setOpacity(255);
                            this->waitingTransition = true;
                            
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "transition_direction_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -350, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
                        }
                    }
                    else if(this->soundBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_sound){
                            resetPrevBtn();
                            this->curState = s_sound;
                            this->soundBtn->setOpacity(255.0f);
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "sound_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -374, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
                            bgmVolBar->setOpacity(255.0f);
                            sfxVolBar->setOpacity(255.0f);
                            volumeLabel->setOpacity(255.0f);
                        }
                    }
                    else if(this->objectHierarchyBtn->getBoundingBox()->containsPoint(point)){
                        if(curState != s_object_hierarchy){
                            resetPrevBtn();
                            this->curState = s_object_hierarchy;
                            this->objectHierarchyBtn->setOpacity(255.0f);
                            if(instructionMsg != nullptr){
                                this->removechild(instructionMsg, true);
                            }
                            instructionMsg = Volt2D::Sprite::createWithSpriteSheet("instructionMsg", "demoMenu", "object_hierarchy_instruction.png");
                            instructionMsg->setAnchorPoint(glm::vec2(-0.5, 0));
                            instructionMsg->setPosition(glm::vec3(-704, -374, 0));
                            this->addChild(instructionMsg);
                            Volt2D::Director::getInstance().getSoundManager()->playSFX("browse_sfx");
                            
                            sampleBody = Volt2D::Sprite::createWithSpriteSheet("samplebody", "demoMenu", "sample_body.png");
                            sampleBody->setPosition(glm::vec3(227, 89, 0));
                            sampleBody->setZDepth(z_samples);
                            this->addChild(sampleBody);
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
                    case s_object_hierarchy:
                        sampleBody->addAngle(diff_x);
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
            this->removechild(instructionMsg, true);
            sampleSprite = nullptr;
            instructionMsg = nullptr;
            break;
        case s_sprite_animation:
            spriteAnimationBtn->setOpacity(defaultBtnOpacity);
            this->removechild(sampleAnimation, true);
            this->removechild(instructionMsg, true);
            sampleAnimation = nullptr;
            instructionMsg = nullptr;
            break;
        case s_progress:
            progressBtn->setOpacity(defaultBtnOpacity);
            //prog bar
            this->removechild(sampleProgBar, true);
            this->removechild(sampleProgBarBg, true);
            //prog radian
            this->removechild(sampleProgRad, true);
            this->removechild(sampleProgRadBg, true);
            this->removechild(instructionMsg, true);
            sampleProgBar = nullptr;
            sampleProgBarBg = nullptr;
            sampleProgRad = nullptr;
            sampleProgRadBg = nullptr;
            instructionMsg = nullptr;
            break;
        case s_particle_system:
            particleSysBtn->setOpacity(defaultBtnOpacity);
            this->removechild(sampleParticleSystem, true);
            this->removechild(instructionMsg, true);
            sampleParticleSystem = nullptr;
            instructionMsg = nullptr;
            break;
        case s_text:
            textBtn->setOpacity(defaultBtnOpacity);
            this->removechild(sampleText, true);
            sampleText = nullptr;
            this->removechild(instructionMsg, true);
            instructionMsg = nullptr;
            break;
        case s_st_fade:
            sceneTransitionFadeBtn->setOpacity(defaultBtnOpacity);
            waitingTransition = false;
            waitingTransitionMsg->setOpacity(0);
            this->removechild(instructionMsg, true);
            instructionMsg = nullptr;
            break;
        case s_st_move:
            sceneTransitionMoveBtn->setOpacity(defaultBtnOpacity);
            waitingTransition = false;
            waitingTransitionMsg->setOpacity(0);
            this->removechild(instructionMsg, true);
            instructionMsg = nullptr;
            break;
        case s_st_flip:
            sceneTransitionFlipBtn->setOpacity(defaultBtnOpacity);
            waitingTransition = false;
            waitingTransitionMsg->setOpacity(0);
            this->removechild(instructionMsg, true);
            instructionMsg = nullptr;
            break;
        case s_sound:
            soundBtn->setOpacity(defaultBtnOpacity);
            this->removechild(instructionMsg, true);
            Volt2D::Director::getInstance().getSoundManager()->stopSound("main_bgm");
            bgmVolBar->setOpacity(0);
            sfxVolBar->setOpacity(0);
            volumeLabel->setOpacity(0);
            instructionMsg = nullptr;
            break;
        case s_object_hierarchy:
            objectHierarchyBtn->setOpacity(defaultBtnOpacity);
            this->removechild(instructionMsg, true);
            if(sampleArm3 != nullptr)
                sampleArm2->removechild(sampleArm3, true);
            if(sampleArm2 != nullptr)
                sampleArm1->removechild(sampleArm2, true);
            if(sampleArm1 != nullptr)
                sampleBody->removechild(sampleArm1, true);
            this->removechild(sampleBody, true);
            sampleBody = nullptr;
            sampleArm1 = nullptr;
            sampleArm2 = nullptr;
            sampleArm3 = nullptr;
            instructionMsg = nullptr;
            level = 0;
            break;
        default:
            break;
    }
}

void MenuScene::exit(){

}