//
//  SpriteObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteObject__
#define __OpenGL_2D_Framework__SpriteObject__

#include "RenderableObject.h"
//#include "ActionObject.h"
//#include "test.cpp"
//#include "ActionDelay.h"
//#include "ActionMoveTo.h"

#include <vector>
#include <list>
#include "Timer.h"

//class ActionSchedule;

static int ID_COUNTER = 0;

class SpriteObject : public RenderableObject{
private:
protected:
    int spriteID;
    
    int w;
    int h;
    

//    float z;    //each sprite can set 0~100.
    
	//Action schedule list
public:
    SpriteObject();	//not implemented
//    SpriteObject(Program *ptr);
    virtual ~SpriteObject();	//virtual!
    
    enum SpriteType{
        NORMAL_TYPE = 0,
        BILLBOARD_TYPE
    };
    
    SpriteType type;
    
    //z depth
//    void setZ_Depth(float value);
//    float getZ_Depth();
    
//    //sprite action
//	void addAction(ActionObject* action);
//    void addAction(ActionObject* action, int repeat);
//    void addActions(std::initializer_list<ActionObject*> actions, int repeat);
//    void runAction();
//    void stopAction();
//    bool isActionRunning();
//    void update();
//    void updateSpriteData(ActionObject* obj);
};

#endif /* defined(__OpenGL_2D_Framework__SpriteObject__) */
