//
//  TitleScene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__TitleScene__
#define __OpenGL_2D_Framework__TitleScene__

#include <stdio.h>
#include <iostream>

#include "Scene.h"
#include "Sprite.h"
#include "ProgressBar.h"
#include "progressRadian.h"
#include "FontManager.h"
#include "Text.h"
#include "BattleScene.h"
#include "ActionDelay.h"
#include "ActionMoveBy.h"
#include "ActionMoveTo.h"
#include "ActionRotateBy.h"
#include "ActionRotateTo.h"
#include "ActionFadeBy.h"
#include "ActionFadeTo.h"
#include "ActionScaleBy.h"
#include "ActionScaleTo.h"

class TitleScene : public Scene{
protected:
private:
    Sprite* bg;
    Sprite* creeper;
    Sprite* ground;
    Sprite* mouseCursor;
    ProgressBar* loadingBar;
    ProgressRadian* cooldownIcon;
    Sprite* loadingBarBg;
    Text* helloWorldText;
    Sprite* originPoint, *endPoint;
    
    bool keyLockL = false;
    
    virtual void exit();
    
public:
    TitleScene();
    ~TitleScene();
    
    //override pure
    virtual void init();
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void mouseButton(double x, double y, int button, int action);
    virtual void mouseMove(double x, double y);
//    virtual void update();
//    virtual void render();
    virtual void injectKey();
    virtual void injectMouseMove();
    virtual void update() override;
    
    void updateMouseInput();
};

#endif /* defined(__OpenGL_2D_Framework__TitleScene__) */