//
//  SpriteActionSchedule.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteActionSchedule__
#define __OpenGL_2D_Framework__SpriteActionSchedule__

#include <list>
#include <vector>
#include "ActionObject.h"
#include "ActionMoveTo.h"
#include "ActionJumpBy.h"
#include "ActionFadeTo.h"
#include "ActionRotateBy.h"
#include "ActionDelay.h"

const int REPEAT_FOREVER = -1;
const int REPEAT_ONCE = 0;

class SpriteActionSchedule{
private:
    //list of sprite actions
    std::list<ActionObject*> actionList;

    int repeat;
    int repeatCounter;
    int size;
    int iterateCounter;
    
public:
	//default constructor
    SpriteActionSchedule();
	//constructor
    SpriteActionSchedule(ActionObject* action);
	//copy constructor
    SpriteActionSchedule(const SpriteActionSchedule& other);
	//destructor
    ~SpriteActionSchedule();
    
	void createSchedule(ActionObject *action);
    void createSchedule(std::vector<ActionObject*> actions, int repeat);
//    void createSchedule(std::vector<SpriteAction*> &actions, int repeat);
    
    std::list<ActionObject*> &getList();
    
    double sharedUnusedTime;
    bool readyToUseUnusedTime;
    
    bool isRepeatDone();
    void countRepeat();
    bool isIterateDone();
    void countIterate();
    void reviveAllActions();
};

#endif /* defined(__OpenGL_2D_Framework__SpriteActionSchedule__) */
