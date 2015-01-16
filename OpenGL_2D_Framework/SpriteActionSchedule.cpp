//
//  SpriteActionSchedule.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/4/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "SpriteActionSchedule.h"
#include <iostream>

using std::cout;
using std::endl;

SpriteActionSchedule::SpriteActionSchedule(){
    cout << "Creating sprite action schedule" << endl;
}

SpriteActionSchedule::SpriteActionSchedule(SpriteAction* other){
    this->actionList.push_back(other);
    
    this->repeat = 0;   //default
    this->repeatCounter = 0;
    this->size = 1; //single schedule
    this->iterateCounter = 0;   //init
    this->sharedUnusedTime = 0; //init
    this->readyToUseUnusedTime = false;
}

SpriteActionSchedule::SpriteActionSchedule(const SpriteActionSchedule& other){
    for (std::list<SpriteAction*>::const_iterator ci = other.actionList.begin(); ci != other.actionList.end(); ++ci){
        cout << "\tAdding from list...action#" << (*ci)->getActionID() << endl;
        this->actionList.push_back(*ci);
    }
    this->repeat = other.repeat;
    this->repeatCounter = other.repeatCounter;
    this->size = other.size;
    this->iterateCounter = other.iterateCounter;
    this->sharedUnusedTime = other.sharedUnusedTime;
    this->readyToUseUnusedTime = other.readyToUseUnusedTime;
}

SpriteActionSchedule::~SpriteActionSchedule(){

}

void SpriteActionSchedule::createSchedule(SpriteAction *action){
    actionList.push_back(action);
}

void SpriteActionSchedule::createSchedule(std::vector<SpriteAction*> &actions, int repeat){
    cout << "Creating Sprite Action Schedule..." << endl;
    this->repeat = repeat;
    this->repeatCounter = 0;
    this->size = (int)actions.size();
    this->iterateCounter = 0;
    this->sharedUnusedTime = 0;
    this->readyToUseUnusedTime = false;
    
    for (int i = 0; i<(int)actions.size(); ++i){
        SpriteAction *dataPtr, *clonePtr;
        switch(actions.at(i)->getActionID()){
            case ACTION_MOVE_TO:
            {
                cout << "\tMoveTo...";
                //cast to actual action pointer
                dataPtr = static_cast<ActionMoveTo*>(actions.at(i));
                clonePtr = new ActionMoveTo();
                //create clone
                break;
            }
            case ACTION_JUMP_BY:
            {
                cout << "\tJumpBy...";
                dataPtr = static_cast<ActionJumpBy*>(actions.at(i));
                clonePtr = new ActionJumpBy();
                break;
            }
            case ACTION_FADE_TO:
            {
                cout << "\tFadeTo...";
                dataPtr = static_cast<ActionFadeTo*>(actions.at(i));
                clonePtr = new ActionFadeTo();
                break;
            }
            case ACTION_DELAY:
            {
                cout << "\tDelay...";
                dataPtr = static_cast<ActionDelay*>(actions.at(i));
                clonePtr = new ActionDelay();
                break;
            }
            case ACTION_ROTATE_BY:
            {
                cout << "\tRotateBy...";
                dataPtr = static_cast<ActionRotateBy*>(actions.at(i));
                clonePtr = new ActionRotateBy();
                break;
            }
            default:
            {
                std::cout << "uh...what action?" << std::endl;
                break;
            }
        }
        //copy data
        clonePtr->clone(dataPtr);
        //set pointer to this clone;
        
        //add ptr
        this->actionList.push_back(clonePtr);
        cout << "\tAdded." << endl;;
    }
}

std::list<SpriteAction*> &SpriteActionSchedule::getList(){
    return actionList;
}

bool SpriteActionSchedule::isRepeatDone(){
//    return true;
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
    for(std::list<SpriteAction*>::const_iterator ci = actionList.begin(); ci != actionList.end(); ++ci){
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