//
//  PS3ControllerWrapper.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__PS3ControllerWrapper__
#define __OpenGL_2D_Framework__PS3ControllerWrapper__

#define RELEASED 0
#define PRESSED 1

const unsigned int SELECT = 0;
const unsigned int L3 = 1;
const unsigned int R3 = 2;
const unsigned int START = 3;
const unsigned int DPAD_UP = 4;
const unsigned int DPAD_RIGHT = 5;
const unsigned int DPAD_DOWN = 6;
const unsigned int DPAD_LEFT = 7;
const unsigned int L2 = 8;
const unsigned int R2 = 9;
const unsigned int L1 = 10;
const unsigned int R1 = 11;
const unsigned int TRIANGLE = 12;
const unsigned int CIRCLE = 13;
const unsigned int CROSS = 14;
const unsigned int SQUARE = 15;
const unsigned int HOME = 16;

const unsigned int LEFT_HORIZONTAL = 0;
const unsigned int LEFT_VERTICAL = 1;
const unsigned int RIGHT_HORIZONTAL = 2;
const unsigned int RIGHT_VERTICAL = 3;


class PS3ControllerWrapper{
private:
    unsigned int joystickInputNum;
    int buttonCount;                //ps3
    const unsigned char* buttons;   //GLFW releases for us.
    int axisCount;
    const float* axises;
    
public:
    //nothing initialize. It's just wrapper.
    PS3ControllerWrapper(int num, int buttonCount, int axisCount);
    ~PS3ControllerWrapper(){};
    
    bool getKeyStatus(unsigned int key);
    void receiveButtonInput(const unsigned char* buttonInputs);
    void receiveAxisInput(const float* axisInputs);
    float getAxisValue(unsigned int axis);
};

#endif /* defined(__OpenGL_2D_Framework__PS3ControllerWrapper__) */
