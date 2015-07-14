//
//  ActionCallFunc.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionCallFunc__
#define __OpenGL_2D_Framework__ActionCallFunc__

#include "ActionObject.h"

class ActionCallFunc : public ActionObject{
private:
    std::function<void()> func;
    
public:
    ActionCallFunc();
    ActionCallFunc(const ActionCallFunc& other);
    ~ActionCallFunc();
    
    //by default this func
    void initActionCallFunc(const std::function<void()> func);
    
    //override
    virtual void startAction();
    virtual void updateAction(double& remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionCallFunc__) */
