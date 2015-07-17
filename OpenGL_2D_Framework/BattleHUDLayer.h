//
//  BattleHUDLayer.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__BattleHUDLayer__
#define __OpenGL_2D_Framework__BattleHUDLayer__

#include "Sprite.h"
#include "Layer.h"
#include "StatusBar.h"
#include <vector>

class BattleHUDLayer : public Layer{
private:
    std::vector<StatusBar*> statusBars;
    
public:
    BattleHUDLayer();
    ~BattleHUDLayer();
    
    virtual void init();
    virtual void exit();
};

#endif /* defined(__OpenGL_2D_Framework__BattleHUDLayer__) */
