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
//#include "ActionType.h"

//Action IDs
enum ActionID{
    //delay
    ACTION_DELAY = 0,
    //move
    ACTION_MOVE_TO,
    ACTION_MOVE_BY,
    //rotate
    ACTION_ROTATE_TO,
    ACTION_ROTATE_BY,
    //scale
    ACTION_SCALE_TO,
    ACTION_SCALE_BY,
    //jump
    ACTION_JUMP_TO,
    ACTION_JUMP_BY,
    //fade
    ACTION_FADE_TO,
    ACTION_FADE_BY,
    //blink
    ACTION_BLINK
};

class SpriteObject;

class ActionObject{
private:
protected:
    //action's unique enum ID
    ActionID actionID;
//    ActionType type;
    
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
    
    virtual void updateAction(double& remainedTime) = 0;
    virtual void instantUpdate() = 0;
    virtual void intervalUpdate(double& remainedTime) = 0;
    
    //kill and reset
    void kill();
    virtual void revive();
    
    SpriteObject* getOwner();
    void bindOwnerPtr(SpriteObject* ownerPtr);
};

#endif /* defined(__OpenGL_2D_Framework__ActionObject__) */
