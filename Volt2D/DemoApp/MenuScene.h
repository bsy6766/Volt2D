//
//  MenuScene.h
//  Volt2D
//
//  Created by Seung Youp Baek on 7/25/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__MenuScene__
#define __Volt2D__MenuScene__

#include "Scene.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "ProgressBar.h"
#include "ProgressRadian.h"
#include "ParticleSystem.h"
#include "Text.h"
#include "Actions.h"

class MenuScene : public Volt2D::Scene{
private:
    Volt2D::Sprite* menuBg;
    Volt2D::Sprite* spriteBtn;
    Volt2D::Sprite* spriteAnimationBtn;
    Volt2D::Sprite* spriteSheetBtn;
    Volt2D::Sprite* progressBtn;
    Volt2D::Sprite* particleSysBtn;
    Volt2D::Sprite* textBtn;
    Volt2D::Sprite* sceneTransitionMoveBtn;
    Volt2D::Sprite* sceneTransitionFadeBtn;
    Volt2D::Sprite* sceneTransitionFlipBtn;
    
    Volt2D::Sprite* sampleSprite;
    Volt2D::SpriteAnimation* sampleAnimation;
    Volt2D::ProgressBar* sampleProgBar;
    Volt2D::Sprite* sampleProgBarBg;
    Volt2D::ProgressRadian* sampleProgRad;
    Volt2D::Sprite* sampleProgRadBg;
    
    Volt2D::Sprite* displayBorderline;
    
    Volt2D::Sprite* instructionBox;
    
    Volt2D::Sprite* exitMsgWindow;
    Volt2D::Sprite* exitConfirm;
    Volt2D::Sprite* exitCancel;
    
    Volt2D::Sprite* originPoint;
    Volt2D::Sprite* endPoint;
    
    bool waitingExit;
    bool mouseClicked;
    bool mouseDragged;
    bool ctrlPressed;
    bool displayBoxClicked;
    
    glm::vec2 prevMousePos;
    
    enum MenuScene_Z{
        z_bg = 0,
        z_btn,
        z_dispaly_frame,
        z_samples_bg,
        z_samples,
        z_exit,
        z_exit_btn
    };
    
    enum State{
        s_none = 0,
        s_sprite,
        s_sprite_animation,
        s_progress,
        s_particle_system,
        s_text,
        s_st_fade,
        s_st_move,
        s_st_flip
    };
    
    State curState;
    float defaultBtnOpacity;
    bool sampleActioning;
    void toggleActionFlag(){
        sampleActioning = false;
    };
    
    void resetPrevBtn();
    
public:
    MenuScene();
    ~MenuScene();
    
    void init() override;
    void onEnter() override;
    void update(double dt) override;
    void keyPressed(int key, int mods) override;
    void keyReleased(int key, int mods) override;
    void mouseButton(double x, double y, int button, int action, int mods) override;
    void mouseMove(double x, double y) override;
    void exit() override;
};

#endif /* defined(__Volt2D__MenuScene__) */
