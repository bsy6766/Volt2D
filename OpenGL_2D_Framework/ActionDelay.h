//
//  ActionDelay.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__ActionDelay__
#define __CS364FinalProject__ActionDelay__

#include "SpriteAction.h"

class ActionDelay : public SpriteAction{
private:
	//time
    double totalDelayed;
    double delayTick;
    
public:
    ActionDelay();
    ~ActionDelay();

    void initDelay(double duration);
    void update(double elapsedTime, double unusedtime);
    
    //getter
    double getDelayTick();

    //virtuals
    void clone(SpriteAction *);
    void revive();
};

#endif /* defined(__CS364FinalProject__ActionDelay__) */
