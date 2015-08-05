//
//  TitleButtonLayer.h
//  Volt2D
//
//  Created by Seung Youp Baek on 7/10/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__TitleButtonLayer__
#define __Volt2D__TitleButtonLayer__

#include "Director.h"
#include "Layer.h"
#include "Sprite.h"
#include "ParticleSystem.h"
#include "Actions.h"
#include <map>
#include "BattleScene.h"

class TitleButtonLayer : public Volt2D::Layer{
private:
//    Sprite* mouseCursor;
    Volt2D::Sprite* newGameButton;
    Volt2D::Sprite* creditsButton;
    Volt2D::Sprite* optionsButton;
    Volt2D::Sprite* exitGameButton;
    Volt2D::Sprite* selectingArrowIcon;
    Volt2D::Sprite* creditScreen;
    Volt2D::Sprite* continueButton;
    
    Volt2D::ParticleSystem* magicalOrbits;
    Volt2D::ParticleSystem* flame;
    Volt2D::ParticleSystem* blueMeteor;
    Volt2D::ParticleSystem* muhanDojun;
    Volt2D::ParticleSystem* fireBall;
    
    Volt2D::Sprite* tentacle;
    Volt2D::Sprite* arm1;
    Volt2D::Sprite* arm2;
    Volt2D::Sprite* arm3;
    
    bool hasSavedData;
    
    std::unordered_map<unsigned int, bool> joystickMap;
    
    float selectingArrowIconX;
    int selectingButtonID;
    
    bool exitPressed;
    
    enum TitleLayerZ{
        z_buttons = 0,
        z_selecting_icon,
        z_credit_screen,
        z_mouse_cursor,
        z_top
    };
    
    enum ButtonID{
        CONTINUE = 0,
        NEW_GAME,
        OPTIONS,
        CREDITS,
        EXIT_GAME
    };
    
    bool openingCredits;
    void openCredits();
    void closeCredits();
    
    void testFunc();
    void testFunc2(int num);
    
public:
    TitleButtonLayer();
    ~TitleButtonLayer();
    virtual void init();
    virtual void exit();
    
    virtual void update(double dt);
    
	virtual void keyPressed(int key, int mods);
    virtual void mouseButton(double x, double y, int button, int aciton, int mods);
    virtual void mouseMove(double x, double y);
};

#endif /* defined(__Volt2D__TitleButtonLayer__) */
