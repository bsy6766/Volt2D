//
//  ActionScaleTo.h
//  Volt2D
//
//  Created by Seung Youp Baek on 6/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ActionScaleTo__
#define __Volt2D__ActionScaleTo__

#include "Sprite.h"
#include "ActionObject.h"

namespace Volt2D{
/**
 *  @class ActionScaleBy
 *  @brief Scale target by specific scale
 */
class ActionScaleTo : public Volt2D::ActionObject{
private:
    /**
     *  Final scale value to scale
     */
    glm::vec3 destScale;
    
    /**
     *  Target's scale
     */
    glm::vec3 srcScale;
    
    /**
     *  Total scaled
     */
    glm::vec3 scaled;
    
    /**
     *  Total amount of scale
     */
    glm::vec3 totalScalingAmount;
    
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
    ActionScaleTo();
    
    /**
     *  Initialize ActionScaleTo
     *  @param scale An amount of scale to scale
     *  @param duration A duration to scale
     */
    void initScaleTo(glm::vec3 scale, double duration);
public:
    /**
     *  Create ActionScaleBy
     *  @param duration A duration to scale by
     *  @param opacity An scale to scale by
     */
    static ActionScaleTo* createScaleTo(double duration, glm::vec3 scale);
    
    //Detructor
    ~ActionScaleTo();
    
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
}

#endif /* defined(__Volt2D__ActionScaleTo__) */
