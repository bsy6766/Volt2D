//
//  BattleScene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__BattleScene__
#define __OpenGL_2D_Framework__BattleScene__

#include "Scene.h"
#include "Sprite.h"
#include "CommonInclude.h"
#include "BattleHUDLayer.h"

class BattleScene : public Scene{
private:
    Sprite* bg;
    Sprite* playerFieldSlot;
    Sprite* enemyFieldSlot;
    BattleHUDLayer* HUD_Layer;
    
public:
    BattleScene();
    ~BattleScene();
    
    virtual void init();
    virtual void update();
//	virtual void keyPressed(int key, int mods);
//	virtual void keyReleased(int key, int mods);
//    virtual void mouseButton(double x, double y, int button, int action);
//    virtual void mouseMove(double x, double y);
    virtual void injectKey();
    virtual void injectMouseMove();
    
    enum BattleState{
        PLAYER_TURN = 0,        //Player's turn
        ENEMY_TURN,             //Enemy's turn (AI)
        CHARACTER_SELECTING,    //Player selecting which character to take action
        SKILL_SELECTING,        //Player selecting which action/skill to use
        ENEMY_TARGETING,         //Player selecting which enemy to target with selected skill
        
    };
    
    virtual void exit();
};

#endif /* defined(__OpenGL_2D_Framework__BattleScene__) */
