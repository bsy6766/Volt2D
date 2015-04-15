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

//inherit. must need
#include "Scene.h"
//#include "Sprite.h"

class TitleScene : public Scene{
protected:
private:
//    Sprite* bg;
    virtual void exit();
public:
    TitleScene();
    ~TitleScene();
    
    //override pure
    virtual void init();
    virtual void keyPressed();
    virtual void keyReleased();
    virtual void update();
    virtual void render();
};

#endif /* defined(__OpenGL_2D_Framework__TitleScene__) */
