//
//  ActionScaleBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/19/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionScaleBy__
#define __OpenGL_2D_Framework__ActionScaleBy__

#include "Sprite.h"
#include "ActionObject.h"

namespace Volt2D{
/**
 *  @class ActionScaleBy
 *  @brief Scale target by specific scale
 */
class ActionScaleBy : public Volt2D::ActionObject{
private:
    /**
     *  Total amount to scale by
     */
    glm::vec3 totalScalingAmount;
    
    /**
     *  Previous scale
     */
    glm::vec3 prevScale;
    
    /**
     *  total scaled scale
     */
    glm::vec3 scaled;
    
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
    ActionScaleBy();
    
    /**
     *  Initialize ActionScaleBy
     *  @param scale An amount of scale to scale
     *  @param duration A duration to scale
     */
    void initScaleBy(glm::vec3 scale, double duration);
public:
    /**
     *  Create ActionScaleBy
     *  @param duration A duration to scale by
     *  @param opacity An scale to scale by
     */
    static ActionScaleBy* createScaleBy(double duration, glm::vec3 scale);
    
    //Destructor
    ~ActionScaleBy();
    
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

#endif /* defined(__OpenGL_2D_Framework__ActionScaleBy__) */
