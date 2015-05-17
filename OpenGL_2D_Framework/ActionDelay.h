//
//  ActionDelay.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionDelay__
#define __OpenGL_2D_Framework__ActionDelay__

#include "ActionObject.h"

class ActionDelay : public ActionObject{
private:
	//time
    double totalDelayed;
    double delayTick;
    
public:
    ActionDelay();
    ~ActionDelay();

    void initDelay(double duration);
    
    void updateAction();
//    void instantUpdate();
//    void intervalUpdate();
    
    //getter
    double getDelayTick();

    //virtuals
    virtual void instantUpdate();
    virtual void intervalUpdate();
    virtual void update(double elapsedTime, double unusedtime);
    
    //override
    void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionDelay__) */
