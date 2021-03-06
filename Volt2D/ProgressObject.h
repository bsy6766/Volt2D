//
//  ProgressObject.h
//  Volt2D
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__ProgressObject__
#define __Volt2D__ProgressObject__

#include "Texture.h"
#include "RenderableObject.h"
#include "ProgressFromTo.h"
#include "SpriteSheet.h"

#define VOID_OFFSET(i) (GLvoid*)(i)

namespace Volt2D{
/**
 *  @class ProgressObject
 *  @brief Base class for ProgressBar and ProgressRadian
 *  \todo Make ProgressBar and ProgressRadian reverisble
 */
class ProgressObject : public Volt2D::RenderableObject{
protected:
    //protected constructor
    ProgressObject();
    
    /**
     *  Progress texture.
     */
    Texture* texture;
    
    /**
     *  texture width
     */
    int textureWidth;
    
    /**
     *  texture height
     */
    int textureHeight;
    
    /**
     *  total percentage
     */
    int totalPercentage;
    
    /**
     *  A rate of percentage for single increment or decrement
     */
    int percentageRate;
    
    /**
     *  Total steps ProgressObject has (totalPercentage / percentageRate)
     */
    int totalSteps;
    
    /**
     *  Current percentage of progress
     */
    int currentPercentage;
private:
public:
    //virtual destructor
    virtual ~ProgressObject();
    
    /**
     *  Set object's percentage
     *  @param percentage A percentage to set
     */
    void setPercentage(int percentage);
    
    /**
     *  Add percentage to object's current percentage
     *  @param percentage A percentage to add
     */
    void addPercentage(int percentage);
    
    /**
     *  Get current percentage
     *  @return Object's current percentage
     */
    int getPercentage();
    
//    virtual void addActions(std::initializer_list<ActionObject*> actions, int repeat);
};
}   //namespace end

#endif /* defined(__Volt2D__ProgressObject__) */
