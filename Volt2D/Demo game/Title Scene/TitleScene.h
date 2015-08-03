//
//  TitleScene.h
//  Volt2D
//
//  Created by Seung Youp Baek on 4/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__TitleScene__
#define __Volt2D__TitleScene__

#include "Scene.h"
#include "Sprite.h"
#include "FontManager.h"
#include "BattleScene.h"
#include "SoundManager.h"
#include "SpriteSheet.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include "ParticleSystem.h"

#include "Actions.h"

#include "TitleButtonLayer.h"

class TitleScene : public Volt2D::Scene{
protected:
private:
    Volt2D::Sprite* bg;
    Volt2D::Sprite* title;
    Volt2D::Sprite* version;
    Volt2D::SpriteAnimation* character;
    Volt2D::ParticleSystem* magicalOrbits;
    Volt2D::ParticleSystem* flame;
    Volt2D::ParticleSystem* blueMeteor;
    Volt2D::ParticleSystem* muhanDojun;
    Volt2D::ParticleSystem* fireBall;
    
    TitleButtonLayer* titleButtonLayer;
    
    enum TitleSceneZ{
        z_bg = 0,
        z_button_layer,
        z_title,
		z_text,
		z_animation,
		z_particles,
		z_fireball
    };
    
    void initLayers();
    void printAngle();
    
public:
    TitleScene();
    ~TitleScene();
    
    //override pure
    void init() override;
    void onEnter() override;
    void exit() override;
    void keyPressed(int key, int mode) override;
//    virtual void keyReleased(int key, int mode);
    void mouseButton(double x, double y, int button, int action) override;
//    virtual void mouseMove(double x, double y);

    void update(double dt) override;
    
    void updateMouseInput();
};

#endif /* defined(__Volt2D__TitleScene__) */
