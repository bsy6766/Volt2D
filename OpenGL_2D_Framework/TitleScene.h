//
//  TitleScene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__TitleScene__
#define __OpenGL_2D_Framework__TitleScene__

#include <stdio.h>
#include <iostream>

#include "Scene.h"
#include "Sprite.h"
#include "FontManager.h"
#include "Text.h"
#include "BattleScene.h"
#include "SoundManager.h"

#include "TitleButtonLayer.h"

class TitleScene : public Scene{
protected:
private:
    Sprite* bg;
    Text* title;
    
    TitleButtonLayer* titleButtonLayer;
    
    virtual void exit();
    
    enum TitleSceneZ{
        z_bg = 0,
        z_button_layer
    };
    
    void initLayers();
    
public:
    TitleScene();
    ~TitleScene();
    
    //override pure
    virtual void init();
	virtual void keyPressed(int key, int mode);
//    virtual void keyReleased(int key, int mode);
//    virtual void mouseButton(double x, double y, int button, int action);
//    virtual void mouseMove(double x, double y);
    
    virtual void injectKey();
    virtual void injectMouseMove();
    virtual void update() override;
    
    void updateMouseInput();
};

#endif /* defined(__OpenGL_2D_Framework__TitleScene__) */
