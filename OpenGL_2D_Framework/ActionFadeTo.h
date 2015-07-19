//
//  ActionFadeTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionFadeTo__
#define __OpenGL_2D_Framework__ActionFadeTo__

#include "SpriteObject.h"
#include "ActionObject.h"

/**
 *  @name ActionFadeTo
 *  @brief Fade target to specific opacity
 *  @note Max opacity: 255.0, Min opacity: 0
 */
class ActionFadeTo : public ActionObject{
private:
    /**
     *  Final opacity to fade
     */
    float finalOpacity;
    
    /**
     *  Target's opacity
     */
    float originalOpacity;
    
    /**
     *  Total faded opacity
     */
    float fadedOpacity;
    
    /**
     *  Total opacity to fade
     */
    float totalOpacityToFade;
    
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
    ActionFadeTo();
    
    /**
     *  Initialize ActionFadeTo
     *  @param opacity An opacity to fade
     *  @param duration A duration to fade
     */
    void initFadeTo(float opacity, double duration);
public:
    /**
     *  Create ActionFadeTo
     *  @param duration A duration to fade to
     *  @param opacity An opacity to fade to
     */
    static ActionFadeTo* createFadeTo(double duration, float opacity);
    
    //destructor
    ~ActionFadeTo();
    
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

#endif /* defined(__OpenGL_2D_Framework__ActionFadeTo__) */
