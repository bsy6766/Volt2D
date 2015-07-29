//
//  MenuScene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/25/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__MenuScene__
#define __OpenGL_2D_Framework__MenuScene__

#include "Scene.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "ParticleSystem.h"
#include "Text.h"

class MenuScene : public Scene{
private:
    
    
public:
    MenuScene();
    ~MenuScene();
    
    void init() override;
    void exit() override;
};

#endif /* defined(__OpenGL_2D_Framework__MenuScene__) */
