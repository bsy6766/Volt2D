//
//  PS3ControllerWrapper.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "PS3ControllerWrapper.h"

PS3ControllerWrapper::PS3ControllerWrapper(int num, int buttonCount, int axisCount):
joystickInputNum(num),
buttonCount(buttonCount),
axisCount(axisCount)
{
    
}

bool PS3ControllerWrapper::getKeyStatus(unsigned int key){
    return buttons[key];
}

void PS3ControllerWrapper::receiveButtonInput(const unsigned char *buttonInputs){
    this->buttons = buttonInputs;
}

void PS3ControllerWrapper::receiveAxisInput(const float *axisInputs){
    this->axises = axisInputs;
}

float PS3ControllerWrapper::getAxisValue(unsigned int axis){
    return this->axises[axis];
}