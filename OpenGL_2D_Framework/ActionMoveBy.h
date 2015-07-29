//
//  ActionMoveBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionMoveBy__
#define __OpenGL_2D_Framework__ActionMoveBy__

#include "ActionObject.h"
#include "Sprite.h"

namespace Volt2D{
/**
 *  @class ActionMoveBy
 *  @brief Move target object by distance with in duration
 */
class ActionMoveBy : public Volt2D::ActionObject{
private:
    /**
     *  A distance to move
     */
    glm::vec3 distance;
    
    /**
     *  Total moved distance
     */
    glm::vec3 movedDistance;
    
    /**
     *  Previous distance the action moved
     */
    glm::vec3 previousDistance;
    
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
    
    //Private constructor
    ActionMoveBy();
    
    /**
     *  Initialize MoveBy action
     *  @param distance A distance to move
     *  @param duration A duration to move
     */
    void initMoveBy(glm::vec3 distance, double duration);
public:
    /**
     *  Create ActionMoveBy
     *  @param duration A duration to move by
     *  @param distance A distance to move by
     */
    static ActionMoveBy* createMoveBy(double duration, glm::vec3 distance);
    
    //Destructor
    ~ActionMoveBy();
    
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

#endif /* defined(__OpenGL_2D_Framework__ActionMoveBy__) */
