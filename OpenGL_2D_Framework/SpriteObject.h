//
//  SpriteObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteObject__
#define __OpenGL_2D_Framework__SpriteObject__

#include "Program.h"
#include "RenderableObject.h"
#include "ActionSchedule.h"
#include "ActionObject.h"
//#include "ActionDelay.h"
//#include "ActionMoveTo.h"

#include <vector>
#include <list>
#include "Timer.h"

class ActionSchedule;

static int ID_COUNTER = 0;

class SpriteObject : public RenderableObject{
private:
protected:
    int spriteID;
    
    int w;
    int h;
    
    Program *progPtr;
    
    bool actionRunning;
    float z;    //each sprite can set 0~100.
    
	//Action schedule list
    std::list<ActionSchedule *> actionScheduleList;
    
public:
    SpriteObject();	//not implemented
    SpriteObject(Program *ptr);
    virtual ~SpriteObject();	//virtual!
    
    enum SpriteType{
        NORMAL_TYPE = 0,
        BILLBOARD_TYPE
    };
    
    SpriteType type;
    
    //z depth
    void setZ_Depth(float value);
    float getZ_Depth();
    
    //sprite action
	void addAction(ActionObject* action);
    void addAction(ActionObject* action, int repeat);
    void addActions(std::initializer_list<ActionObject*> actions, int repeat);
//	void addActions(SpriteActionSchedule &actions);
//	void addActions(SpriteActionSchedule* actions);
    void runAction();
    void stopAction();
    
    std::list<ActionObject*> getSpriteActionList();
    bool isActionRunning();
    
//    virtual void update() = 0;
    void update();
    void updateSpriteData(ActionObject* obj);
};

#endif /* defined(__OpenGL_2D_Framework__SpriteObject__) */
