//
//  main.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/15/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#elif __APPLE__
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include "Director.h"
#include "TitleScene.h"

//#include "SpriteSheet.h"

void splitFilename (string& str)
{
    size_t found;
    cout << "Splitting: " << str << endl;
    found=str.find_last_of("/\\");
    cout << " folder: " << str.substr(0,found) << endl;
    cout << " file: " << str.substr(found+1) << endl;
    str = str.substr(0, found);
}

int main(int argc, const char * argv[]) {
    
    cout << "argc = " << argc << endl;
    cout << "argv[0] = " << argv[0] << endl;
    
    if(argc > 0){
        std::string wd(argv[0]);
        splitFilename(wd);
        
#if DEBUG
#else
        Director::getInstance().setWorkingDir(wd);
#endif

        cout << "wd = " << wd << endl;
    }
    
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
    
//    int result = chdir(runningPath.c_str());
    
//    SpriteSheet* ss = new SpriteSheet();
//    ss->initSpriteSheetWithXML("battle scene.xml");
//    delete ss;
    
    Director::getInstance().setWindowSize(1440, 900);
    try{
        Director::getInstance().initApp(1440, 900, "JB_Engine(OpenGL4) test game build");
        TitleScene* titleScene = new TitleScene();
        Director::getInstance().pushScene(titleScene);
        Director::getInstance().run();

    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
