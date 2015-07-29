//
//  PS3ControllerWrapper.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__PS3ControllerWrapper__
#define __OpenGL_2D_Framework__PS3ControllerWrapper__

namespace Volt2D{
/// @{
/// @name Button constants
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
/// @}

/**
 *  @class PS3ControllerWrapper
 *  @brief Simple PS3 dualshock3 controller input wrapper
 */

class PS3ControllerWrapper{
private:
    /**
     *  GLFW assigned joystick number. Max 16.
     */
    unsigned int joystickInputNum;
    
    /**
     *  Number of buttons available with controleller
     */
    int buttonCount;
    
    /**
     *  Buttons buffer for all available buttons.
     *  GLFW_PRESS if pressed, else GLFW_RELEASE
     *  GLFW releases buffer.
     */
    const unsigned char* buttons;
    
    /**
     *  Number of axis avaialale with controller
     */
    int axisCount;
    
    /**
     *  Axises buffer for all available axises.
     *  Value range: -1 ~ 1
     *  GLFW releases buffer
     */
    const float* axises;
    
public:
    /**
     *  Contructor
     *  @param num A joystick number assigned by GLFW
     *  @param buttonCount A total number of buttons available with this controller
     *  @param axisCount A total number of axises available with this controller
     */
    PS3ControllerWrapper(int num, int buttonCount, int axisCount);
    ~PS3ControllerWrapper(){};
    
    /**
     *  Get key status for specific button.
     *  @return True if pressed. False if released
     */
    bool getKeyStatus(unsigned int key);
    
    /**
     *  Receive button input buffer from Director.
     *  @param buttonInputs List of input for all buttons
     */
    void receiveButtonInput(const unsigned char* buttonInputs);
    
    /**
     *  Receive axis input buffer from Director.
     *  @param axisInputs List of input for all axises
     */
    void receiveAxisInput(const float* axisInputs);
    
    /**
     *  Get axis status for specific axis.
     *  @return -1 = Left/Up, 1 = Right/Down
     */
    float getAxisValue(unsigned int axis);
};
}

#endif /* defined(__OpenGL_2D_Framework__PS3ControllerWrapper__) */
