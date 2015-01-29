//
//  ActionMoveTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/5/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionMoveTo__
#define __OpenGL_2D_Framework__ActionMoveTo__

#include "SpriteAction.h"

class ActionMoveTo :  public SpriteAction{
private:
    glm::vec2 destination;
    glm::vec2 previousPosition;
    glm::vec2 originalPosition;
    glm::vec2 movedDistance;
    
public:
    ActionMoveTo();
    ActionMoveTo(const ActionMoveTo& other);
    ~ActionMoveTo();
    
    void initMoveTo(glm::vec2 destination, double duration);
    
    //set & get
    void setOriginalPosition(glm::vec2 pos, bool fresh);
    glm::vec2 getMovedDistance();
    
    //virtuals
    void clone(SpriteAction* dataPtr);
    void update(double elapsedTime, double unusedTime);
    
    //override
    void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionMoveTo__) */
