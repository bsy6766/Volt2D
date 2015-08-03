//
//  ActionRotateBy.h
//  Volt2D
//
//  Created by Seung Youp Baek on 12/8/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ActionRotateBy__
#define __Volt2D__ActionRotateBy__

#include "Sprite.h"
#include "ActionObject.h"

namespace Volt2D{
/**
 *  @class ActionRotateBy
 *  @brief Rotate target by specific angle in degree within duration
 *  @note Angle is degree.
 */
class ActionRotateBy :  public Volt2D::ActionObject{
private:
    /**
     *  An angle to rotate
     */
    float rotatingAngle;
    
    /**
     *  A previous angle this object rotated
     */
    float previousAngle;
    
    /**
     *  Total rotated angle
     */
    float movedAngle;
    
    /** Rotation axis */
    glm::vec3 axis;
    
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
    ActionRotateBy();
    
    /**
     *  Initialize ActionRotateBy
     *  @param angle An angle to rotate
     *  @param duration An duration to rotate
     *  @param axis Rotation axis
     */
    void initRotateBy(float angle, double duration, glm::vec3 axis = Z_AXIS);
    
public:
    /**
     *  Create ActionRotateTo
     *  @param duration A duration to rotate
     *  @param angle An angle to rotate by
     *  @param axis A rotation axis. Z axis by default
     */
    static ActionRotateBy* createRotateBy(double duration, float angle, glm::vec3 axis = Z_AXIS);
    
    //Destructor
    ~ActionRotateBy();
    
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
}

#endif /* defined(__Volt2D__ActionRotateBy__) */
