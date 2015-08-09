//
//  ActionCallFunc.h
//  Volt2D
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ActionCallFunc__
#define __Volt2D__ActionCallFunc__

#if _WIN32
#include <functional>
#endif
#include "ActionObject.h"

namespace Volt2D{
/**
 *  @class ActionCallFunc
 *  @brief bind callback function
 */
class ActionCallFunc : public ActionObject{
private:
    /**
     *  Function pointer.
     */
    std::function<void()> function;
    
    //private constructor
    ActionCallFunc();
    
    /**
     *  Initialize ActionCallFunc
     *  @param func A std::function of function
     */
    void initActionCallFunc(const std::function<void()>& func);
public:
    /**
     *  Create ActionCallFunc
     *  @param func A std::function of function
     */
    static ActionCallFunc* createCallFunc(const std::function<void()>& func);
    
    //Destructor
    ~ActionCallFunc();
    
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

#endif /* defined(__Volt2D__ActionCallFunc__) */
