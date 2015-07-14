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
    //delay has nothing...just consuming time. yolo
    void instantUpdate();
    void intervalUpdate(double& remainedTime);
    
public:
    ActionDelay();
    ActionDelay(const ActionDelay& other);
    ~ActionDelay();

    void initDelay(double duration);

    //override
    virtual void updateAction(double& remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionDelay__) */
