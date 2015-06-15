//
//  ActionMoveBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/15/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionMoveBy__
#define __OpenGL_2D_Framework__ActionMoveBy__

#include "ActionObject.h"

class ActionMoveBy : public ActionObject{
protected:
private:
    glm::vec3 distance;
    glm::vec3 movedDistance;
    glm::vec3 previousDistance;    
    
public:
    ActionMoveBy();
    ActionMoveBy(const ActionMoveBy& other);
    ~ActionMoveBy();
    
    void initMoveBy(glm::vec3 distance, double duration);
    
    //set & get
    glm::vec3 getMovedDistance();
    
    //virtuals
    virtual void updateAction(double remainedTime);
    virtual void instantUpdate();
    virtual void intervalUpdate(double remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionMoveBy__) */
