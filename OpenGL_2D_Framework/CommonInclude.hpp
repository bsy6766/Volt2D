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

using glm::vec4;
using glm::vec3;
using glm::vec2;
using glm::mat4;

namespace Utility{
    /**
     * Computes random number between the range.
     * This function handles all type of number
     */
    template<typename Type>
    inline Type randRange(Type min, Type max){
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
    
    /**
     *  Wrap angle with boundary between 0 and 360 degrees.
     *  @param degree A float reference of angle in degree to wrap
     */
    inline void wrapAngle(float& degree){
        if(degree >= 360){
            while(degree >= 360){
                degree -= 360.0;
            }
        }
        else if(degree < 0){
            while(degree < 0){
                degree += 360;
            }
        }
    }
    
    /**
     *  Wrap color value with boundary between 0 and 255
     *  @param value A float reference of color value to wrap
     */
    inline void wrapColor(float& value){
        if(value > 255.0f){
//            while(value > 255.0f){
//                value -= 255.0f;
//            }
            value = 255.0f;
        }
        else if(value < 0){
//            while(value < 0){
//                value += 255.0f;
//            }
            value = 0;
        }
    }
    
    /**
     *  Print glm::vec2
     */
    inline void printVec2(vec2 point){
        cout << "vec2 = (" << point.x << ", " << point.y << ")" << endl;
    }
    
    /**
     *  Print glm::vec3
     */
    inline void printVec3(vec3 point){
        cout << "vec3 = (" << point.x << ", " << point.y <<  ", " << point.z << ")" << endl;
    }
    
    /**
     *  Print glm::vec4
     */
    inline void printVec4(vec4 point){
        cout << "vec3 = (" << point.r << ", " << point.g <<  ", " << point.b << ", " << point.a << ")" << endl;
    }
}


#endif /* defined(__OpenGL_2D_Framework__CommonInclude__) */