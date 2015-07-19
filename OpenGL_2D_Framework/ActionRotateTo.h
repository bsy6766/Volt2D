//
//  ActionRotateTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionRotateTo__
#define __OpenGL_2D_Framework__ActionRotateTo__

#include "SpriteObject.h"
#include "ActionObject.h"

/**
 *  @name ActionRotateTo
 *  @brief Rotate target to specific angle in degree within duration
 *  @note Angle is degree.
 */
class ActionRotateTo :  public ActionObject{
private:
    /**
     *  Target's angle
     */
    float startAngle;
    
    /**
     *  Final angle to rotate
     */
    float destinationAngle;
    
    /**
     *  Total rotated angle
     */
    float movedAngle;
    
    /**
     *  Total angle to rotate from object's angle
     */
    float totalAngleToRotate;
    
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
    ActionRotateTo();
    
    /**
     *  Initialize ActionRotateTo
     *  @param angle An angle to rotate
     *  @param duration An duration to rotate
     */
    void initRotateTo(float angle, double duration);
public:
    /**
     *  Create ActionRotateTo
     *  @param duration A duration to rotate
     *  @param angle An angle to rotate to
     */
    static ActionRotateTo* createRotateTo(double duration, float angle);
    
    //Destructor
    ~ActionRotateTo();
    
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

#endif /* defined(__OpenGL_2D_Framework__ActionRotateTo__) */
