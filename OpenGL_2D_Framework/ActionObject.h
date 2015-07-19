//
//  ActionObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionObject__
#define __OpenGL_2D_Framework__ActionObject__

#include "CommonInclude.h"
#include "Timer.h"
#include <glm/glm.hpp>

/**
 *  @name AcitonObject
 *  @brief A base class of action classes.
 */

class RenderableObject;

class ActionObject{
private:
protected:
    /**
     *  Action duration
     */
    double duration;
    
    /**
     *  Action's total elapsed time since it started
     */
    double totalElapsedTime;
    
    /**
     *  A target to update from this action
     */
    RenderableObject* target;
public:
    ActionObject();
    ActionObject(const ActionObject& other);
    virtual ~ActionObject();
    
    /**
     *  Only true if action starts running.
     *  False means it never started
     */
    bool running;
    
    /**
     *  Only true if action is valid.
     *  False means action is ended or dead
     */
    bool alive;
    
    /**
     * action won't get deleted if it is true.
     * It becomes true when action repeats forever
     */
    bool isProtected;
    
    /**
     *  Getter for action's duration
     *  @return duration of action object
     */
    double getDuration();
    
    /**
     *  Checks if action is running or not
     *  @return true if action is running. Else, false.
     */
    bool isRunning();
    
    /**
     *  Checks if action is alive or dead
     *  @return true if action is still valid. Else, false.
     */
    bool isAlive();
    
    /**
     *  Update time varaibles of this action object.
     *  @param elapsedTime An elapsed time for current iteration
     *  @return Remaining time that action didn't use if it ended. This will be stored and used on next action.
     */
    double setCurrentTime(double elapsedTime);
    
    /**
     *  Virtual function for starting action.
     *  Each action needs to update their own variables so it needs to be overriden
     */
    virtual void startAction();
    
    /**
     *  Update action. Pure virtual. 
     *  @param remainedTime An reference of remained time that stored in ActionSchedule.
     */
    virtual void updateAction(double& remainedTime) = 0;
    
    /**
     *  Kill and stop action. Action will be deleted if it doesn't have to repeat or protected
     */
    void kill();
    
    /**
     *  Revive this action.
     */
    virtual void revive();
    
    /**
     *  Get target of this object
     *  @return Object's target
     */
    RenderableObject* getTarget();
    
    /**
     *  Bind target to update
     *  @param target A RenderableObject pointer of target
     */
    void bindTarget(RenderableObject* target);
    
    /**
     *  Clone object
     */
    virtual ActionObject* clone() = 0;
};

#endif /* defined(__OpenGL_2D_Framework__ActionObject__) */
