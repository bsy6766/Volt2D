//
//  main.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/15/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include <iostream>
#include <string>
#include "Director.h"
#include "TitleScene.h"

#include "SpriteSheet.h"

int main(int argc, const char * argv[]) {
    
    char cCurrentPath[FILENAME_MAX];
    
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return errno;
    }
    
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    
    //    printf ("The current working directory is %s\n", cCurrentPath);
    std::string runningPath(cCurrentPath);
    std::cout << "The current working directory is " << runningPath << std::endl;
    
    std::string windowTitle = "opengl 2d framework";
    
    SpriteSheet* ss = new SpriteSheet();
    ss->initSpriteSheetWithXML("battle scene.xml");
    delete ss;
    
    Director::getInstance().setWindowSize(1280, 720);
    
    try{
        Director::getInstance().initApp(1280, 720, "JB_Engine(OpenGL4) test game build");
        TitleScene* titleScene = new TitleScene();
        Director::getInstance().pushScene(titleScene);
        Director::getInstance().run();

    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
