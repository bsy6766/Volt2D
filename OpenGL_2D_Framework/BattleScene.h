//
//  BattleScene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__BattleScene__
#define __OpenGL_2D_Framework__BattleScene__

#include <stdio.h>

#include "Scene.h"
#include "Sprite.h"
#include "CommonInclude.h"

class BattleScene : public Scene{
private:
    Sprite* bg;
    bool mouseClicked = false;
    glm::vec2 prevMousePos;
    glm::vec2 curMousePos;
    
public:
    BattleScene();
    ~BattleScene();
    
    virtual void init();
//    virtual void update();
//    virtual void render();
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void mouseButton(int button, int action);
    virtual void mouseMove(double x, double y);
    
    virtual void exit();
};

#endif /* defined(__OpenGL_2D_Framework__BattleScene__) */
