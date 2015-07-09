//
//  Z_Float.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/9/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Z_Float__
#define __OpenGL_2D_Framework__Z_Float__

class Z_Float{
public:
    Z_Float();
    
    float z;
    bool dirty = false;
    
    void setZ(float z);
    bool getZ(float& z);
    bool isValid();
};

#endif /* defined(__OpenGL_2D_Framework__Z_Float__) */
