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
//        ActionID actionId = (*action_it)->getActionID();
//        ActionType type = (*action_it)->getType();
        double elapsedTime = Timer::getInstance().getElapsedTime();
        double t = (*action_it)->setCurrentTime(elapsedTime);
        if(t != 0 && this->remainedTime == 0){
            cout << "t = " << t << endl;
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
        
        /*
        switch (actionId) {
            case ActionID::ACTION_DELAY:
            {
                ActionDelay *delayPtr = static_cast<ActionDelay*>(*action_it);
                //check starting. if alive but not running, run
                if(!delayPtr->isRunning()){
                    delayPtr->startAction();
//                    this->remainedTime = 0;
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
            case ActionID::ACTION_MOVE_TO:
            {
                ActionMoveTo *moveToPtr = static_cast<ActionMoveTo*>(*action_it);
                
                if(!moveToPtr->isRunning()){
                    moveToPtr->startAction();
//                    moveToPtr->setCurrentPos(moveToPtr->getOwner()->getPosition());
                }
            
                moveToPtr->updateAction(this->remainedTime);
                
//                moveToPtr->getOwner()->setPosition(moveToPtr->getMovedPosition());
                if(!moveToPtr->isAlive()){
                    if(instantSchedule) removeAction = true;
                }
                else{
                    finished = false;
                }
                break;
            }
            case ActionID::ACTION_MOVE_BY:
            {
                ActionMoveBy *moveByPtr = static_cast<ActionMoveBy*>(*action_it);
                
                if(!moveByPtr->isRunning()){
                    moveByPtr->startAction();
                }
            
                moveByPtr->updateAction(this->remainedTime);
                
//                moveByPtr->getOwner()->addPosition(moveByPtr->getMovedDistance());
                if(!moveByPtr->isAlive()){
                    if(instantSchedule) removeAction = true;
                }
                else{
                    finished = false;
                }
                break;
            }
            case ActionID::ACTION_ROTATE_TO:
            {
                ActionRotateTo* rotateToPtr = static_cast<ActionRotateTo*>(*action_it);
                if(!rotateToPtr->isRunning()){
                    rotateToPtr->startAction();
//                    rotateToPtr->setOriginalAngle(rotateToPtr->getOwner()->getAngle());
                }
                
                rotateToPtr->updateAction(this->remainedTime);
//                rotateToPtr->getOwner()->setAngle(rotateToPtr->getMovedAngle());
                
                if(!rotateToPtr->isAlive()){
                    if(instantSchedule) removeAction = true;
                }
                else{
                    finished = false;
                }
                break;
            }
            case ActionID::ACTION_ROTATE_BY:
            {
                ActionRotateBy* rotateByPtr = static_cast<ActionRotateBy*>(*action_it);
                if(!rotateByPtr->isRunning()){
                    rotateByPtr->startAction();
                }
                
                rotateByPtr->updateAction(this->remainedTime);
//                rotateByPtr->getOwner()->addAngle(rotateByPtr->getMovedAngle());
                
                if(!rotateByPtr->isAlive()){
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
            case ActionID::ACTION_FADE_TO:
            {
                ActionFadeTo* fadeToPtr = static_cast<ActionFadeTo*>(*action_it);
                if(!fadeToPtr->isRunning()){
                    fadeToPtr->startAction();
//                    fadeToPtr->setOriginalOpacity(fadeToPtr->getOwner()->getOpacity());
                }
                
                fadeToPtr->updateAction(this->remainedTime);
//                fadeToPtr->getOwner()->setOpacity(fadeToPtr->getFadedOpacity());
                
                if(!fadeToPtr->isAlive()){
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
            case ActionID::ACTION_FADE_BY:
            {
                ActionFadeBy* fadeByPtr = static_cast<ActionFadeBy*>(*action_it);
                if(!fadeByPtr->isRunning()){
                    fadeByPtr->startAction();
                }
                
                fadeByPtr->updateAction(this->remainedTime);
                fadeByPtr->getOwner()->addOpacity(fadeByPtr->getFadedOpacity());
                
                if(!fadeByPtr->isAlive()){
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
            case ActionID::ACTION_SCALE_TO:
            {
                ActionScaleTo* scaleToPtr = static_cast<ActionScaleTo*>(*action_it);
                if(!scaleToPtr->isRunning()){
                    scaleToPtr->startAction();
//                    scaleToPtr->setCurrentScale(scaleToPtr->getOwner()->getScale());
                }
                
                scaleToPtr->updateAction(this->remainedTime);
//                scaleToPtr->getOwner()->setScale(scaleToPtr->getScaledScale());
                
                if(!scaleToPtr->isAlive()){
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
            case ActionID::ACTION_SCALE_BY:
            {
                ActionScaleBy* scaleByPtr = static_cast<ActionScaleBy*>(*action_it);
                if(!scaleByPtr->isRunning()){
                    scaleByPtr->startAction();
                }
                
                scaleByPtr->updateAction(this->remainedTime);
//                scaleByPtr->getOwner()->addScale(scaleByPtr->getScaledScale());
                
                if(!scaleByPtr->isAlive()){
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
            case ActionID::ACTION_JUMP_TO:
            {
                break;
            }
            case ActionID::ACTION_JUMP_BY:
            {
                break;
            }
            case ActionID::ACTION_BLINK:
            {
                break;
            }
            default:
                break;
        }
        */
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