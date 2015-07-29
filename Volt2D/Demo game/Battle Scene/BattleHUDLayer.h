//
//  BattleHUDLayer.h
//  Volt2D
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__BattleHUDLayer__
#define __Volt2D__BattleHUDLayer__

#include "Sprite.h"
#include "Layer.h"
#include "StatusBar.h"
#include <vector>

class BattleHUDLayer : public Volt2D::Layer{
private:
    std::vector<StatusBar*> statusBars;
    
public:
    BattleHUDLayer();
    ~BattleHUDLayer();
    
    virtual void init();
    virtual void exit();
};

#endif /* defined(__Volt2D__BattleHUDLayer__) */
