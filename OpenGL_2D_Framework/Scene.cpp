//
//  Scene.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Scene.h"

Scene Scene::instance;

winSize Scene::getWindowSize(){
    return WinSize;
}

void Scene::setWindowSize(int screenWidth, int screenHeight){
    WinSize = {(float)screenWidth, (float)screenHeight};
}