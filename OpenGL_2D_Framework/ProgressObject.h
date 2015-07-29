//
//  ProgressObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/21/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressObject__
#define __OpenGL_2D_Framework__ProgressObject__

#include "Texture.h"
#include "RenderableObject.h"
#include "ProgressFromTo.h"

#define VOID_OFFSET(i) (GLvoid*)(i)

namespace Volt2D{
/**
 *  @class ProgressObject
 *  @brief Base class for ProgressBar and ProgressRadian
 *  \todo Make ProgressBar and ProgressRadian reverisble
 */
class ProgressObject : public RenderableObject{
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
    int w;
    
    /**
     *  texture height
     */
    int h;
    
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

#endif /* defined(__OpenGL_2D_Framework__ProgressObject__) */
