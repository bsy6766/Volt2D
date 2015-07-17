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
}

void TitleScene::init(){
    cout << "TitleScene::init()" << endl;
//    WinSize size = Director::getInstance().getWindowSize();
//    SoundManager::getInstance().createChannelGroup("bgmChannelGroup");
//    SoundManager::getInstance().createNewSound("titleSceneBgm", "titleSceneBgm", "title bgm.mp3");
    Director::getInstance().getSoundManager()->createBGM("titleSceneBgm", "title bgm.mp3");
    Director::getInstance().getSoundManager()->createSFX("titleSceneMenuBrowse", "title_scene_menu_browse.mp3");
    Director::getInstance().getSoundManager()->createSFX("titleSceneMenuSelect", "title_scene_menu_select.mp3");
//    SoundManager::getInstance().addSoundToChannelGroup("bgmChannelGroup", "titleSceneBgm");

    bg = new Sprite();
    bg->initSpriteWithTexture("title scene/title_scene_bg.png");
    bg->setZDepth(z_bg);
    this->addObject("title_scene_bg", bg);
    
    
    FontManager::getInstance().addFont("UhBee Kang-Ja.ttf", 50);
    title = new Text();
    title->setColor(glm::vec3(255, 255, 255));
    title->setTextAlign(Text::TextAlign::ALIGN_LEFT);
    //    title->initText("Hello world!\nNew line with left align!\nOpenGL with TTF font.\n`!@#$%^&*()-+_=", "Arial.ttf");
    title->initText("Engine Test", "UhBee Kang-Ja.ttf");
    title->setZDepth(10);
    title->setPosition(glm::vec3(0, 200, 0));
    this->addObject("hellowWorldText", title);
    
    initLayers();
}

void TitleScene::initLayers(){
    titleButtonLayer = new TitleButtonLayer();
    titleButtonLayer->setInputListenable(true);
    this->addLayer(titleButtonLayer);
}

void TitleScene::update(){
//    if(Director::getInstance().getJoyStick(0)->keyPressed(CIRCLE)){
//        cout << "circle pressed" << endl;
//    }
    Scene::update();
}

void TitleScene::keyPressed(int key, int mods){
    if(key == GLFW_KEY_0){
        Director::getInstance().getSoundManager()->playSound("titleSceneBgm");
    }
    else if(key == GLFW_KEY_9){
        Director::getInstance().getSoundManager()->pauseSound("titleSceneBgm");
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