//
//  TitleScene.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 4/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "TitleScene.h"

using namespace Volt2D;

TitleScene::TitleScene():
bg(0),
titleButtonLayer(0)
{
}

TitleScene::~TitleScene(){

}

void TitleScene::init(){
//    cout << "TitleScene::init()" << endl;
//    WinSize size = Volt2D::Director::getInstance().getWindowSize();
//    SoundManager::getInstance().createChannelGroup("bgmChannelGroup");
//    SoundManager::getInstance().createNewSound("titleSceneBgm", "titleSceneBgm", "title bgm.mp3");
    Volt2D::SoundManager* sm = Volt2D::Director::getInstance().getSoundManager();
    sm->createBGM("titleSceneBgm", "title bgm.mp3");
    sm->createSFX("titleSceneMenuBrowse", "title_scene_menu_browse.mp3");
    sm->createSFX("titleSceneMenuSelect", "title_scene_menu_select.mp3");
//    sm->createSFX("titleSceneMenuSelect", "title bgm.mp3");
//    sm->createChannelGroup("SFXGroup");
    sm->createChannelGroup("BGMGroup");
//    sm->bindSoundToChannelGroup("titleSceneMenuBrowse", "SFXGroup");
//    sm->bindSoundToChannelGroup("titleSceneMenuSelect", "SFXGroup");
    sm->bindSoundToChannelGroup("titleSceneBgm", "BGMGroup");
//    SoundManager::getInstance().addSoundToChannelGroup("bgmChannelGroup", "titleSceneBgm");

    SpriteSheet::createSpriteSheet("titleSceneSpriteSheet", "title scene/title_scene_sprite_sheet.png", "title scene/title_scene_sprite_sheet.xml");
    
//    bg = Sprite::createSprite("titleSceneBg", "title scene/title_scene_bg.png");
    bg = Sprite::createSpriteWithFrameName("titleSceneBg", "titleSceneSpriteSheet", "title_scene_bg.png");
    bg->setZDepth(z_bg);
//    bg->setAnchrPoint(glm::vec2(0.5, 0.5));
    this->addChild(bg);
    
//    auto delayIt = ActionDelay::createDelay(2);
//    auto rotateIt = ActionRotateTo::createRotateTo(2, 180);
//    auto rotateIt2 = ActionRotateTo::createRotateTo(2, 270);
//    auto moveIt = ActionMoveTo::createMoveTo(2, glm::vec3(0, 100, 0));
//    bg->addActions({delayIt, rotateIt, moveIt, rotateIt2}, 0);
//    bg->runAction();
//    delete rotateIt;
//    delete delayIt;
//    delete rotateIt2;
//    delete moveIt;
    
    title = Sprite::createSprite("titleSceneTitle", "title scene/scrolls_title.png");
//    title = Sprite::createSpriteWithFrameName("titleSceneTitle", "titleSceneSpriteSheet", "title.png");
    title->setZDepth(z_title);
    title->setY(170);
//    auto delay = ActionDelay::createDelay(2);
//    auto rotateTo = ActionRotateTo::createRotateTo(1, 80, RotationType::LEFT);
//    auto rotateTo2 = ActionRotateTo::createRotateTo(1, 40);
//    auto print = ActionCallFunc::createCallFunc(std::bind(&TitleScene::printAngle, this));
//    title->addActions({delay, print, rotateTo, print, delay, rotateTo2, print, delay, rotateTo, print, delay, rotateTo2, print}, 0);
//    title->runAction();
//    delete rotateTo;
    this->addChild(title);
    
    version = Sprite::createSprite("titleSceneTitle", "title scene/version.png");
    version->setZDepth(z_title);
    version->setX(-648);
    version->setY(-432);
    this->addChild(version);
    
    Text* title;
    FontManager::getInstance().addFont("UhBee Kang-Ja.ttf", 50);
    title = Text::createText("titleText", "Engine Test", "UhBee Kang-Ja.ttf");
    title->setColor(Color::WHITE);
//    title->setTextAlign(Text::TextAlign::ALIGN_LEFT);
//    title->initText("Engine Test", "UhBee Kang-Ja.ttf");
    title->setZDepth(z_text);
//    title->setPosition(glm::vec3(0, 100, 0));
    this->addChild(title);
    
    character = SpriteAnimation::createWithAnimation("character", "run", "title scene/run.png", 8, 0.1);
    character->setZDepth(999);
    character->addPosition(glm::vec3(-100, -100, 0));
	character->setZDepth(z_animation);
//    character->addActions({delay, rotateTo}, 0);
//    character->runAction();
    this->addChild(character);
    
    auto delay = ActionDelay::createDelay(1);
    auto moveTo = ActionMoveTo::createMoveTo(8, glm::vec3(600, -250, 0));
    
    fireBall = ParticleSystem::createWithLuaConfig("fireBallParticle", "Particle/fireBall.lua");
    fireBall->setPosition(glm::vec3(-600, -250, 0));
    fireBall->addActions({delay, moveTo, delay}, 0);
	fireBall->setZDepth(z_fireball);
    
    magicalOrbits = ParticleSystem::createWithLuaConfig("testParticle", "Particle/magicalOrbits.lua");
    magicalOrbits->setPosition(vec3(-400, 0, 0));
	magicalOrbits->setZDepth(z_particles);
    
    flame = ParticleSystem::createWithLuaConfig("flameParticle", "Particle/flame.lua");
	flame->setPosition(vec3(-200, 0, 0));
	flame->setZDepth(z_particles);
    
    blueMeteor = ParticleSystem::createWithLuaConfig("blueMeteorParticle", "Particle/blueMeteor.lua");
	blueMeteor->setPosition(vec3(50, 0, 0));
	blueMeteor->setZDepth(z_particles);
    
    muhanDojun = ParticleSystem::createWithLuaConfig("muhanDojunParticle", "Particle/muhanDojun.lua");
	muhanDojun->setPosition(vec3(300, 100, 0))  ;
	muhanDojun->setZDepth(z_particles);
    
    initLayers();
}

void TitleScene::printAngle(){
    cout << "angle = " << title->getAngle() << endl;
}

void TitleScene::initLayers(){
    titleButtonLayer = new TitleButtonLayer();
    titleButtonLayer->setName("titleButtonLayer");
    titleButtonLayer->setInputListenable(true);
//    titleButtonLayer->addPosition(glm::vec3(-535, 105, 0));
//    titleButtonLayer->setAngle(90);
    this->addChild(titleButtonLayer);
}

void TitleScene::update(double dt){
//    if(Volt2D::Director::getInstance().getJoyStick(0)->keyPressed(CIRCLE)){
//        cout << "circle pressed" << endl;
    //    }
    
    PS3ControllerWrapper* joystick = Volt2D::Director::getInstance().getJoyStick(0);
    if(joystick){
        if(joystick->getKeyStatus(CIRCLE) == GLFW_PRESS){
            titleButtonLayer->addPosition(glm::vec3(100, 100, 0));
        }
    }
//    if(joystick->getKeyStatus(CROSS) == GLFW_PRESS){
//        continueButton->setPosition(glm::vec3(0));
//        glm::vec3 pos = continueButton->getPosition();
//        cout << pos.x <<" " << pos.y << " "<< pos.z << endl;
//    }
    Scene::update(dt);
}

void TitleScene::keyPressed(int key, int mods){
//    if(key == GLFW_KEY_B){
//        magicalOrbits->addPosition(vec3(100, 0, 0));
//    }
//    else if(key == GLFW_KEY_V){
//        magicalOrbits->addPosition(vec3(-100, 0, 0));
//    }
    
    if(key == GLFW_KEY_M){
        this->addChild(magicalOrbits);
        this->addChild(flame);
        this->addChild(blueMeteor);
        this->addChild(muhanDojun);
        fireBall->runAction();
        this->addChild(fireBall);
    }
    if(key == GLFW_KEY_N){
        magicalOrbits->resume();
        flame->resume();
        blueMeteor->resume();
        muhanDojun->resume();
        fireBall->resume();
    }
    if(key == GLFW_KEY_COMMA){
        magicalOrbits->reset(true);
        flame->reset(true);
        blueMeteor->reset(true);
        muhanDojun->reset(true);
        fireBall->reset(true);
    }
    
    if(key == GLFW_KEY_P){
        glm::vec3 bgpos = bg->getPosition();
        cout << bgpos.x << " " << bgpos.y << " " << bgpos.z << endl;
    }
    if(key == GLFW_KEY_0){
        Volt2D::Director::getInstance().getSoundManager()->playBGM("titleSceneBgm");
    }
    else if(key == GLFW_KEY_9){
        Volt2D::Director::getInstance().getSoundManager()->stopSound("titleSceneBgm");
    }
    else if(key == GLFW_KEY_8){
        Volt2D::Director::getInstance().getSoundManager()->pauseBGM("titleSceneBgm");
    }
    else if(key == GLFW_KEY_7){
        Volt2D::Director::getInstance().getSoundManager()->resumeBGM("titleSceneBgm");
    }
    else if(key == GLFW_KEY_6){
        float curChGroupVol = 0;
        if(Volt2D::Director::getInstance().getSoundManager()->getChannelGroupVolume("SFXGroup", curChGroupVol)){
            cout << "cur ch group vol = " << curChGroupVol << endl;
        }
        curChGroupVol+=0.1f;
        Volt2D::Director::getInstance().getSoundManager()->setChannelGroupVolume("SFXGroup", curChGroupVol);
        
        float curMenuBrowseVol = 0;
        if(Volt2D::Director::getInstance().getSoundManager()->getSoundVolume("titleSceneMenuBrowse", curMenuBrowseVol)){
            cout << "cur ch browse vol = " << curMenuBrowseVol << endl;
        }
        
        float curMenuSelectVol = 0;
        if(Volt2D::Director::getInstance().getSoundManager()->getSoundVolume("titleSceneMenuSelect", curMenuBrowseVol)){
            cout << "cur ch select vol = " << curMenuSelectVol << endl;
        }
        
    }
    else if(key == GLFW_KEY_5){
        float curChGroupVol = 0;
        if(Volt2D::Director::getInstance().getSoundManager()->getChannelGroupVolume("SFXGroup", curChGroupVol)){
            cout << "cur ch group vol = " << curChGroupVol << endl;
        }
        curChGroupVol-=0.1f;
        Volt2D::Director::getInstance().getSoundManager()->setChannelGroupVolume("SFXGroup", curChGroupVol);
        
        float curMenuBrowseVol = 0;
        if(Volt2D::Director::getInstance().getSoundManager()->getSoundVolume("titleSceneMenuBrowse", curMenuBrowseVol)){
            cout << "cur ch browse vol = " << curMenuBrowseVol << endl;
        }
        
        float curMenuSelectVol = 0;
        if(Volt2D::Director::getInstance().getSoundManager()->getSoundVolume("titleSceneMenuSelect", curMenuBrowseVol)){
            cout << "cur ch select vol = " << curMenuSelectVol << endl;
        }
    }
	Scene::keyPressed(key, mods);
}

void TitleScene::mouseButton(double x, double y, int button, int action){
//    ps->setPosition(glm::vec3(x, y, 0));
    Scene::mouseButton(x, y, button, action);
}

void TitleScene::injectKey(){
    
}

void TitleScene::injectMouseMove(){

}

void TitleScene::exit(){
    //You can delete other objects here
}