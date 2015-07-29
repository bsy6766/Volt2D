//
//  ActionJumpTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionJumpTo__
#define __OpenGL_2D_Framework__ActionJumpTo__

#include "SpriteObject.h"
#include "ActionObject.h"

/**
 *  @class ActionJumpTo
 *  @brief Jump object to position
 */
class ActionJumpTo : public ActionObject{
private:
    float height;
    glm::vec3 srcPos;
    glm::vec3 destPos;
    bool yPhaseChanged;
    
    //private constructor
    ActionJumpTo();
    
    /**
     *  Instant update.
     *  This is called when duration is 0
     */
    void instantUpdate();
    
    /**
     *  Interval update.
     *  This is called when duration is not 0
     *  @param remainedTime A remainedTime the schedule list has.
     */
    void intervalUpdate(double& remainedTime);
    
    /**
     *  Initialize ActionJumpTo
     */
    void initActionJumpTo(double duration, glm::vec3 dest, float h);
public:
    /**
     *  Create ActionJumpTo
     */
    static ActionJumpTo* createJumpTo(double duration, glm::vec3 destination, float height);
    
    //Destructor
    ~ActionJumpTo();
    
    /**
     *  Start the action.
     */
    virtual void startAction();
    
    /**
     *  Update this action
     *  @param remainedTime A remained time the ActionSchedule has.
     */
    virtual void updateAction(double& remainedTime);
    
    /**
     *  Revive the action.
     */
    virtual void revive();
    
    /**
     *  Clone the action object.
     */
    virtual ActionObject* clone();
};


#endif /* defined(__OpenGL_2D_Framework__ActionJumpTo__) */
