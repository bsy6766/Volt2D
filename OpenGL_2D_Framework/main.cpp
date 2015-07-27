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


//test
#include "LuaConfig.h"

void splitFilename (std::string& str)
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
//        Director::getInstance().setWorkingDir(wd);
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
    

    LuaConfig* systemConfig = LuaConfig::create("systemConfig");
#if _WIN32
	systemConfig->loadConfig("system", runningPath + "/../config_win32.lua");
#elif __APPLE__
	systemConfig->loadConfig("system", runningPath + "/../System/config_osx.lua");
#endif
    int screenWidth = systemConfig->getFloat("system", "window.size.screenWidth");
    int screenHeight = systemConfig->getFloat("system", "window.size.screenHeight");
    std::string windowTitle = systemConfig->getString("system", "window.title");
    glm::vec3 clearBufferColor = glm::vec3(systemConfig->getFloat("system", "clearBuffer.r"),
                                           systemConfig->getFloat("system", "clearBuffer.g"),
                                           systemConfig->getFloat("system", "clearBuffer.b"));
//    systemConfig->loadConfig("level1", runningPath + "/../config.lua");
//    systemConfig->loadConfig("level2", runningPath + "/../config.lua");
//    cout << "w = " << systemConfig->getFloat("system", "window.size.screenWidth") << endl;
//    cout << "h = " << systemConfig->getFloat("system", "window.size.screenHeight") << endl;
//    cout << "title = " << systemConfig->getString("system", "window.title") << endl;
//    cout << "fullscreen = " << systemConfig->getBoolean("system", "window.fullsize") << endl;
//    cout << "windowed = " << systemConfig->getBoolean("system", "window.windowed") << endl;
//    cout << "borderless = " << systemConfig->getBoolean("system", "window.borderless") << endl;
//    cout << "Level1 name = " << systemConfig->getString("level1", "name") << endl;
//    cout << "level2 = " << systemConfig->getString("level2", "");
    delete systemConfig;
    
    

//    Director::getInstance().setWindowSize(1440, 900);
    try{
        Director::getInstance().initApp(screenWidth, screenHeight, windowTitle, clearBufferColor);
        TitleScene* titleScene = new TitleScene();
        Director::getInstance().pushScene(titleScene);
        Director::getInstance().run();

    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
