//
//  TitleButtonLayer.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/10/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__TitleButtonLayer__
#define __OpenGL_2D_Framework__TitleButtonLayer__

#include "Director.h"
#include "Layer.h"
#include "Sprite.h"
//#include "ActionFadeTo.h"
//#include "ActionFadeBy.h"
//#include "ActionMoveTo.h"
//#include "ActionScaleTo.h"
//#include "ActionDelay.h"
//#include "ProgressBar.h"
//#include "ProgressFromTo.h"
//#include "ActionCallFunc.h"
#include "ParticleSystem.h"
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
    
    bool hasSavedData;
    
    std::unordered_map<unsigned int, bool> joystickMap;
    
    float selectingArrowIconX;
    int selectingButtonID;
    
    bool exitPressed;
    
    enum TitleLayerZ{
        z_buttons = 0,
        z_selecting_icon,
        z_credit_screen,
        z_mouse_cursor
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
    virtual void mouseButton(double x, double y, int button, int aciton);
    virtual void mouseMove(double x, double y);
};

#endif /* defined(__OpenGL_2D_Framework__TitleButtonLayer__) */
