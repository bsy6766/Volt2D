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
    
    SoundManager::getInstance().createBGM("../Sound/title bgm.mp3");
    SoundManager::getInstance().playBGM();

    bg = new Sprite();
    bg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/title scene/title_scene_bg.png");
    bg->setZDepth(z_bg);
    this->addObject("title_scene_bg", bg);
    
    initLayers();
}

void TitleScene::initLayers(){
    titleButtonLayer = new TitleButtonLayer();
    titleButtonLayer->setInputListenable(true);
    this->addLayer(titleButtonLayer);
}

void TitleScene::update(){
    Scene::update();

}

void TitleScene::injectKey(){
    
}

void TitleScene::injectMouseMove(){

}

void TitleScene::exit(){
    cout << "TitleScene::exit" << endl;
}