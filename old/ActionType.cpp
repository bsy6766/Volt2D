//
//  ActionType.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ActionType.h"

//default
const ActionType ActionType::ACTION_DEFAULT = ActionType("ACTION_DEFAULT");
//delay
const ActionType ActionType::ACTION_DELAY = ActionType("ACTION_DELAY");
//move
const ActionType ActionType::ACTION_MOVE_TO = ActionType("ACTION_MOVE_TO");
const ActionType ActionType::ACTION_MOVE_BY = ActionType("ACTION_MOVE_BY");
//rotate
const ActionType ActionType::ACTION_ROTATE_TO = ActionType("ACTION_ROTATE_TO");
const ActionType ActionType::ACTION_ROTATE_BY = ActionType("ACTION_ROTATE_BY");
//scale
const ActionType ActionType::ACTION_SCALE_TO = ActionType("ACTION_SCALE_TO");
const ActionType ActionType::ACTION_SCALE_BY = ActionType("ACTION_SCALE_BY");
//jump
const ActionType ActionType::ACTION_JUMP_TO = ActionType("ACTION_JUMP_TO");
const ActionType ActionType::ACTION_JUMP_BY = ActionType("ACTION_JUMP_BY");
//fade
const ActionType ActionType::ACTION_FADE_TO = ActionType("ACTION_FADE_TO");
const ActionType ActionType::ACTION_FADE_BY = ActionType("ACTION_FADE_BY");
//blink
const ActionType ActionType::ACTION_BLINK = ActionType("ACTION_BLINK");

ActionType::ActionType(std::string strName){
    this->name = strName;
}

std::string ActionType::toString() const{
    return this->name;
}