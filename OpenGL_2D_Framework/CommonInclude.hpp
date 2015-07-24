//
//  CommonInclude.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__CommonInclude__
#define __OpenGL_2D_Framework__CommonInclude__

#include <iostream>
#include <assert.h>
#include <string>
#include <glm/glm.hpp>

using std::cout;
using std::endl;

using std::string;

using glm::vec3;
using glm::vec2;
using glm::mat4;

namespace Utility{
    /**
     * Computes random number between the range.
     * This function handles all type of number
     */
    template<typename Type>
    inline Type computeRandom(Type min, Type max){
        Type randVal = (Type)rand() / RAND_MAX;
        return min + randVal * (max - min);
    }
    
    /**
     *  Find nearest power of two from passed number.
     */
    inline int findNearestPowTwo(unsigned int num){
        num--;
        num |= num >> 1;
        num |= num >> 2;
        num |= num >> 4;
        num |= num >> 8;
        num |= num >> 16;
        num++;
        return num;
    }
}


#endif /* defined(__OpenGL_2D_Framework__CommonInclude__) */