//
//  ActionDelay.h
//  Volt2D
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ActionDelay__
#define __Volt2D__ActionDelay__

#include "ActionObject.h"

namespace Volt2D{
/**
 *  @class ActionDelay
 *  @brief Delay action for specific duration
 */
class ActionDelay : public ActionObject{
private:
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
    ActionDelay();
    
    /**
     *  Initialize delay action
     *  @param duration Time to delay.
     */
    void initDelay(double duration);
public:
    /**
     *  Create ActionDelay
     *  @duration A duration to delay
     */
    static ActionDelay* createDelay(double duration);
    
    //Destructor
    ~ActionDelay();

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

#endif /* defined(__Volt2D__ActionDelay__) */
