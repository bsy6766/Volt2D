//
//  ActionObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionObject__
#define __OpenGL_2D_Framework__ActionObject__

//#define GLM_FORCE_RADIANS

#include "CommonInclude.h"
#include "Timer.h"
#include <glm/glm.hpp>

//class SpriteObject;
class RenderableObject;

class ActionObject{
private:
protected:
    //item vars
    double duration;
    double totalElapsedTime;
    double previousTime;
    double speed;
    
    RenderableObject* target;
    
public:
    unsigned int objID;
    
    ActionObject();
    ActionObject(const ActionObject& other);
    virtual ~ActionObject();
    
    bool running;
    bool alive;
    
    /**
     * action won't get deleted if it is true.
     * It becomes true when action repeats forever
     */
    bool isProtected;
    
    //getters
    double getDuration();
    
    bool isRunning();   //check if action object is running or not. 
    bool isAlive();
    
    //time functions
    double setCurrentTime(double elapsedTime);
    
    //setters
    void setSpeed(double speed);
    
    virtual void startAction();
    void stopAction();
    
    virtual void updateAction(double& remainedTime) = 0;
    virtual void instantUpdate() = 0;
    virtual void intervalUpdate(double& remainedTime) = 0;
    
    //kill and reset
    void kill();
    virtual void revive();
    
    RenderableObject* getTarget();
    void bindTarget(RenderableObject* target);
};

#endif /* defined(__OpenGL_2D_Framework__ActionObject__) */
