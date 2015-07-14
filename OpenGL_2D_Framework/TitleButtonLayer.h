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
#include "ActionFadeTo.h"
#include "ActionScaleTo.h"
#include "ActionDelay.h"

class TitleButtonLayer : public Layer{
private:
    Sprite* mouseCursor;
    Sprite* newGameButton;
    Sprite* creditsButton;
    Sprite* optionsButton;
    Sprite* exitGameButton;
    Sprite* selectingArrowIcon;
    Sprite* creditScreen;
    
    Sprite* originPoint;
    Sprite* endPoint;
    
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
        NEW_GAME = 0,
        OPTIONS,
        CREDITS,
        EXIT_GAME
    };
    
    bool openingCredits;
    void openCredits();
    void closeCredits();
    
public:
    TitleButtonLayer();
    ~TitleButtonLayer();
    virtual void init();
    virtual void exit();
    
    virtual void update();
    
	virtual void keyPressed(int key, int mods);
    virtual void mouseButton(double x, double y, int button, int aciton);
    virtual void mouseMove(double x, double y);
};

#endif /* defined(__OpenGL_2D_Framework__TitleButtonLayer__) */
