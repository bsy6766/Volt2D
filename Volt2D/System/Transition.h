//
//  Transition.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/27/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Transition__
#define __OpenGL_2D_Framework__Transition__

class Transition{
protected:
    Transition();
private:
    double duration;
public:
    virtual ~Transition();
};

#endif /* defined(__OpenGL_2D_Framework__Transition__) */
