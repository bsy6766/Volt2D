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
}

SpriteObject::~SpriteObject(){
	cout << "SpriteObject::Deleting...";
	for (std::list<SpriteActionSchedule *>::const_iterator ci = spriteActionScheduleList.begin(); ci != spriteActionScheduleList.end(); ++ci){
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

void SpriteObject::addAction(ActionObject *action){
//    SpriteActionSchedule
    cout << "Adding Action#" << action->getActionID() << " to Sprite #" << spriteID << std::endl;
    spriteActionScheduleList.push_back(new SpriteActionSchedule(action));
}

void SpriteObject::addActions(SpriteActionSchedule &actions){
    cout << "Adding list of actions reference to Sprite #" << spriteID << std::endl;
    spriteActionScheduleList.push_back(new SpriteActionSchedule(actions));
}

void SpriteObject::addActions(SpriteActionSchedule* actions){
	cout << "Adding list of actions pointer to Sprite #" << spriteID << std::endl;
	spriteActionScheduleList.push_back(actions);
}

void SpriteObject::runAction(){
    actionRunning = true;
}

void SpriteObject::stopAction(){
    actionRunning = false;
    
    for(std::list<SpriteActionSchedule*>::const_iterator ci = spriteActionScheduleList.begin(); ci != spriteActionScheduleList.end(); ++ci){
        std::list<ActionObject*> spriteActionList = (*ci)->getList();
        for(std::list<ActionObject*>::const_iterator i = spriteActionList.begin(); i != spriteActionList.end(); ++i){
            (*i)->alive = false;
            (*i)->running = false;
            delete (*i);
        }
        spriteActionList.clear();
        delete (*ci);
    }
    spriteActionScheduleList.clear();
}

bool SpriteObject::isActionRunning(){
    return actionRunning;
}

void SpriteObject::update(){
    //if there is no action, set running to false and return
    if(spriteActionScheduleList.empty()){
        actionRunning = false;
        return;
    }
    
    //iterate through schedule list
    for(std::list<SpriteActionSchedule*>::const_iterator ci = spriteActionScheduleList.begin(); ci != spriteActionScheduleList.end(); ++ci){
        //get first schedule from list
        std::list<ActionObject*> spriteActionList = (*ci)->getList();
        
        //iterate through the schedule(even if theres only one action!)
        bool sequence = true;
        bool instantHasNext = false;
        
        for(std::list<ActionObject*>::const_iterator i = spriteActionList.begin(); i != spriteActionList.end() && sequence; ++i){
            //get first action
            //if action is dead(already processed), just continue to next action
            if(!(*i)->isAlive())
                continue;

            //get id, because we have tons of different actions...
            ActionID actionID = (*i)->getActionID();
            
            switch (actionID) {
                case ACTION_MOVE_TO:
                {
                    //cast sprite action to move to
                    ActionMoveTo *moveToPtr = static_cast<ActionMoveTo*>(*i);
                    //if action is alive, and now running, has original position...run the algorithm.
                    
                    //if action is alive(probably guaranteed at this point), but isn't running yet,
                    if(moveToPtr->isAlive() && !moveToPtr->isRunning()){
                        //set running to true
                        moveToPtr->startAction();
                        //set starting point
                        moveToPtr->setOriginalPosition(glm::vec2(position.x, position.y), true);
                    }
                    //but handle instant action first.
                    if(moveToPtr->getDuration() == 0){
                        instantUpdate(moveToPtr, ci, instantHasNext, sequence);
                        //update position
                        glm::vec2 d = moveToPtr->getMovedDistance();
                        position += glm::vec3(d.x, d.y, 0);
//                        position += moveToPtr->getMovedDistance();
                    }
                    else{
                        //since instant action doesn't consume iteration and get updated right away in here, we have to delete on next action
                        //also need to check if schedule needs to repeat
                        intervalUpdate(moveToPtr, ci, instantHasNext, sequence);
                    }
                    break;
                }
//                case ACTION_JUMP_BY:
//                {
//                    ActionJumpBy *jumpByPtr = static_cast<ActionJumpBy*>(*i);
//                    
//                    if(jumpByPtr->isAlive() && !jumpByPtr->isRunning()){
//                        jumpByPtr->startAction();
//                        jumpByPtr->setJumpingPosition(position, true);
//                    }
//                    
//                    //0 second instant. if x value is same with sprite's position, no need to process thing.
//                    //instant
//                    if(jumpByPtr->getDuration() == 0){
//                        //same x, just y, 0 second, stay...
//                        if(jumpByPtr->getDistance().x == 0){
//                            jumpByPtr->running = false;
//                            jumpByPtr->alive = false;
//                        }
//                        else{
//                            instantUpdate(jumpByPtr, ci, instantHasNext, sequence);
//                            //update Position
//                            position += jumpByPtr->getMovedDistance();
//                        }
//                    }
//                    else{
//                        intervalUpdate(jumpByPtr, ci, instantHasNext, sequence);
//                    }
//                    
//                    break;
//                }
                case ACTION_FADE_TO:
                {
                    ActionFadeTo *fadeToPtr = static_cast<ActionFadeTo*>(*i);
                    
                    if(fadeToPtr->isAlive() && !fadeToPtr->isRunning()){
                        cout << "Sprite #" << spriteID << " starting ACTION_FADE_TO" << endl;
                        fadeToPtr->startAction();
                        fadeToPtr->setOriginalOpacity(opacity);
                    }
                    
                    if(fadeToPtr->getDuration() == 0){
                        instantUpdate(fadeToPtr, ci, instantHasNext, sequence);
                        
                        opacity = fadeToPtr->getFadedOpacity();
                    }
                    else{
                        intervalUpdate(fadeToPtr, ci, instantHasNext, sequence);
                    }
                    break;
                }
                    
                case ACTION_DELAY:
                {
                    ActionDelay *delayPtr = static_cast<ActionDelay*>(*i);
                    
                    if(delayPtr->isAlive() && !delayPtr->isRunning()){
                        cout << "Sprite #" << spriteID << " starting ACTION_DELAY" << endl;
                        delayPtr->startAction();
                    }
                    
                    if(delayPtr->getDuration() == 0){
                        instantUpdate(delayPtr, ci, instantHasNext, sequence);
                    }
                    else{
                        intervalUpdate(delayPtr, ci, instantHasNext, sequence);
                    }
                    break;
                }
                
                case ACTION_ROTATE_BY:
                {
                    ActionRotateBy *rotateByPtr = static_cast<ActionRotateBy*>(*i);
                    
                    if(rotateByPtr->isAlive() && !rotateByPtr->isRunning()){
                        rotateByPtr->startAction();
                        rotateByPtr->setOriginalAngle(angle, true);
                    }
                    
                    if(rotateByPtr->getDuration() == 0){
                        instantUpdate(rotateByPtr, ci, instantHasNext, sequence);
                        
                        angle += rotateByPtr->getMovedAngle();
                    }
                    else{
                        intervalUpdate(rotateByPtr, ci, instantHasNext, sequence);
                    }
                    break;
                }
//                case ACTION_SCALE_BY:
//                {
//                    ActionScaleBy *scaleByPtr = static_cast<ActionScaleBy*>(*i);
//                    
//                    if(scaleByPtr->isAlive() && !scaleByPtr->isRunning()){
//                        scaleByPtr->startAction();
//                        scaleByPtr->setOriginalScale(scale);
//                    }
//                    
//                    if(scaleByPtr->getDuration() == 0){
//                        instantUpdate(scaleByPtr, ci, instantHasNext, sequence);
//                        scale += scaleByPtr->getScaledScale();
//                    }
//                    else{
//                        intervalUpdate(scaleByPtr, ci, instantHasNext, sequence);
//                    }
//                    break;
//                }
                default:
                    break;
            }//switch end
        }//for iterator action list end
        //after iterating single schedule, increment repeat counter
        //        (*ci)->count();
    }//for iterator schedule list end
}

void SpriteObject::instantUpdate(ActionObject *actionPtr, std::list<SpriteActionSchedule*>::const_iterator &ci, bool &instantHasNext, bool &sequence){
    actionPtr->update(-1, 0);
    
    //if action is done, increment interate counter;
    if(!actionPtr->isAlive()){
        (*ci)->countIterate();
    }
    
    //check if there are other actions on the schedule
    if(!(*ci)->isIterateDone()){
        //if so, mark true, else false by default
        instantHasNext = true;
    }
    else{
        //if this is the last action, break sequence
        sequence = false;
    }
    
    //now, action si done, not running, but alive, don't worry :)
    actionPtr->running = false;
}

void SpriteObject::intervalUpdate(ActionObject *actionPtr, std::list<SpriteActionSchedule *>::const_iterator &ci, bool &instantHasNext, bool &sequence){
    if(instantHasNext && (*ci)->isRepeatDone()){
        if(!(*ci)->getList().front()->isProtected){
            delete (*ci)->getList().front();
        }
        (*ci)->getList().pop_front();
    }
    
    double elapsedTime = Timer::getInstance().getElapsedTime();
    
    // update action with elapsed time and get unused time
    double unusedTime = actionPtr->setCurrentTime(elapsedTime);
    
    //if unused time is able to use
    if((*ci)->readyToUseUnusedTime){
        //update with unusedTime.
        actionPtr->update(elapsedTime, (*ci)->sharedUnusedTime);
        (*ci)->readyToUseUnusedTime = false;
        (*ci)->sharedUnusedTime = 0;
    }
    else{
        actionPtr->update(elapsedTime, 0);
        if(unusedTime > 0){
            (*ci)->readyToUseUnusedTime = true;
            (*ci)->sharedUnusedTime = unusedTime;
        }
    }
    
    //if current action is dead, we consider this as one iteration of sequence
    if(!actionPtr->isAlive()){
        (*ci)->countIterate();
    }
    
    //since this is a sequence, break the for loop
    sequence = false;
}

void SpriteObject::updateFromSpriteAction(){
    //update from all actions
    if(spriteActionScheduleList.empty())
        return;
    
    bool scheduleEmpty = false;
    //iterate through schedule
    for(std::list<SpriteActionSchedule*>::const_iterator ci = spriteActionScheduleList.begin(); ci != spriteActionScheduleList.end(); ++ci){
        if((*ci)->getList().empty()){
            scheduleEmpty = true;
            continue;
        }
        
        std::list<ActionObject*>::const_iterator action_ci;
        
        bool allActionDead = true;
        for(action_ci = (*ci)->getList().begin(); action_ci != (*ci)->getList().end(); ++action_ci){
            if ((*action_ci)->isAlive() || (*action_ci)->isRunning()) {
                if(!(*action_ci)->isAlive()){
                    (*action_ci)->running = false;
                }
                allActionDead = false;
                break;
            }
        }
        
        //if there is at least one running(even if its dead) action
        if(!allActionDead){
            //update
            ActionID actionID = (*action_ci)->getActionID();
            switch (actionID) {
                case ACTION_MOVE_TO:
                {
                    ActionMoveTo *ptr = static_cast<ActionMoveTo*>(*action_ci);
//                    position += ptr->getMovedDistance();
                    glm::vec2 d = ptr->getMovedDistance();
                    position += glm::vec3(d.x, d.y, 0);
                    setPosition(position);
                    break;
                }
                    
                case ACTION_JUMP_BY:
                {
                    ActionJumpBy *ptr = static_cast<ActionJumpBy*>(*action_ci);
//                    position += ptr->getMovedDistance();
                    glm::vec2 d = ptr->getMovedDistance();
                    position += glm::vec3(d.x, d.y, 0);
                    break;
                }
                case ACTION_FADE_TO:
                {
                    ActionFadeTo *ptr = static_cast<ActionFadeTo*>(*action_ci);
                    opacity += ptr->getFadedOpacity();
                    break;
                }
                case ACTION_DELAY:
                {
                    //we do nothing...just wait and consume time!
                    break;
                }
                case ACTION_ROTATE_BY:
                {
                    ActionRotateBy *ptr = static_cast<ActionRotateBy*>(*action_ci);
                    if(angle > 360)
                        angle -= 360;
                    else if(angle < 0)
                        angle += 360;
                    
                    angle += ptr->getMovedAngle();
                    break;
                }
                case ACTION_SCALE_BY:
                {
//                    ActionScaleBy *ptr = static_cast<ActionScaleBy*>(*action_ci);
//                    scale += ptr->getScaledScale();
                }
                default:
                    break;
            }
            
            if(!(*action_ci)->isAlive() && (*ci)->isRepeatDone()){
                if(!(*ci)->getList().front()->isProtected){
                    cout << "sprite#" << spriteID << " deleting it's action#" << (*ci)->getList().front()->getActionID() << std::endl;
                    delete(*ci)->getList().front();
                }
                cout << "sprite#" << spriteID << " popping it's action#" << (*ci)->getList().front()->getActionID() << std::endl;
                (*ci)->getList().pop_front();
                if((*ci)->getList().empty()){
                    scheduleEmpty = true;
                }
            }
            
        }
        
        //if iteration is done, all action is dead, but need to repeat,
        if((*ci)->isIterateDone() && allActionDead && !(*ci)->isRepeatDone()){
            //revive all the actions
            (*ci)->reviveAllActions();
        }
        
    }
    
    if(scheduleEmpty){
        delete spriteActionScheduleList.front();
        spriteActionScheduleList.pop_front();
        scheduleEmpty = false;
    }
}
