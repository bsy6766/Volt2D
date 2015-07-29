//
//  ActionFadeBy.h
//  Volt2D
//
//  Created by Seung Youp Baek on 6/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ActionFadeBy__
#define __Volt2D__ActionFadeBy__

#include "ActionObject.h"
#include "Sprite.h"

namespace Volt2D{
/**
 *  @class ActionFadeBy
 *  @brief Fade target by specific opacity
 *  @note Max opacity: 255.0, Min opacity: 0
 */
class ActionFadeBy : public Volt2D::ActionObject{
private:
    /**
     *  Total opacity to fade by
     */
    float opacityToFade;
    
    /**
     *  Total opacity faded
     */
    float fadedOpacity;
    
    /**
     *  Previous opacity this object faded
     */
    float previousOpacity;
    
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
    ActionFadeBy();
    
    /**
     *  Initialize ActionFadeBy
     *  @param opacity An opacity to fade
     *  @param duration A duration to fade
     */
    void initFadeBy(float opacity, double duration);
    
public:
    /**
     *  Create ActionFadeBy
     *  @param duration A duration to fade by
     *  @param opacity An opacity to fade by
     */
    static ActionFadeBy* createFadeBy(double duration, float opacity);
    
    //Destructor
    ~ActionFadeBy();
    
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

#endif /* defined(__Volt2D__ActionFadeBy__) */
