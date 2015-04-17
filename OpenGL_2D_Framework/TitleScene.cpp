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
    bg = new Sprite();
    bg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/title scene/titleScene_bg.png");
    bg->setZ_Depth(1);
    WinSize size = Director::getInstance().getWindowSize();
    bg->setPosition(glm::vec2(size.w/2, size.h/2));
    addSprite(bg);
}

void TitleScene::keyPressed(int key){
    if(key == GLFW_KEY_ENTER){
        Director::getInstance().pushScene(new BattleScene());
        Director::getInstance().transitionToNextScene(true);
    }
}

void TitleScene::keyReleased(int key){
    
}

void TitleScene::mouseButton(int button, int action){
    
}

void TitleScene::mouseMove(double x, double y){
    
}

void TitleScene::exit(){
    cout << "TitleScene::init" << endl;
}