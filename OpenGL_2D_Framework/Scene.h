//
//  Scene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Scene__
#define __OpenGL_2D_Framework__Scene__

/*
	Scene class
	Singletone
	The purpose of this class is to make Root Scene node.
	Treating the entire program as a scene, the scene director will have data related to window
	such as window size, title, or glenable stuffs. 
	Currently, it doesn't do much, but it will be very handy later.
*/

struct winSize{
    float w;
    float h;
};

const int SCREEN_TO_WORLD_SCALE = 10;
const float static GLOBAL_Z_VALUE = 0;

//Singleton Scene
class Scene{
private:
    static Scene instance;
    winSize WinSize;
    Scene(){
        WinSize = {0, 0};
    }
    
    //copy constructor not defined. Prevents copying instance
    Scene(Scene const&);
    //assign operator constructor not defined. Prevenets copying instance
    void operator=(Scene const&);
    
public:
    //return static Scene instance
    static Scene& getInstance(){
        return instance;
    }
    
    winSize getWindowSize();
    void setWindowSize(int screenWidth, int screenHeight);
};

#endif /* defined(__OpenGL_2D_Framework__Scene__) */
