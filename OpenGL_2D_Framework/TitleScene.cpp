//
//  TitleScene.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "TitleScene.h"

using std::cout;
using std::endl;

TitleScene::TitleScene():
bg(0),
titleButtonLayer(0)
{
    cout << "TitleScene()" << endl;
}

TitleScene::~TitleScene(){
    cout << "~TitleScene()" << endl;
    exit();
}

void TitleScene::init(){
    cout << "TitleScene::init()" << endl;
//    WinSize size = Director::getInstance().getWindowSize();
//    SoundManager::getInstance().createChannelGroup("bgmChannelGroup");
//    SoundManager::getInstance().createNewSound("titleSceneBgm", "titleSceneBgm", "title bgm.mp3");
    SoundManager* sm = Director::getInstance().getSoundManager();
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

    bg = Sprite::createSprite("titleSceneBg", "title scene/title_scene_bg.png");
    bg->setZDepth(z_bg);
    this->addChild(bg);
    
    
    FontManager::getInstance().addFont("UhBee Kang-Ja.ttf", 50);
    title = Text::createText("titleText", "Engine Test", "UhBee Kang-Ja.ttf");
    title->setColor(glm::vec3(255, 255, 255));
    title->setTextAlign(Text::TextAlign::ALIGN_LEFT);
    title->initText("Engine Test", "UhBee Kang-Ja.ttf");
    title->setZDepth(10);
    title->setPosition(glm::vec3(0, 100, 0));
    this->addChild(title);
    
    initLayers();
}

void TitleScene::initLayers(){
    titleButtonLayer = new TitleButtonLayer();
    titleButtonLayer->setName("titleButtonLayer");
    titleButtonLayer->setInputListenable(true);
//    titleButtonLayer->addPosition(glm::vec3(-535, 105, 0));
//    titleButtonLayer->setAngle(90);
    this->addChild(titleButtonLayer);
}

void TitleScene::update(){
//    if(Director::getInstance().getJoyStick(0)->keyPressed(CIRCLE)){
//        cout << "circle pressed" << endl;
    //    }
    
    PS3ControllerWrapper* joystick = Director::getInstance().getJoyStick(0);
    if(joystick->getKeyStatus(CIRCLE) == GLFW_PRESS){
        titleButtonLayer->addPosition(glm::vec3(100, 100, 0));
    }
//    if(joystick->getKeyStatus(CROSS) == GLFW_PRESS){
//        continueButton->setPosition(glm::vec3(0));
//        glm::vec3 pos = continueButton->getPosition();
//        cout << pos.x <<" " << pos.y << " "<< pos.z << endl;
//    }
    Scene::update();
}

void TitleScene::keyPressed(int key, int mods){
    if(key == GLFW_KEY_P){
        glm::vec3 bgpos = bg->getPosition();
        cout << bgpos.x << " " << bgpos.y << " " << bgpos.z << endl;
    }
    if(key == GLFW_KEY_0){
        Director::getInstance().getSoundManager()->playBGM("titleSceneBgm");
    }
    else if(key == GLFW_KEY_9){
        Director::getInstance().getSoundManager()->stopSound("titleSceneBgm");
    }
    else if(key == GLFW_KEY_8){
        Director::getInstance().getSoundManager()->pauseBGM("titleSceneBgm");
    }
    else if(key == GLFW_KEY_7){
        Director::getInstance().getSoundManager()->resumeBGM("titleSceneBgm");
    }
    else if(key == GLFW_KEY_6){
        float curChGroupVol = 0;
        if(Director::getInstance().getSoundManager()->getChannelGroupVolume("SFXGroup", curChGroupVol)){
            cout << "cur ch group vol = " << curChGroupVol << endl;
        }
        curChGroupVol+=0.1f;
        Director::getInstance().getSoundManager()->setChannelGroupVolume("SFXGroup", curChGroupVol);
        
        float curMenuBrowseVol = 0;
        if(Director::getInstance().getSoundManager()->getSoundVolume("titleSceneMenuBrowse", curMenuBrowseVol)){
            cout << "cur ch browse vol = " << curMenuBrowseVol << endl;
        }
        
        float curMenuSelectVol = 0;
        if(Director::getInstance().getSoundManager()->getSoundVolume("titleSceneMenuSelect", curMenuBrowseVol)){
            cout << "cur ch select vol = " << curMenuSelectVol << endl;
        }
        
    }
    else if(key == GLFW_KEY_5){
        float curChGroupVol = 0;
        if(Director::getInstance().getSoundManager()->getChannelGroupVolume("SFXGroup", curChGroupVol)){
            cout << "cur ch group vol = " << curChGroupVol << endl;
        }
        curChGroupVol-=0.1f;
        Director::getInstance().getSoundManager()->setChannelGroupVolume("SFXGroup", curChGroupVol);
        
        float curMenuBrowseVol = 0;
        if(Director::getInstance().getSoundManager()->getSoundVolume("titleSceneMenuBrowse", curMenuBrowseVol)){
            cout << "cur ch browse vol = " << curMenuBrowseVol << endl;
        }
        
        float curMenuSelectVol = 0;
        if(Director::getInstance().getSoundManager()->getSoundVolume("titleSceneMenuSelect", curMenuBrowseVol)){
            cout << "cur ch select vol = " << curMenuSelectVol << endl;
        }
    }
	Scene::keyPressed(key, mods);
}

void TitleScene::injectKey(){
    
}

void TitleScene::injectMouseMove(){

}

void TitleScene::exit(){
    cout << "TitleScene::exit" << endl;
}