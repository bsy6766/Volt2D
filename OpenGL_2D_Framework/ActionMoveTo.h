//
//  ActionMoveTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/5/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionMoveTo__
#define __OpenGL_2D_Framework__ActionMoveTo__

#include "ActionObject.h"

class ActionMoveTo :  public ActionObject{
private:
    glm::vec3 destination;
    glm::vec3 originalPosition;
    glm::vec3 movedPosition;
    glm::vec3 totalDistance;
    
public:
    ActionMoveTo();
    ActionMoveTo(const ActionMoveTo& other);
    ~ActionMoveTo();
    
    void initMoveTo(glm::vec3 destination, double duration);
    
    //set & get
    void setCurrentPos(glm::vec3 pos);
    glm::vec3 getMovedPosition();
    
    //virtuals
    virtual void updateAction(double& remainedTime);
    virtual void instantUpdate();
    virtual void intervalUpdate(double& remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionMoveTo__) */
