//
//  Director.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Director.h"

Director::Director(){

}

Director::~Director(){
	while (!sceneQueue.empty()){
		delete sceneQueue.front();
		sceneQueue.pop();
	}

	assert(sceneQueue.empty());

}

winSize Director::getWindowSize(){
	return WinSize;
}

void Director::setWindowSize(int screenWidth, int screenHeight){
	WinSize = { (float)screenWidth, (float)screenHeight };
}

void Director::pushScene(Scene* pScene){
	sceneQueue.push(pScene);
}