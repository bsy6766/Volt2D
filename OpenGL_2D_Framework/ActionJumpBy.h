//
//  ActionJumpBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/6/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionJumpBy__
#define __OpenGL_2D_Framework__ActionJumpBy__

#include "ActionObject.h"

class ActionJumpBy: public ActionObject{
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
    virtual void instantUpdate();
    virtual void update(double elapsedTime, double unusedTime);
    virtual void clone(ActionObject* dataPtr);
};

#endif /* defined(__OpenGL_2D_Framework__ActionJumpBy__) */
