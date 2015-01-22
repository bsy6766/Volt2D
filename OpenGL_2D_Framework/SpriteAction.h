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

/**
*	SpriteAction
*	This class is a base class to an Action classes.
*/

class SpriteAction{
private:
protected:
	//action's unique enum ID
    ActionID actionID;
    
	//item vars
    double duration;
    double totalElapsedTime;
    double unusedTime;
    double speed;
    
public:
    SpriteAction();
    virtual ~SpriteAction();
    
	/**
	* is currently running or not. 
	*/
    bool running;

	/**
	* is live or dead
	*/
    bool alive;

    double previousTime;
    
	/**
	* action won't get deleted if it is true. 
	* It becomes true when action repeats forever
	*/
    bool isProtected;
    
	//getters
	ActionID getActionID();
	glm::vec2 getDestination();
	glm::vec2 getMovedDistance();
    double getDuration();
	
	bool isRunning();
    bool isAlive();

	//time functions
    double getPreviousTime();
    double getTotalElapsedTime();
    double getElapsedTime();

    double setCurrentTime(double time);

	//setters
	void setSpeed(double speed);

    void startAction();
    void stopAction();
    
	/**
	* pure virtual function.
	* Derived class 
	*/
    virtual void update(double elapsedTime, double unusedTime) = 0;
    virtual void clone(SpriteAction *ptr);

	//kill and reset
    void kill();
    void revive();
};

#endif /* defined(__CS364FinalProject__SpriteAction__) */
