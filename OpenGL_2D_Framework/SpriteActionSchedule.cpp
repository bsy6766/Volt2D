//
//  SpriteActionSchedule.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteActionSchedule.h"
#include <iostream>

using std::cout;
using std::endl;

SpriteActionSchedule::SpriteActionSchedule() :
repeat(0),
repeatCounter(0),
size(0),
iterateCounter(0),
sharedUnusedTime(0),
readyToUseUnusedTime(false)
{
    cout << "SpriteActionSchedule::Creating sprite action schedule" << endl;
            
}

SpriteActionSchedule::SpriteActionSchedule(ActionObject* action){
    assert(action != 0);
    
    this->actionList.push_back(action);
    
    this->repeat = 0;   //default
    this->repeatCounter = 0;
    this->size = 1; //single schedule
    this->iterateCounter = 0;   //init
    this->sharedUnusedTime = 0; //init
    this->readyToUseUnusedTime = false;
}

SpriteActionSchedule::SpriteActionSchedule(const SpriteActionSchedule& other) :
repeat(other.repeat),
repeatCounter(other.repeatCounter),
size(other.size),
iterateCounter(other.iterateCounter),
sharedUnusedTime(other.sharedUnusedTime),
readyToUseUnusedTime(other.readyToUseUnusedTime)
{
    for (std::list<ActionObject*>::const_iterator ci = other.actionList.begin(); ci != other.actionList.end(); ++ci){
        cout << "SpriteActionSchedule::Adding from list...action#" << (*ci)->getActionID() << endl;
        this->actionList.push_back(*ci);
    }
}

SpriteActionSchedule::~SpriteActionSchedule(){
    cout << "SpriteActionSchedule::Deleting...";
    
	for (auto& it : actionList){
		delete it;
	}
    
    cout << "Done." << endl;
}

void SpriteActionSchedule::createSchedule(ActionObject *action){
    actionList.push_back(action);
}

void SpriteActionSchedule::createSchedule(std::vector<ActionObject*> actions, int repeat){
    for(auto it : actions){
        this->actionList.push_back(it);
    }
    
    this->repeat = repeat;
    this->repeatCounter = 0;
    this->size = (int)actions.size();
    this->iterateCounter = 0;
    this->sharedUnusedTime = 0;
    this->readyToUseUnusedTime = false;
}

std::list<ActionObject*> &SpriteActionSchedule::getList(){
    return actionList;
}

bool SpriteActionSchedule::isRepeatDone(){
    if(repeat == REPEAT_FOREVER)
        return false;
    return repeat == repeatCounter;
}

bool SpriteActionSchedule::isIterateDone(){
    return size == iterateCounter;
}

void SpriteActionSchedule::countRepeat(){
    if(repeat == REPEAT_FOREVER)
        return;
    if(repeatCounter < repeat)
        repeatCounter++;
}

void SpriteActionSchedule::countIterate(){
    if(iterateCounter <= size)
        iterateCounter++;
}

void SpriteActionSchedule::reviveAllActions(){
    for(std::list<ActionObject*>::const_iterator ci = actionList.begin(); ci != actionList.end(); ++ci){
        switch ((*ci)->getActionID()) {
            case ACTION_MOVE_TO:
                static_cast<ActionMoveTo*>(*ci)->revive();
                break;
            case ACTION_FADE_TO:
                static_cast<ActionFadeTo*>(*ci)->revive();
                break;
            case ACTION_JUMP_BY:
                static_cast<ActionJumpBy*>(*ci)->revive();
                break;
            case ACTION_DELAY:
                static_cast<ActionDelay*>(*ci)->revive();
                break;
            case ACTION_ROTATE_BY:
                static_cast<ActionRotateBy*>(*ci)->revive();
                break;
            default:
                break;
        }
    }
    iterateCounter = 0;
}