//
//  Z_Float.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/9/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Z_Float.h"

Z_Float::Z_Float():
z(0),
dirty(false)
{
    
}

void Z_Float::setZ(float z){
    this->z = z;
    this->dirty = true;
}

bool Z_Float::getZ(float& z){
    if(dirty){
        z = this->z;
        return true;
    }
    else{
        return false;
    }
}

bool Z_Float::isValid(){
    return this->dirty;
}