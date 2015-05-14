//
//  SpriteObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteObject__
#define __OpenGL_2D_Framework__SpriteObject__

//#include
#include "Program.h"
#include "SpriteAction.h"
#include "ActionMoveTo.h"
#include "Timer.h"
#include "ActionJumpBy.h"
#include "ActionFadeTo.h"
#include "ActionDelay.h"
#include "ActionRotateBy.h"
#include "ActionScaleBy.h"
#include "SpriteActionSchedule.h"

#include <vector>
#include <list>

#include "RenderableObject.h"

static int ID_COUNTER = 0;

class SpriteObject : public RenderableObject{
private:
	/**
	*	Update instant actions.
	*	Instant actions are actions with 0 duration. 
	*	
	*/
    void instantUpdate(SpriteAction *actionPtr, std::list<SpriteActionSchedule*>::const_iterator &ci, bool &instantHasNext, bool &sequence);
    void intervalUpdate(SpriteAction *actionPtr, std::list<SpriteActionSchedule*>::const_iterator &ci, bool &instantHasNext, bool &sequence);
	
//	WinSize size = Director::getInstance().getWindowSize();

protected:
    int spriteID;
    
    int w;
    int h;
    
//    glm::vec2 position;
    Program *progPtr;
    
    bool actionRunning;
    float z;    //each sprite can set 0~100.
    
	//Action schedule list
    std::list<SpriteActionSchedule *> spriteActionScheduleList;
    
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
	void addAction(SpriteAction *action);
	void addActions(SpriteActionSchedule &actions);
	void addActions(SpriteActionSchedule* actions);
    void runAction();
    void stopAction();
    
    std::list<SpriteAction*> getSpriteActionList();
    bool isActionRunning();
    
//    virtual void update() = 0;
    void update();
    void updateFromSpriteAction();
};

#endif /* defined(__OpenGL_2D_Framework__SpriteObject__) */
