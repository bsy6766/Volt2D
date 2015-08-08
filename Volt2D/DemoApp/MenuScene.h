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
    Volt2D::Sprite* soundBtn;
    float bgmVol, sfxVol;
    Volt2D::Sprite* volumeLabel;
    Volt2D::ProgressBar* bgmVolBar;
    Volt2D::ProgressBar* sfxVolBar;
    
    Volt2D::Sprite* sampleSprite;
    Volt2D::SpriteAnimation* sampleAnimation;
    Volt2D::ProgressBar* sampleProgBar;
    Volt2D::Sprite* sampleProgBarBg;
    Volt2D::ProgressRadian* sampleProgRad;
    Volt2D::Sprite* sampleProgRadBg;
    Volt2D::ParticleSystem* sampleParticleSystem;
    Volt2D::Text* sampleText;
    
    Volt2D::Sprite* waitingTransitionMsg;
    
    Volt2D::Sprite* displayBorderline;
    
    Volt2D::Sprite* instructionBox;
    Volt2D::Sprite* instructionMsg;
    
    Volt2D::Sprite* exitMsgWindow;
    
    bool waitingExit;
    bool waitingTransition;
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
        z_exit
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
        s_st_flip,
        s_sound
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
