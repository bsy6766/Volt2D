//
//  ActionMoveBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionMoveBy__
#define __OpenGL_2D_Framework__ActionMoveBy__

#include "SpriteObject.h"
#include "ActionObject.h"

class ActionMoveBy : public ActionObject{
protected:
private:
    glm::vec3 distance;
    glm::vec3 movedDistance;
    glm::vec3 previousDistance;
    
    void instantUpdate();
    void intervalUpdate(double& remainedTime);
    
public:
    ActionMoveBy();
    ActionMoveBy(const ActionMoveBy& other);
    ~ActionMoveBy();
    
    void initMoveBy(glm::vec3 distance, double duration);
    
    //virtuals
    virtual void updateAction(double& remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionMoveBy__) */
