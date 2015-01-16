//
//  Scene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__Scene__
#define __CS364FinalProject__Scene__

//This class contains screen info

struct winSize{
    float w;
    float h;
};

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

#endif /* defined(__CS364FinalProject__Scene__) */
