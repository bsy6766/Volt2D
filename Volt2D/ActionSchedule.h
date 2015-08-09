//
//  ActionSchedule.h
//  Volt2D
//
//  Created by Seung Youp Baek on 5/17/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ActionSchedule__
#define __Volt2D__ActionSchedule__

#include "ActionObject.h"
#include <list>

namespace Volt2D{
/**
 *  @class ActionSchedule
 *  @brief pack of ActionObject(s).
 *  \todo Comment and document this class
 */
class ActionSchedule{
protected:
private:    
    int repeat;
    int repeatCounter;
    bool instantSchedule;
    bool finished;
    
    double remainedTime;
    
    std::list<Volt2D::ActionObject*> actionList;
    void clearList();    
    
public:
    ActionSchedule();
    ~ActionSchedule();
    void createSchedule(Volt2D::ActionObject* action, int repeat);
    void createSchedule(Volt2D::ActionObject** actions, int size, int repeat);
    void createSchedule(std::initializer_list<Volt2D::ActionObject*>& actions, int repeat);
    void terminateAllAction();
    void updateSchedule();
    bool isEmpty();
    bool isFinished();
    bool needRepeat();
    void reviveSchedule();
    std::list<Volt2D::ActionObject*>& getList();
    bool isInstant();
};
}

#endif /* defined(__Volt2D__ActionSchedule__) */
