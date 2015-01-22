//
//  ActionJumpBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/6/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__ActionJumpBy__
#define __CS364FinalProject__ActionJumpBy__

#include "SpriteAction.h"

class ActionJumpBy: public SpriteAction{
private:
    glm::vec2 distance;
    glm::vec2 jumpingPosition;
    glm::vec2 previousPosition;
    glm::vec2 movedDistance;
    
public:
    ActionJumpBy();
    ~ActionJumpBy();
    
    void initJumpBy(glm::vec2 distance, double duration);
    
    //set & get
    void setJumpingPosition(glm::vec2 jumpingPosition, bool fresh);
    glm::vec2& getDistance();
    glm::vec2& getMovedDistance();
    
    //virtual
    void update(double elapsedTime, double unusedTime);
    void clone(SpriteAction* dataPtr);
};

#endif /* defined(__CS364FinalProject__ActionJumpBy__) */
