//
//  Utility.h
//  Volt2D
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Utility__
#define __Volt2D__Utility__

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <math.h>
#endif

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

namespace Volt2D{
    /**
     *  Axises
     */
    static const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
    static const glm::vec3 X_NAXIS = glm::vec3(-1, 0, 0);
    static const glm::vec3 Y_AXIS = glm::vec3(0, 1, 0);
    static const glm::vec3 Y_NAXIS = glm::vec3(0, -1, 0);
    static const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);
    static const glm::vec3 Z_NAXIS = glm::vec3(0, 0, -1);
    
    /**
     *  Radian to degree
     */
    inline float radianToDegree(float radian){
        return (radian * 180.0f) / M_PI;
    }
    
    /**
     *  Degree to radian
     */
    inline float degreeToRadian(float degree){
        return (degree * M_PI) / 180.0f;
    }
    
    /**
     * Computes random number between the range.
     * This function handles all type of number
     */
    template<typename Type>
    inline Type randRange(Type min, Type max){
        Type randVal = (Type)rand() / (Type)RAND_MAX;
        return min + randVal * (max - min);
    }
    
    /**
     *  Random float betwen -1.0 and 1.0f
     */
    inline float randf(){
        return  ((std::rand() / (float)RAND_MAX) * 2) - 1;
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
     *  Check if number is power of two.
     *  @param num Number to check if it's power of two. Must be greater than 1.
     */
    inline bool isPowerOfTwo(unsigned int num){
        return !(num == 0) && !(num & (num - 1));
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
            value = 255.0f;
        }
        else if(value < 0){
            value = 0;
        }
    }
    
    /**
     *  Print glm::vec2
     */
    inline void printVec2(vec2 point, std::string prefix = ""){
        if(!prefix.empty())
            prefix += " ";
        cout << prefix << "vec2 = (" << point.x << ", " << point.y << ")" << endl;
    }
    
    /**
     *  Print glm::vec3
     */
    inline void printVec3(vec3 point, std::string prefix = ""){
        if(!prefix.empty())
            prefix += " ";
        cout << prefix << "vec3 = (" << point.x << ", " << point.y <<  ", " << point.z << ")" << endl;
    }
    
    /**
     *  Print glm::vec4
     */
    inline void printVec4(vec4 point, std::string prefix = ""){
        if(!prefix.empty())
            prefix += " ";
        cout << prefix << "vec4 = (" << point.r << ", " << point.g <<  ", " << point.b << ", " << point.a << ")" << endl;
    }
    
    /**
     *  Print glm::mat4
     */
    inline void printMat4(mat4 matrix, std::string prefix = ""){
        if(!prefix.empty())
            prefix += " ";
        cout << prefix << "mat4 = " << endl;
        cout << "[ " << matrix[0][0] << ", " << matrix[1][0] << ", " << matrix[2][0] << ", " << matrix[3][0] << " ]" << endl;
        cout << "[ " << matrix[0][1] << ", " << matrix[1][1] << ", " << matrix[2][1] << ", " << matrix[3][1] << " ]" << endl;
        cout << "[ " << matrix[0][2] << ", " << matrix[1][2] << ", " << matrix[2][2] << ", " << matrix[3][2] << " ]" << endl;
        cout << "[ " << matrix[0][3] << ", " << matrix[1][3] << ", " << matrix[2][3] << ", " << matrix[3][3] << " ]" << endl;
    }
    
    /**
     *  X coordinate to world coordinate
     */
    inline double screenToWorldCoordinateX(double screenX){
        
        return -1.0;
    }
    
    inline void splitFilename (std::string& str)
    {
        size_t found;
        found=str.find_last_of("/\\");
        str = str.substr(0, found);
    }
}

#endif /* defined(__Volt2D__Utility__) */