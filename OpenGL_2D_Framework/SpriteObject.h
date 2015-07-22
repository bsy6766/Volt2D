//
//  SpriteObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteObject__
#define __OpenGL_2D_Framework__SpriteObject__

#include "RenderableObject.h"

#include <vector>
#include <list>
#include "Timer.h"

/**
 *  @class SpriteObject
 *  @brief Base class between Sprite and Sprite animation
 *  @note This class is getting useless. 
 *  \todo Remove SpriteObject or find better way to find
 */
class SpriteObject : public RenderableObject{
private:
protected:
    int w;
    int h;

public:
    SpriteObject();
    virtual ~SpriteObject();
    
    enum SpriteType{
        NORMAL_TYPE = 0,
        BILLBOARD_TYPE
    };
    
    SpriteType type;
};

#endif /* defined(__OpenGL_2D_Framework__SpriteObject__) */
