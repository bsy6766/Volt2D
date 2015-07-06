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
    bg->setZ_Depth(0);
    addSprite(bg);
    
    creeper = new Sprite();
    creeper->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/boss_creeper.png");
    creeper->setZ_Depth(2);
//    creeper->type = Sprite::BILLBOARD_TYPE;
    addSprite(creeper);
    
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
    moveToOriginAction.initMoveTo(glm::vec3(0, 0, 0), 1);
    
    ActionMoveBy moveByAction;
    moveByAction.initMoveBy(glm::vec3(0, 25, 0), 1);
    
    ActionFadeTo fadeTo;
    fadeTo.initFadeTo(255, 1);
    
    ActionFadeBy fadeBy;
    fadeBy.initFadeBy(-127, 1);
    
    ActionScaleTo scaleTo;
    scaleTo.initScaleTo(glm::vec3(1, 1, 1), 1);
    
    ActionScaleBy scaleBy;
    scaleBy.initScaleBy(glm::vec3(1, 1, 0), 1);
    
//    creeper->setOpacity(0);
//    creeper->setScale(glm::vec3(2, 2, 2));
//    creeper->addActions({new ActionDelay(preDelay), new ActionScaleBy(scaleBy)}, 0);
    creeper->addActions({new ActionDelay(preDelay), new ActionScaleBy(scaleBy), new ActionDelay(actionDelayBtw), new ActionRotateBy(rotateByAction), new ActionDelay(actionDelayBtw), new ActionMoveBy(moveByAction), new ActionDelay(actionDelayBtw), new ActionFadeBy(fadeBy), new ActionDelay(actionDelayBtw), new ActionScaleTo(scaleTo), new ActionDelay(actionDelayBtw), new ActionRotateTo(rotateToAction), new ActionDelay(actionDelayBtw), new ActionMoveTo(moveToOriginAction), new ActionDelay(actionDelayBtw), new ActionFadeTo(fadeTo)}, 10);
    
//    bg->addActions({delayAction4, fadeOutAction1, rotateAction1, delayAction5, fadeInAction1, rotateToAction1}, 1);
    
//    bg->addActions({delayAction4, moveToAction3, moveByAction1}, 2);
    
//    bg->setAngle(1);
//    bg->addActions({delayAction4, rotateToAction1}, 2);
//    bg->addActions({rotateAction1, rotateAction2}, 20);
    

//    ground = new Sprite();
//    ground->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/battle scene/battle_scene_bg.png");
//    ground->setZ_Depth(1);
//    ground->setPosition(glm::vec3(0, -50, 0));
//    ground->rotateBy(90, glm::vec3(-1, 0, 0));
//    addSprite(ground);
    
//    ActionDelay* delayAction = new ActionDelay();
//    delayAction->initDelay(3);
//    ActionDelay* delayAction1 = new ActionDelay();
//    delayAction1->initDelay(5);
//    ActionDelay* delayAction2 = new ActionDelay();
//    delayAction2->initDelay(6);
//    ActionDelay* delayAction3 = new ActionDelay();
//    delayAction3->initDelay(7);
//    ground->addAction(delayAction, 2);
//    ground->addActions({delayAction1, delayAction2, delayAction3}, 1);
    
//    ActionMoveTo* moveRightAction = new ActionMoveTo();
//    moveRightAction->initMoveTo(glm::vec2(0, 100), 3);
//    
//    ActionMoveTo* moveLeftAction = new ActionMoveTo();
//    moveLeftAction->initMoveTo(glm::vec2(0, -50), 3);
//    
//    ActionFadeTo* fadeOutDay = new ActionFadeTo();
//    fadeOutDay->initFadeTo(0, 2);
//
//    ActionDelay* delayBeforeFade = new ActionDelay();
//    delayBeforeFade->initDelay(2);
//
//    ActionFadeTo* fadeInDay = new ActionFadeTo();
//    fadeInDay->initFadeTo(255, 2);
//    
//    ActionRotateBy* rotateByAction = new ActionRotateBy();
//    rotateByAction->initRotateBy(180, 3);
//
//    ActionDelay* delayBtwFade = new ActionDelay();
//    delayBtwFade->initDelay(2);
//
//    SpriteActionSchedule* dayBGSchedule = new SpriteActionSchedule();
//
//    dayBGSchedule->createSchedule({moveRightAction, delayBeforeFade, fadeOutDay, delayBtwFade, fadeInDay, rotateByAction, moveLeftAction}, REPEAT_FOREVER);
//    ground->addActions(dayBGSchedule);
//    ground->runAction();
    
    FontManager::getInstance().addFont("UhBee Kang-Ja.ttf", 50);
//    FontManager::getInstance().addFont("Arial.ttf", 50);
    
    helloWorldText = new Text();
    helloWorldText->setColor(glm::vec3(255, 255, 255));
    helloWorldText->setTextAlign(Text::TextAlign::ALIGN_LEFT);
//    helloWorldText->initText("Hello world!\nNew line with left align!\nOpenGL with TTF font.\n`!@#$%^&*()-+_=", "Arial.ttf");
    helloWorldText->initText("Hello world!\nNew line with left align!\nOpenGL with TTF font.\n`!@#$%^&*()-+_=", "UhBee Kang-Ja.ttf");
    addText(helloWorldText);
//    delete helloWorldText;
    
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

void TitleScene::exit(){
    cout << "TitleScene::init" << endl;
}