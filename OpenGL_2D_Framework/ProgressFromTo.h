//
//  ProgressFromTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressFromTo__
#define __OpenGL_2D_Framework__ProgressFromTo__

#include "ProgressObject.h"
#include "ActionObject.h"

/**
 *  @class ProgressFromTo
 *  @brief Move progress bar
 */
class ProgressFromTo : public ActionObject{
private:
    int from;
    int to;
    int totalPercentage;
    int changedPercentage;
    int previousPercentage;
    
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
    ProgressFromTo();
    
    /**
     *  Initialize ProgressFromTo
     *  @param from Starting percentage
     *  @param to Final percentage
     *  @param duration A duration to move progress bar
     */
    void initProgressFromTo(int from, int to, double duration);
public:
    /**
     *  Create ProgressFromTo
     *  @param duration A duration to fade to
     *  @param from A percentage to start
     *  @param to A percentage to end
     */
    static ProgressFromTo* createFromTo(double duration, int from, int to);
    //destructor
    ~ProgressFromTo();
    
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

#endif /* defined(__OpenGL_2D_Framework__ProgressFromTo__) */
