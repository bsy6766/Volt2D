//
//  SpriteAction.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/11/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__SpriteAction__
#define __CS364FinalProject__SpriteAction__

#include <glm/glm.hpp>

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

class SpriteAction{
private:
protected:
    
    ActionID actionID;
    
    double duration;
    double totalElapsedTime;
    double unusedTime;
    double speed;
    
public:
    SpriteAction();
    virtual ~SpriteAction();
    
    bool running;
    bool alive;

    double previousTime;
    
    bool isProtected;
    
    ActionID getActionID();
    void startAction();
    void stopAction();
    glm::vec2 getDestination();
    double getDuration();
    glm::vec2 getMovedDistance();
    void setSpeed(double speed);
    
    virtual void update(double elapsedTime, double unusedTime) = 0;
    virtual void clone(SpriteAction *ptr);
    
    double getPreviousTime();
    double getCurrentTime();
    double setCurrentTime(double time);
    double getElapsedTime();
    
    bool isRunning();
    bool isAlive();
    
    void kill();
    void revive();
};

#endif /* defined(__CS364FinalProject__SpriteAction__) */
