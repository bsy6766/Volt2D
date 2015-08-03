//
//  BattleScene.h
//  Volt2D
//
//  Created by Seung Youp Baek on 4/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__BattleScene__
#define __Volt2D__BattleScene__

#include "Scene.h"
#include "Sprite.h"
#include "BattleHUDLayer.h"

class BattleScene : public Volt2D::Scene{
private:
    Volt2D::Sprite* bg;
    Volt2D::Sprite* playerFieldSlot;
    Volt2D::Sprite* enemyFieldSlot;
    BattleHUDLayer* HUD_Layer;
    
public:
    BattleScene();
    ~BattleScene();
    
    void init() override;
    void onEnter() override;
    void update(double dt) override;
//	virtual void keyPressed(int key, int mods);
//	virtual void keyReleased(int key, int mods);
//    virtual void mouseButton(double x, double y, int button, int action);
//    virtual void mouseMove(double x, double y);
    
    enum BattleState{
        PLAYER_TURN = 0,        //Player's turn
        ENEMY_TURN,             //Enemy's turn (AI)
        CHARACTER_SELECTING,    //Player selecting which character to take action
        SKILL_SELECTING,        //Player selecting which action/skill to use
        ENEMY_TARGETING,         //Player selecting which enemy to target with selected skill
        
    };
    
    virtual void exit();
};

#endif /* defined(__Volt2D__BattleScene__) */
