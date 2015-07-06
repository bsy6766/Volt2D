//
//  ActionScaleTo.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 6/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionScaleTo__
#define __OpenGL_2D_Framework__ActionScaleTo__

#include "SpriteObject.h"
#include "ActionObject.h"

class ActionScaleTo : public ActionObject{
private:
    glm::vec3 destScale;
    glm::vec3 srcScale;
    glm::vec3 scaled;
    glm::vec3 totalScalingAmount;
public:
    ActionScaleTo();
    ActionScaleTo(const ActionScaleTo& other);
    ~ActionScaleTo();
    
    void initScaleTo(glm::vec3 scale, double duration);
    
    //get & set
//    glm::vec3 getScaledScale();
//    void setCurrentScale(glm::vec3 scale);
    
    //virtuals
    virtual void startAction();
    virtual void updateAction(double& remainedTime);
    virtual void instantUpdate();
    virtual void intervalUpdate(double& remainedTime);
    virtual void revive();
    
};

#endif /* defined(__OpenGL_2D_Framework__ActionScaleTo__) */
