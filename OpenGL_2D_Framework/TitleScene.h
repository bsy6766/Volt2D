//
//  TitleScene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__TitleScene__
#define __OpenGL_2D_Framework__TitleScene__

#include "Scene.h"
#include "Sprite.h"
#include "FontManager.h"
#include "BattleScene.h"
#include "SoundManager.h"
#include "ActionDelay.h"
#include "SpriteSheet.h"
#include "ActionRotateTo.h"
#include "ActionRotateBy.h"
#include "ActionCallFunc.h"
#include "ActionMoveTo.h"
#include "ActionMoveBy.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include "ParticleSystem.h"

#include "TitleButtonLayer.h"

class TitleScene : public Scene{
protected:
private:
    Sprite* bg;
    Sprite* title;
    Sprite* version;
    SpriteAnimation* character;
    ParticleSystem* magicalOrbits;
    ParticleSystem* flame;
    ParticleSystem* blueMeteor;
    ParticleSystem* muhanDojun;
    ParticleSystem* fireBall;
    
    TitleButtonLayer* titleButtonLayer;
    
    enum TitleSceneZ{
        z_bg = 0,
        z_button_layer,
        z_title
    };
    
    void initLayers();
    void printAngle();
    
public:
    TitleScene();
    ~TitleScene();
    
    //override pure
    virtual void init();
    virtual void exit();
	virtual void keyPressed(int key, int mode);
//    virtual void keyReleased(int key, int mode);
    virtual void mouseButton(double x, double y, int button, int action);
//    virtual void mouseMove(double x, double y);
    
    virtual void injectKey();
    virtual void injectMouseMove();
    virtual void update() override;
    
    void updateMouseInput();
};

#endif /* defined(__OpenGL_2D_Framework__TitleScene__) */
