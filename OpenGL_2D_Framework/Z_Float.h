//
//  Z_Float.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/9/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Z_Float__
#define __OpenGL_2D_Framework__Z_Float__

namespace Volt2D{
/**
 *  C++ float wrapper like Java's Float
 */
class Z_Float{
private:
    /**
     *  z value. 0 by default
     */
    float z;
public:
    //Default constructor
    Z_Float();
    
    /**
     *  Dirty flag. 
     *  True if z is ever set. Else, false.
     */
    bool dirty;
    
    /**
     *  Set z. 
     */
    void setZ(float z);
    
    /**
     *
     *  @param z A float reference to get z.
     *  @return true if z was ever set. Else, false.
     */
    bool getZ(float& z);
    
    /**
     *  Check if z is valid and set by user.
     */
    bool isValid();
};
}   //namespace end

#endif /* defined(__OpenGL_2D_Framework__Z_Float__) */
