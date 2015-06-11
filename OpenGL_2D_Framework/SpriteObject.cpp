//
//  SpriteObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteObject.h"
#include <iostream>

SpriteObject::SpriteObject() :
spriteID(ID_COUNTER),
actionRunning(false),
progPtr(0),
w(0),
h(0),
type(NORMAL_TYPE),
RenderableObject()
{
    progPtr = Director::getInstance().getProgramPtr();
    ID_COUNTER++;
    cout << "SpriteObject::SpriteObject()" << endl;
}

SpriteObject::SpriteObject(Program *ptr) :
spriteID(ID_COUNTER),
actionRunning(false),
progPtr(ptr),
w(0),
h(0),
type(NORMAL_TYPE),
RenderableObject()
{
    ID_COUNTER++;
    cout << "SpriteObject::SpriteObject(Program*)" << endl;
}

SpriteObject::~SpriteObject(){
	cout << "SpriteObject::Deleting...";
	for (std::list<ActionSchedule*>::const_iterator ci = actionScheduleList.begin(); ci != actionScheduleList.end(); ++ci){
		delete (*ci);
	}
	cout << "Done." << endl;
}

void SpriteObject::setZ_Depth(float value){
    if(value >= 100){
        value = 99;
    }
    else if(value < 0){
        value = 0;
    }
    
    z = value;
}

float SpriteObject::getZ_Depth(){
    return z;
}

void SpriteObject::addAction(ActionObject* action){
    addAction(action, 0);
}

void SpriteObject::addAction(ActionObject *action, int repeat){
    cout << "Adding Action#" << action->getActionID() << " to Sprite #" << spriteID << std::endl;
    //bind owner
    action->bindOwnerPtr(this);
    ActionSchedule* singleActionSchedule = new ActionSchedule();
    singleActionSchedule->createSchedule(action, repeat);
    actionScheduleList.push_back(singleActionSchedule);
}

void SpriteObject::addActions(std::initializer_list<ActionObject *> actions, int repeat){
    for(auto it:actions){
        it->bindOwnerPtr(this);
    }
    ActionSchedule* singleActionSchedule = new ActionSchedule();
    singleActionSchedule->createSchedule(actions, repeat);
    actionScheduleList.push_back(singleActionSchedule);
}

void SpriteObject::runAction(){
    actionRunning = true;
}

void SpriteObject::stopAction(){
    actionRunning = false;
    
    for(std::list<ActionSchedule*>::const_iterator ci = actionScheduleList.begin(); ci != actionScheduleList.end(); ++ci){
        (*ci)->terminateAllAction();
        delete (*ci);
    }
    actionScheduleList.clear();
}

bool SpriteObject::isActionRunning(){
    return actionRunning;
}

void SpriteObject::update(){
    //if there is no action, set running to false and return
    if(actionScheduleList.empty()){
        actionRunning = false;
        return;
    }
    
//    //iterate through schedule list
    for(auto schedule_it = actionScheduleList.begin(); schedule_it != actionScheduleList.end(); ){
//        cout << "Updating schedule" << endl;
        (*schedule_it)->updateSchedule();

        if((*schedule_it)->isEmpty()){
            delete *schedule_it;
            schedule_it = actionScheduleList.erase(schedule_it);
            continue;
        }
        else{
            //not empty, but is done?
            if((*schedule_it)->isFinished()){
                if((*schedule_it)->needRepeat()){
                    //revive, increment counter
                    cout << "Reviving schedule." << endl;
                    (*schedule_it)->reviveSchedule();
                    schedule_it++;
                }
                else{
                    //repeat done. delete list
                    cout << "Repeat done. deleting list." << endl;
                    delete *schedule_it;
                    schedule_it = actionScheduleList.erase(schedule_it);
                    continue;
                }
                
            }
            else{
                schedule_it++;
            }
        }
    }
}
