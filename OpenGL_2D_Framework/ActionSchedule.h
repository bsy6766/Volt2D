//
//  ActionSchedule.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/17/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionSchedule__
#define __OpenGL_2D_Framework__ActionSchedule__

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

#endif /* defined(__OpenGL_2D_Framework__ActionSchedule__) */
