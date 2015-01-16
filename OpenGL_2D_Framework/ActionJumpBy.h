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
    void clone(SpriteAction* dataPtr);
    ~ActionJumpBy();
    void initJumpBy(glm::vec2 distance, double duration);
    
    void setJumpingPosition(glm::vec2 jumpingPosition, bool fresh);
    glm::vec2& getDistance();
    glm::vec2& getMovedDistance();
    
    void update(double elapsedTime, double unusedTime);
};

#endif /* defined(__CS364FinalProject__ActionJumpBy__) */
