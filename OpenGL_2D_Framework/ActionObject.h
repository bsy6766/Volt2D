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

//Action IDs
enum ActionID{
    ACTION_DELAY = 0,
    ACTION_MOVE_TO,
    ACTION_MOVE_BY,
    ACTION_ROTATE_TO,
    ACTION_ROTATE_BY,
    ACTION_SCALE_TO,
    ACTION_SCALE_BY,
    ACTION_JUMP_TO,
    ACTION_JUMP_BY,
    ACTION_FADE_TO
};

class SpriteObject;

class ActionObject{
private:
protected:
    //action's unique enum ID
    ActionID actionID;
    
    static unsigned int ACTION_ID;
    
    //item vars
    double duration;
    double totalElapsedTime;
    double previousTime;
    double elapsedTime;
    double unusedTime;
    double remainedTimeByDeath;
    double speed;
    
    SpriteObject* owner;
    
public:
    unsigned int objID;
    
    ActionObject();
    virtual ~ActionObject();
    
    bool running;
    bool alive;
    
    /**
     * action won't get deleted if it is true.
     * It becomes true when action repeats forever
     */
    bool isProtected;
    
    //getters
    ActionID getActionID();
    double getDuration();
    
    bool isRunning();   //check if action object is running or not. 
    bool isAlive();
    
    //time functions
    double getPreviousTime();
    double getTotalElapsedTime();
    double getElapsedTime();
    double setCurrentTime(double elapsedTime);
    double getRemainedTime();
    
    //setters
    void setSpeed(double speed);
    
    void startAction();
    void stopAction();
    
    virtual void updateAction(double remainedTime) = 0;
    virtual void instantUpdate() = 0;
    virtual void intervalUpdate(double remainedTime) = 0;
    
    //kill and reset
    void kill();
    virtual void revive();
    
    SpriteObject* getOwner();
    void bindOwnerPtr(SpriteObject* ownerPtr);
};

#endif /* defined(__OpenGL_2D_Framework__ActionObject__) */
