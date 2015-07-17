//
//  ActionType.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionType__
#define __OpenGL_2D_Framework__ActionType__

#include <string>

class ActionType{
public:
    //default
    static const ActionType ACTION_DEFAULT;
    //delay
    static const ActionType ACTION_DELAY;
    //move
    static const ActionType ACTION_MOVE_TO;
    static const ActionType ACTION_MOVE_BY;
    //rotate
    static const ActionType ACTION_ROTATE_TO;
    static const ActionType ACTION_ROTATE_BY;
    //scale
    static const ActionType ACTION_SCALE_TO;
    static const ActionType ACTION_SCALE_BY;
    //jump
    static const ActionType ACTION_JUMP_TO;
    static const ActionType ACTION_JUMP_BY;
    //fade
    static const ActionType ACTION_FADE_TO;
    static const ActionType ACTION_FADE_BY;
    //blink
    static const ActionType ACTION_BLINK;
    
private:
    ActionType(std::string strName);
    
    std::string name;
    
public:
    std::string toString() const;
};

bool operator==(const ActionType& left, const ActionType& right){
    return (left == right);
}

#endif /* defined(__OpenGL_2D_Framework__ActionType__) */
