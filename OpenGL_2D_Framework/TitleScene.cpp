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

    bg = new Sprite();
    bg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/bg_grid.png");
    bg->setZDepth(0);
    this->addObject("bg", bg);
    
    creeper = new Sprite();
    creeper->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/boss_creeper.png");
    creeper->setZDepth(1);
//    creeper->type = Sprite::BILLBOARD_TYPE;
    creeper->setPosition(glm::vec3(100, 0, 0));
    this->addObject("creeper", creeper);
    
    loadingBar = new ProgressBar();
    loadingBar->initProgressBar(GL_TEXTURE_2D, "../Texture/battle scene/progressbar.png");
    loadingBar->setZDepth(2);
    loadingBar->setPercentage(75);
    loadingBar->setPosition(glm::vec3(-370, 317, 0));
    this->addObject("loadingBar", loadingBar);
    
    loadingBarBg = new Sprite();
    loadingBarBg->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/progressbar_bg.png");
    loadingBarBg->setPosition(glm::vec3(-370, 317, 0));
    loadingBarBg->setZDepth(1);
    this->addObject("loadingBarBg", loadingBarBg);
    
    cooldownIcon = new ProgressRadian();
    cooldownIcon->initProgressRadian(GL_TEXTURE_2D, "../Texture/battle scene/fireball_icon.png");
    cooldownIcon->setPosition(glm::vec3(200, -150, 0));
    cooldownIcon->setZDepth(30);
    cooldownIcon->setPercentage(0);
    this->addObject("cooldownIcon", cooldownIcon);
    
    //scope in init()
    ActionDelay actionDelayBtw;
    actionDelayBtw.initDelay(1);
    
    ActionDelay preDelay;
    preDelay.initDelay(3);
    
    ActionRotateTo rotateToAction;
    rotateToAction.initRotateTo(0, 1);
    
    ActionRotateBy rotateByAction;
    rotateByAction.initRotateBy(90, 1);
    
    ActionMoveTo moveToOriginAction;
    moveToOriginAction.initMoveTo(glm::vec3(100, 0, 0), 1);
    
    ActionMoveBy moveByAction;
    moveByAction.initMoveBy(glm::vec3(100, 250, 0), 1);
    
    ActionFadeTo fadeTo;
    fadeTo.initFadeTo(255, 1);
    
    ActionFadeBy fadeBy;
    fadeBy.initFadeBy(-127, 1);
    
    ActionScaleTo scaleTo;
    scaleTo.initScaleTo(glm::vec3(1, 1, 1), 1);
    
    ActionScaleBy scaleBy;
    scaleBy.initScaleBy(glm::vec3(1, 1, 0), 1);
    
    creeper->addActions({new ActionDelay(preDelay), new ActionScaleBy(scaleBy), new ActionDelay(actionDelayBtw), new ActionRotateBy(rotateByAction), new ActionDelay(actionDelayBtw), new ActionMoveBy(moveByAction), new ActionDelay(actionDelayBtw), new ActionFadeBy(fadeBy), new ActionDelay(actionDelayBtw), new ActionScaleTo(scaleTo), new ActionDelay(actionDelayBtw), new ActionRotateTo(rotateToAction), new ActionDelay(actionDelayBtw), new ActionMoveTo(moveToOriginAction), new ActionDelay(actionDelayBtw), new ActionFadeTo(fadeTo)}, 10);
    
    FontManager::getInstance().addFont("UhBee Kang-Ja.ttf", 50);
//    FontManager::getInstance().addFont("Arial.ttf", 50);
    
    helloWorldText = new Text();
    helloWorldText->setColor(glm::vec3(255, 255, 255));
    helloWorldText->setTextAlign(Text::TextAlign::ALIGN_LEFT);
//    helloWorldText->initText("Hello world!\nNew line with left align!\nOpenGL with TTF font.\n`!@#$%^&*()-+_=", "Arial.ttf");
    helloWorldText->initText("Hello world!\nNew line with left align!\nOpenGL with TTF font.\n`!@#$%^&*()-+_=", "UhBee Kang-Ja.ttf");
    helloWorldText->setZDepth(10);
    this->addObject("hellowWorldText", helloWorldText);
    
    helloWorldText->addActions({new ActionDelay(preDelay), new ActionScaleBy(scaleBy), new ActionDelay(actionDelayBtw), new ActionRotateBy(rotateByAction), new ActionDelay(actionDelayBtw), new ActionMoveBy(moveByAction), new ActionDelay(actionDelayBtw), new ActionFadeBy(fadeBy), new ActionDelay(actionDelayBtw), new ActionScaleTo(scaleTo), new ActionDelay(actionDelayBtw), new ActionRotateTo(rotateToAction), new ActionDelay(actionDelayBtw), new ActionMoveTo(moveToOriginAction), new ActionDelay(actionDelayBtw), new ActionFadeTo(fadeTo)}, 10);
//    helloWorldText->setTextRange(1, 20);
    
    glfwSetCursorPos(window, size.w/2, size.h/2);
    cout << "init mouse pos with = (" << size.w/2 << ", " << size.h/2 << ")" << endl;
}

void TitleScene::update(){
    Scene::update();
//    creeper->addPosition(glm::vec3(0, 1, 0));
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
    if(canMoveCamera){
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
    }
    
    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS){
        canMoveCamera = true;
    }
    
    if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS){
        canMoveCamera = false;
    }
    
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        directorRef.getCameraPtr()->setPosition(glm::vec3(0, 0, -77.25));
    }
    
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        loadingBar->setPercentage(100);
    }
    else if(glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE){
        loadingBar->setPercentage(25);
    }
    
    if(!keyLockL && glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){
        cooldownIcon->addPercentage(1);
        cout << "cur % = " << cooldownIcon->getPercentage() << endl;
        keyLockL = true;
    }
    else if(keyLockL && glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE){
        keyLockL = false;
    }
}

void TitleScene::injectMouseMove(){
    if(canMoveCamera){
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        prevMousePos = curMousePos;
        curMousePos.x = x;
        curMousePos.y = y;
        
        glm::vec2 mouseDelta = curMousePos - prevMousePos;
        if(curMousePos.x >= 1280){
            curMousePos.x = 1280;
            glfwSetCursorPos(window, curMousePos.x, curMousePos.y);
        }
        //    float verticalAngle = 0.15f * mouseDelta.y;
        //    float horizontalAngle = 0.15f * mouseDelta.x;
        Director::getInstance().getCameraPtr()->changeAngle(0.15f * mouseDelta.y, 0.15f * mouseDelta.x);
        //billboard
        //    bg->rotateSprite(horizontalAngle * (-1), glm::vec3(0, 1, 0));
        
        //    cout << "curMousePos = (" << x << ", " << y << ")" << endl;
    }
}

void TitleScene::exit(){
    cout << "TitleScene::init" << endl;
}