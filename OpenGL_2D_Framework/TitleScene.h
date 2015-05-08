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

//inherit. must need
#include "Scene.h"
#include "Sprite.h"

#include "BattleScene.h"

class TitleScene : public Scene{
protected:
private:
    Sprite* bg;
    Sprite* ground;
    
    virtual void exit();
    
public:
    TitleScene();
    ~TitleScene();
    
    //override pure
    virtual void init();
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void mouseButton(int button, int action);
    virtual void mouseMove(double x, double y);
//    virtual void update();
//    virtual void render();
    virtual void injectKey();
    virtual void injectMouseMove();
    
    void updateMouseInput();
};

#endif /* defined(__OpenGL_2D_Framework__TitleScene__) */
