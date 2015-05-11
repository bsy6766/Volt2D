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
    WinSize size = Director::getInstance().getWindowSize();
    //init basic stuff
//    bg = new Sprite();
////    bg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/title scene/titleScene_bg.png");
//    bg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/boss_creeper.png");
//    bg->setZ_Depth(2);
//    bg->type = Sprite::BILLBOARD_TYPE;
//    bg->setPosition(glm::vec2(size.w/2-100, size.h/2));
//    addSprite(bg);
//    
    ground = new Sprite();
    ground->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/battle_scene_bg.png");
    ground->setZ_Depth(1);
    ground->setPosition(size.w/2, 0, 0);
    ground->rotateSprite(90, glm::vec3(-1, 0, 0));
    addSprite(ground);
    
    FontManager::getInstance().addFont("UhBee Kang-Ja.ttf", 50);
    
    helloWorldText = new Text();
    helloWorldText->initText("Hello Ahzae from SRL! Welcome to Todayhumor! - sodmaster", "UhBee Kang-Ja.ttf");
    helloWorldText->setColor(glm::vec3(100, 200, 30));
    addText(helloWorldText);
    
    glfwSetCursorPos(window, size.w/2, size.h/2);
    cout << "init mouse pos with = (" << size.w/2 << ", " << size.h/2 << ")" << endl;
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

void TitleScene::injectKey(){
    Director &directorRef = Director::getInstance();
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        directorRef.getCameraPtr()->moveFoward();
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        directorRef.getCameraPtr()->moveBackward();
    }
    
    //A,D
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        directorRef.getCameraPtr()->moveLeft();
    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        directorRef.getCameraPtr()->moveRight();
    }
    
    //Lshift, space
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
        directorRef.getCameraPtr()->moveDown();
    }
    else if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
        directorRef.getCameraPtr()->moveUp();
    }
    
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        directorRef.getCameraPtr()->increaseSpeed();
    }
    else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        directorRef.getCameraPtr()->decreaseSpeed();
    }
    
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        directorRef.getCameraPtr()->setPosition(glm::vec3(0, 0, -77.25));
    }
}

void TitleScene::injectMouseMove(){
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    prevMousePos = curMousePos;
    curMousePos.x = x;
    curMousePos.y = y;
    
    glm::vec2 mouseDelta = curMousePos - prevMousePos;
//    if(curMousePos.x >= 1280){
//        curMousePos.x = 1280;
//        glfwSetCursorPos(window, curMousePos.x, curMousePos.y);
//    }
//    float verticalAngle = 0.15f * mouseDelta.y;
    float horizontalAngle = 0.15f * mouseDelta.x;
    Director::getInstance().getCameraPtr()->changeAngle(0.15f * mouseDelta.y, 0.15f * mouseDelta.x);
    //billboard
//    bg->rotateSprite(horizontalAngle * (-1), glm::vec3(0, 1, 0));
    
//    cout << "curMousePos = (" << x << ", " << y << ")" << endl;
}

void TitleScene::exit(){
    cout << "TitleScene::init" << endl;
}