//
//  ActionSchedule.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/17/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionSchedule.h"

ActionSchedule::ActionSchedule():
repeat(0),
repeatCounter(0),
instantSchedule(false),
finished(false),
remainedTime(0)
{
    cout << "Creating action schedule" << endl;
}

ActionSchedule::~ActionSchedule(){
    cout << "Deleting action schedule" << endl;
}

void ActionSchedule::createSchedule(ActionObject *action, int repeat){
    if(repeat == 0)
        instantSchedule = true;
    else
        instantSchedule = false;
    this->repeat = repeat;
    repeatCounter = 0;
    if(!actionList.empty())
        clearList();
    actionList.push_back(action);
    
//    createSchedule(&action, 1, repeat);
}

void ActionSchedule::createSchedule(ActionObject **actions, int size, int repeat){
    if(repeat == 0)
        instantSchedule = true;
    else
        instantSchedule = false;
    this->repeat = repeat;
    repeatCounter = 0;
    if(!actionList.empty())
        clearList();
    
    for(int i = 0; i < size; i++){
        actionList.push_back(actions[i]);
    }
}

void ActionSchedule::createSchedule(std::initializer_list<ActionObject *>& actions, int repeat){
    if(repeat == 0)
        instantSchedule = true;
    else
        instantSchedule = false;
    this->repeat = repeat;
    repeatCounter = 0;
    if(!actionList.empty())
        clearList();
    
    for(auto it : actions){
        auto clone = it->clone();
        clone->bindTarget(it->getTarget());
        actionList.push_back(clone);
    }
}

void ActionSchedule::clearList(){
    cout << "ActionSchedule::Clearing existing action list" << endl;
    for(auto it : actionList){
        delete it;
    }
    actionList.clear();
}

void ActionSchedule::terminateAllAction(){
    clearList();
}

bool ActionSchedule::isInstant(){
    return instantSchedule;
}

void ActionSchedule::updateSchedule(){
    finished = true;
    
    for(auto action_it = actionList.begin(); action_it != actionList.end();){
        if(!(*action_it)->isAlive()){
            action_it++;
            continue;
        }
        
        double elapsedTime = Timer::getInstance().getElapsedTime();
        double t = (*action_it)->setCurrentTime(elapsedTime);
        if(t != 0 && this->remainedTime == 0){
//            cout << "t = " << t << endl;
            this->remainedTime = t;
        }
        
        bool removeAction = false;
        
        //now no need to check aciton id
        if(!(*action_it)->isRunning()){
            (*action_it)->startAction();
        }
        //update
        (*action_it)->updateAction(this->remainedTime);
        
        //if action is dead after update
        if(!(*action_it)->isAlive()){
            //and don't need to be repeated, delete from list
            if(instantSchedule){
                removeAction = true;
            }
            //else, leave action.
        }
        else{
            finished = false;
        }
        
        if(removeAction){
            delete *action_it;
            action_it = actionList.erase(action_it);
        }
        else{
            action_it++;
        }
        if(!finished)
            break;
    }
}

bool ActionSchedule::isEmpty(){
    return actionList.size() == 0;
}

bool ActionSchedule::isFinished(){
    return finished;
}

void ActionSchedule::reviveSchedule(){
    for(auto it : actionList){
        it->revive();
    }
    repeatCounter++;
}

bool ActionSchedule::needRepeat(){
    if(instantSchedule)
        return false;
    
    return repeat != repeatCounter;
}

std::list<ActionObject*>& ActionSchedule::getList(){
    return actionList;
}