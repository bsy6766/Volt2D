//
//  ActionScaleBy.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/19/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ActionScaleBy__
#define __OpenGL_2D_Framework__ActionScaleBy__

#include "ActionObject.h"
#include "CommonInclude.h"

class ActionScaleBy : public ActionObject{
private:
    glm::vec3 totalScalingAmount;
    glm::vec3 prevScale;
    glm::vec3 scaled;
    
public:
    ActionScaleBy();
    ActionScaleBy(const ActionScaleBy& other);
    ~ActionScaleBy();
    
    //scale 0.0 ~ 1.0
    void initScaleBy(glm::vec3 scale, double duration);
    
    glm::vec3 getScaledScale();
    
    //virtuals
    virtual void updateAction(double& remainedTime);
    virtual void instantUpdate();
    virtual void intervalUpdate(double& remainedTime);
    virtual void revive();
};

#endif /* defined(__OpenGL_2D_Framework__ActionScaleBy__) */
