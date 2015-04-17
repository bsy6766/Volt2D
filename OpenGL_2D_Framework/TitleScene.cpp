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

TitleScene::TitleScene(){
    cout << "TitleScene()" << endl;
}

TitleScene::~TitleScene(){
    cout << "~TitleScene()" << endl;
}

void TitleScene::init(){
    cout << "TitleScene::init()" << endl;
    //init basic stuff
//    bg = new Sprite();
//    bg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/title scene/titleScene_bg.png");
//    bg->setZ_Depth(1);
//    addSprite(bg);
    
    loadingBg = new Sprite();
    loadingBg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/loading/loading background.png");
    loadingBg->setZ_Depth(0);
    loadingBg->setPosition(glm::vec2(640, 360));
    addSprite(loadingBg);
}

void TitleScene::update(){
    spriteManager->update();
}

void TitleScene::render(){
    spriteManager->render();
}

void TitleScene::keyPressed(int key){
    
}

void TitleScene::keyReleased(int key){
    
}

void TitleScene::exit(){
    cout << "TitleScene::init" << endl;
}