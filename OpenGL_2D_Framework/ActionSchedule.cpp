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
        actionList.push_back(it);
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
//        cout << "prcoessing ID = " << (*action_it)->objID << endl;
        ActionID actionId = (*action_it)->getActionID();
        double elapsedTime = Timer::getInstance().getElapsedTime();
        double t = (*action_it)->setCurrentTime(elapsedTime);
        if(t != 0 && this->remainedTime == 0){
            cout << "t = " << t << endl;
            this->remainedTime = t;
        }
        
        bool removeAction = false;
        
        switch (actionId) {
            case ACTION_DELAY:
            {
                ActionDelay *delayPtr = static_cast<ActionDelay*>(*action_it);
                //check starting. if alive but not running, run
                if(!delayPtr->isRunning()){
                    delayPtr->startAction();
                    this->remainedTime = 0;
                }
                //update
                delayPtr->updateAction(this->remainedTime);
                
                //if action is dead after update
                if(!delayPtr->isAlive()){
                    //and don't need to be repeated, delete from list
                    if(instantSchedule){
                        removeAction = true;
                    }
                    //else, leave action.
                }
                else{
                    finished = false;
                }
                break;
            }
            case ACTION_MOVE_TO:
            {
                ActionMoveTo *moveToPtr = static_cast<ActionMoveTo*>(*action_it);
                
                if(!moveToPtr->isRunning()){
                    cout << "Staring move to. rt = " << remainedTime << endl;
                    moveToPtr->startAction();
                    moveToPtr->setOriginalPosition(moveToPtr->getOwner()->getPosition(), true);
                    moveToPtr->updateAction(this->remainedTime);
                    this->remainedTime = 0;
                }
                else{
                    moveToPtr->updateAction(0);
                }
                
                //update position
                moveToPtr->getOwner()->setPosition(moveToPtr->getOwner()->getPosition() + moveToPtr->getMovedDistance());
                glm::vec3 curPos = moveToPtr->getOwner()->getPosition();
                
//                cout << "Moving (" << curPos.x << ", " << curPos.y << ", " << curPos.z << endl;
                
                if(!moveToPtr->isAlive()){
                    if(instantSchedule){
                        removeAction = true;
                    }
                    //else, leave action.
                }
                else{
                    finished = false;
                }
                break;
            }
            case ACTION_MOVE_BY:
            {
                ActionMoveBy *moveByPtr = static_cast<ActionMoveBy*>(*action_it);
                
                if(!moveByPtr->isRunning()){
                    moveByPtr->startAction();
                    moveByPtr->setStartingPos(moveByPtr->getOwner()->getPosition());
                    moveByPtr->updateAction(this->remainedTime);
                    this->remainedTime = 0;
                }
                else{
                    moveByPtr->updateAction(0);
                }
                
                //update position
                moveByPtr->getOwner()->setPosition(moveByPtr->getOwner()->getPosition() + moveByPtr->getMovedDistance());
                glm::vec3 curPos = moveByPtr->getOwner()->getPosition();
                
                temp += moveByPtr->getMovedDistance();
                
//                cout << "temp = (" << temp.x << ", " << temp.y << ", " << temp.z << ")" << endl;
//                cout << "Moving (" << curPos.x << ", " << curPos.y << ", " << curPos.z << ")" << endl;
                
                if(!moveByPtr->isAlive()){
                    if(instantSchedule){
                        removeAction = true;
                    }
                    //else, leave action.
                }
                else{
                    finished = false;
                }
                break;
            }
            default:
                break;
        }
        
        if(removeAction){
            delete *action_it;
            action_it = actionList.erase(action_it);
        }
        else{
            action_it++;
        }
//        this->remainedTime = 0;
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