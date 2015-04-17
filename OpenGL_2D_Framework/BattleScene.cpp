//
//  BattleScene.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "BattleScene.h"

BattleScene::BattleScene():
        prevMousePos(glm::vec2()),
        curMousePos(glm::vec2())
{
    cout << "BattleScene()" << endl;
}

BattleScene::~BattleScene(){
    cout << "~BattleScene()" << endl;
}

void BattleScene::init(){
    bg = new Sprite();
    bg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/battle_scene_bg.png");
    bg->setZ_Depth(1);
    WinSize size = Director::getInstance().getWindowSize();
    bg->setPosition(glm::vec2(size.w/2, size.h/2));
    addSprite(bg);
    
    //create HUD Layer
    Layer* HUDLayer = new Layer;
    addLayer(HUDLayer);
    Sprite* creeper = new Sprite();
    creeper->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/boss_creeper.png");
    creeper->setPosition(glm::vec2(size.w/2, size.h/2));
    creeper->setZ_Depth(2);
    HUDLayer->addSprite(creeper);
}

//void BattleScene::update(){
//    spriteManager->update();
//}
//
//void BattleScene::render(){
//    spriteManager->render();
//}

void BattleScene::keyPressed(int key){
    
}

void BattleScene::keyReleased(int key){
    
}

void BattleScene::mouseButton(int button, int action){
    if(action == GLFW_PRESS)
        mouseClicked = true;
    else if(action == GLFW_RELEASE)
        mouseClicked = false;
}

void BattleScene::mouseMove(double x, double y){
    prevMousePos = curMousePos;
    curMousePos = glm::vec2(x, y);
    
    if(mouseClicked){
        glm::vec2 curBgPos = bg->getPosition();
        glm::vec2 cursorPosDiff = curMousePos - prevMousePos;
        cursorPosDiff.y *= (-1);
        glm::vec2 newBgPos = curBgPos + cursorPosDiff;
        int xBoundary = 320;
        int yBoundary = 180;
        WinSize size = Director::getInstance().getWindowSize();
        glm::vec2 center = glm::vec2(size.w/2, size.h/2);
        if(newBgPos.x > center.x + xBoundary){
            newBgPos.x = center.x + xBoundary;
        }
        else if(newBgPos.x < center.x - xBoundary){
            newBgPos.x = center.x - xBoundary;
        }
        
        if(newBgPos.y > center.y + yBoundary){
            newBgPos.y = center.y + yBoundary;
        }
        else if(newBgPos.y < center.y - yBoundary){
            newBgPos.y = center.y - yBoundary;
        }
        bg->setPosition(newBgPos);
    }
}

void BattleScene::exit(){
    cout << "BattleScene::init" << endl;
}