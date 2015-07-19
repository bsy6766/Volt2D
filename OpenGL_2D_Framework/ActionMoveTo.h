//
//  ActionMoveTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/5/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionMoveTo__
#define __OpenGL_2D_Framework__ActionMoveTo__

#include "SpriteObject.h"
#include "ActionObject.h"

/**
 *  @class ActionMoveTo
 *  @brief Move target object to position within duration
 */
class ActionMoveTo :  public ActionObject{
private:
    /**
     *  A destination to move
     */
    glm::vec3 destination;
    
    /**
     *  Target's starting position.
     */
    glm::vec3 originalPosition;
    
    /**
     *  Total moved distance from starting point
     */
    glm::vec3 movedPosition;
    
    /**
     *  Total distance this object needs to move
     */
    glm::vec3 totalDistance;
    
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
    
    //private constructor
    ActionMoveTo();

    /**
     *  Initialize ActionMoveBy
     *  @param destination A position to move
     *  @param duration A duration to move
     */
    void initMoveTo(glm::vec3 destination, double duration);
    
public:
    /**
     *  Create ActionMoveBy
     *  @param duration A duration to move
     *  @param destination A destination to move
     */
    static ActionMoveTo* createMoveTo(double duration, glm::vec3 destination);
    
    //destructor
    ~ActionMoveTo();
    
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

#endif /* defined(__OpenGL_2D_Framework__ActionMoveTo__) */
