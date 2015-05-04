//
//  BoundingBox.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "BoundingBox.h"

BoundingBox::BoundingBox():
x(0),
y(0),
w(0),
h(0)
{
    
}

BoundingBox::BoundingBox(int x, int y, int w, int h):
x(x),
y(y),
w(w),
h(h)
{
    
}

BoundingBox::~BoundingBox(){
    
}