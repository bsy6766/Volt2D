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
    ActionSchedule* singleActionSchedule = new ActionSchedule();
    singleActionSchedule->createSchedule(action, repeat);
    actionScheduleList.push_back(singleActionSchedule);
}

void SpriteObject::addActions(std::initializer_list<ActionObject *> actions, int repeat){
    ActionSchedule* singleActionSchedule = new ActionSchedule();
    singleActionSchedule->createSchedule(actions, repeat);
    actionScheduleList.push_back(singleActionSchedule);
}

//void SpriteObject::addActions(SpriteActionSchedule &actions){
//    cout << "Adding list of actions reference to Sprite #" << spriteID << std::endl;
//    spriteActionScheduleList.push_back(new SpriteActionSchedule(actions));
//}
//
//void SpriteObject::addActions(SpriteActionSchedule* actions){
//	cout << "Adding list of actions pointer to Sprite #" << spriteID << std::endl;
//	spriteActionScheduleList.push_back(actions);
//}

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
        cout << "Updating schedule" << endl;
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
        }
//        double remainedTimeByDeath = 0;
//        //true: schedule is done. need to revive. False: at least one action is alive.
//        bool scheduleFinished = true;
//        //get reference to list of SpriteActions
//        std::list<ActionObject*>& actionSchedule = (*schedule_it)->getList();
//        //iterate through list of SpriteActions
//        for(auto action_it = actionSchedule.begin(); action_it != actionSchedule.end(); ){
//            //get Action ID
//            ActionID actionId = (*action_it)->getActionID();
//            bool finishScheduleIteration = false;
//            
//            //before we proceed, check if action is dead. If so, continue to next action
//            //Note: action will be dead and remain on schedule only if it needs to repeat
//            if((*action_it)->isAlive())
//                continue;
//            
//            switch (actionId) {
//                case ACTION_DELAY:
//                {
//                    //cast to delay action
//                    ActionDelay *delayPtr = static_cast<ActionDelay*>(*action_it);
//                    //update current action
//                    delayPtr->updateAction();
//                    
//                    //if action is still alive after update, proceed to next schedule.
//                    if(delayPtr->isAlive()){
//                        finishScheduleIteration = true;
//                        scheduleFinished = false;
//                    }
//                    //if action is dead after update
//                    else{
//                        //action is done.
//                        //get remained time and use one next
//                        remainedTimeByDeath = delayPtr->getRemainedTime();
//                        //if the schedule needs to run only once, delete action
//                        if((*schedule_it)->isInstantSchedule()){
//                            delete *action_it;
//                            action_it = actionSchedule.erase(action_it);
//                        }
//                        //else, it needs to remain in schedule and wait to revive. so nothing to do here.
//                    }
//                    break;
//                }
//                default:
//                    break;
//            }
//            
//            //if running action is still alive, break the loop(schedule)
//            if(finishScheduleIteration){
//                break;
//            }
//            
//            //manually increment schedule iterator
//            ++action_it;
//        }
//        //iteration for single schedule is done.
//        //if schedule is empty, it means schedule was meant to run only once and all actions have been proceessed. So, remove from schedule list.
//        if(actionSchedule.empty()){
//            delete &actionSchedule;
//            schedule_it = spriteActionScheduleList.erase(schedule_it);
//            continue;
//        }
//        //not empty
//        //if all action is dead == they are still there because they need to be repeated, increment repeater and revive all.
//        if(scheduleFinished){
//            (*schedule_it)->reviveAllActions();
//        }
    }
    
    
    
    
    //iterate through schedule list
//    for(std::list<SpriteActionSchedule*>::const_iterator ci = spriteActionScheduleList.begin(); ci != spriteActionScheduleList.end(); ++ci){
//        //get first schedule from list
//        std::list<ActionObject*> spriteActionList = (*ci)->getList();
//        
//        //iterate through the schedule(even if theres only one action!)
//        bool sequence = true;
//        bool instantHasNext = false;
//        
//        for(std::list<ActionObject*>::const_iterator i = spriteActionList.begin(); i != spriteActionList.end() && sequence; ++i){
//            //get first action
//            //if action is dead(already processed), just continue to next action
//            if(!(*i)->isAlive())
//                continue;
//
//            //get id, because we have tons of different actions...
//            ActionID actionID = (*i)->getActionID();
//            
//            switch (actionID) {
//                case ACTION_MOVE_TO:
//                {
//                    //cast sprite action to move to
//                    ActionMoveTo *moveToPtr = static_cast<ActionMoveTo*>(*i);
//                    //if action is alive, and now running, has original position...run the algorithm.
//                    
//                    //if action is alive(probably guaranteed at this point), but isn't running yet,
//                    if(moveToPtr->isAlive() && !moveToPtr->isRunning()){
//                        //set running to true
//                        moveToPtr->startAction();
//                        //set starting point
//                        moveToPtr->setOriginalPosition(glm::vec2(position.x, position.y), true);
//                    }
//                    //but handle instant action first.
//                    if(moveToPtr->getDuration() == 0){
//                        instantUpdate(moveToPtr, ci, instantHasNext, sequence);
//                        //update position
//                        glm::vec2 d = moveToPtr->getMovedDistance();
//                        position += glm::vec3(d.x, d.y, 0);
////                        position += moveToPtr->getMovedDistance();
//                    }
//                    else{
//                        //since instant action doesn't consume iteration and get updated right away in here, we have to delete on next action
//                        //also need to check if schedule needs to repeat
//                        intervalUpdate(moveToPtr, ci, instantHasNext, sequence);
//                    }
//                    //update position.
//                    glm::vec2 d = moveToPtr->getMovedDistance();
//                    position += glm::vec3(d.x, d.y, 0);
//                    setPosition(position);
//                    break;
//                }
//                case ACTION_JUMP_BY:
//                {
//                    ActionJumpBy *jumpByPtr = static_cast<ActionJumpBy*>(*i);
//                    
//                    if(jumpByPtr->isAlive() && !jumpByPtr->isRunning()){
//                        jumpByPtr->startAction();
//                        jumpByPtr->setJumpingPosition(glm::vec2(position.x, position.y), true);
//                    }
//                    
//                    if(jumpByPtr->getDuration() == 0){
//                        //same x, just y, 0 second, stay...
//                        if(jumpByPtr->getDistance().x == 0){
//                            jumpByPtr->running = false;
//                            jumpByPtr->alive = false;
//                        }
//                        else{
//                            instantUpdate(jumpByPtr, ci, instantHasNext, sequence);
//                            glm::vec2 d = jumpByPtr->getMovedDistance();
//                            position += glm::vec3(d.x, d.y, 0);
//                        }
//                    }
//                    else{
//                        intervalUpdate(jumpByPtr, ci, instantHasNext, sequence);
//                    }
//                    
//                    break;
//                }
//                case ACTION_FADE_TO:
//                {
//                    ActionFadeTo *fadeToPtr = static_cast<ActionFadeTo*>(*i);
//                    
//                    if(fadeToPtr->isAlive() && !fadeToPtr->isRunning()){
//                        cout << "Sprite #" << spriteID << " starting ACTION_FADE_TO" << endl;
//                        fadeToPtr->startAction();
//                        fadeToPtr->setOriginalOpacity(opacity);
//                    }
//                    
//                    if(fadeToPtr->getDuration() == 0){
//                        instantUpdate(fadeToPtr, ci, instantHasNext, sequence);
//                        opacity = fadeToPtr->getFadedOpacity();
//                    }
//                    else{
//                        intervalUpdate(fadeToPtr, ci, instantHasNext, sequence);
//                    }
//                    //update opacity
//                    opacity += fadeToPtr->getFadedOpacity();
//                    break;
//                }
//                    
//                case ACTION_DELAY:
//                {
//                    ActionDelay *delayPtr = static_cast<ActionDelay*>(*i);
//                    
//                    if(delayPtr->isAlive() && !delayPtr->isRunning()){
//                        cout << "Sprite #" << spriteID << " starting ACTION_DELAY" << endl;
//                        delayPtr->startAction();
//                    }
//                    
//                    if(delayPtr->getDuration() == 0){
//                        instantUpdate(delayPtr, ci, instantHasNext, sequence);
//                    }
//                    else{
//                        intervalUpdate(delayPtr, ci, instantHasNext, sequence);
//                    }
//                    //nothing to update here. just delay!
//                    break;
//                }
//
//                case ACTION_ROTATE_BY:
//                {
//                    ActionRotateBy *rotateByPtr = static_cast<ActionRotateBy*>(*i);
//                    
//                    if(rotateByPtr->isAlive() && !rotateByPtr->isRunning()){
//                        rotateByPtr->startAction();
//                        rotateByPtr->setOriginalAngle(angle, true);
//                    }
//                    
//                    if(rotateByPtr->getDuration() == 0){
//                        instantUpdate(rotateByPtr, ci, instantHasNext, sequence);
//                        
//                        angle += rotateByPtr->getMovedAngle();
//                    }
//                    else{
//                        intervalUpdate(rotateByPtr, ci, instantHasNext, sequence);
//                    }
//                    break;
//                }
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
//                default:
//                    break;
//            }//switch end
//        }//for iterator action list end
//        //after iterating single schedule, increment repeat counter
//        //        (*ci)->count();
//    }//for iterator schedule list end
}

//void SpriteObject::instantUpdate(ActionObject *actionPtr, std::list<SpriteActionSchedule*>::const_iterator &ci, bool &instantHasNext, bool &sequence){
//    actionPtr->instantUpdate();
//    
//    //if action is done, increment interate counter;
//    if(!actionPtr->isAlive()){
//        (*ci)->countIterate();
//    }
//    
//    //check if there are other actions on the schedule
//    if(!(*ci)->isIterateDone()){
//        //if so, mark true, else false by default
//        instantHasNext = true;
//    }
//    else{
//        //if this is the last action, break sequence
//        sequence = false;
//    }
//    
//    //now, action si done, not running, but alive, don't worry :)
//    actionPtr->running = false;
//}
//
//void SpriteObject::intervalUpdate(ActionObject *actionPtr, std::list<SpriteActionSchedule *>::const_iterator &ci, bool &instantHasNext, bool &sequence){
//    if(instantHasNext && (*ci)->isRepeatDone()){
//        if(!(*ci)->getList().front()->isProtected){
//            delete (*ci)->getList().front();
//        }
//        (*ci)->getList().pop_front();
//    }
//    
//    double elapsedTime = Timer::getInstance().getElapsedTime();
//    
//    // update action with elapsed time and get unused time
//    double unusedTime = actionPtr->setCurrentTime(elapsedTime);
//    
//    //if unused time is able to use
//    if((*ci)->readyToUseUnusedTime){
//        //update with unusedTime.
//        actionPtr->update(elapsedTime, (*ci)->sharedUnusedTime);
//        (*ci)->readyToUseUnusedTime = false;
//        (*ci)->sharedUnusedTime = 0;
//    }
//    else{
//        actionPtr->update(elapsedTime, 0);
//        if(unusedTime > 0){
//            (*ci)->readyToUseUnusedTime = true;
//            (*ci)->sharedUnusedTime = unusedTime;
//        }
//    }
//    
//    //if current action is dead, we consider this as one iteration of sequence
//    if(!actionPtr->isAlive()){
//        (*ci)->countIterate();
//    }
//    
//    //since this is a sequence, break the for loop
//    sequence = false;
//}

//void SpriteObject::updateFromSpriteAction(){
//    //update from all actions
//    if(spriteActionScheduleList.empty())
//        return;
//    
//    bool scheduleEmpty = false;
//    //iterate through schedule
//    for(std::list<SpriteActionSchedule*>::const_iterator ci = spriteActionScheduleList.begin(); ci != spriteActionScheduleList.end(); ++ci){
//        scheduleEmpty = false;
//        //if scheduel is empty (which is not normal), just continue;
//        if((*ci)->getList().empty()){
//            scheduleEmpty = true;
//            continue;
//        }
//        
//        std::list<ActionObject*>::const_iterator action_ci;
//        
//        bool allActionDead = true;
//        for(action_ci = (*ci)->getList().begin(); action_ci != (*ci)->getList().end(); ++action_ci){
//            if ((*action_ci)->isAlive() || (*action_ci)->isRunning()) {
//                if(!(*action_ci)->isAlive()){
//                    (*action_ci)->running = false;
//                }
//                allActionDead = false;
//                break;
//            }
//        }
//        
//        //if there is at least one running(even if its dead) action
//        if(!allActionDead){
//            if(!(*action_ci)->isAlive() && (*ci)->isRepeatDone()){
//                if(!(*ci)->getList().front()->isProtected){
//                    cout << "sprite#" << spriteID << " deleting action#" << (*ci)->getList().front()->getActionID() << std::endl;
//                    delete(*ci)->getList().front();
//                }
//                cout << "sprite#" << spriteID << " popping action#" << (*ci)->getList().front()->getActionID() << std::endl;
//                (*ci)->getList().pop_front();
//                if((*ci)->getList().empty()){
//                    scheduleEmpty = true;
//                }
//            }
//            
//        }
//        
//        //if iteration is done, all action is dead, but need to repeat,
//        if((*ci)->isIterateDone() && allActionDead && !(*ci)->isRepeatDone()){
//            //revive all the actions
//            (*ci)->reviveAllActions();
//        }
//        
//    }
//    
//    if(scheduleEmpty){
//        delete spriteActionScheduleList.front();
//        spriteActionScheduleList.pop_front();
//        scheduleEmpty = false;
//    }
//}
