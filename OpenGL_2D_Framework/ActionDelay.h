//
//  ActionDelay.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionDelay__
#define __OpenGL_2D_Framework__ActionDelay__

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
    
    //getter
    double getDelayTick();

    //virtuals
    void clone(SpriteAction *);
    void update(double elapsedTime, double unusedtime);

    //override
    void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionDelay__) */
