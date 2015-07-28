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
//    cout << "Splitting: " << str << endl;
    found=str.find_last_of("/\\");
//    cout << " folder: " << str.substr(0,found) << endl;
//    cout << " file: " << str.substr(found+1) << endl;
    str = str.substr(0, found);
}

int main(int argc, const char * argv[]) {
    //For compiling with terminal.
#if RELEASE
    if(argc > 0){
        std::string wd(argv[0]);
        splitFilename(wd);
        Director::getInstance().setWorkingDir(wd);
    }
#endif
    
    char cCurrentPath[FILENAME_MAX];
    
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return errno;
    }
    
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    
    std::string runningPath(cCurrentPath);
    std::cout << "[main] Working directory = " << runningPath << std::endl;
    

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
    bool vsync = systemConfig->getBoolean("system", "window.vsync");
    delete systemConfig;
    
    try{
        cout << "[main] Starting application." << endl;
        Director::getInstance().initApp(screenWidth, screenHeight, windowTitle, clearBufferColor, vsync);
        TitleScene* titleScene = new TitleScene();
        Director::getInstance().pushScene(titleScene);
        Director::getInstance().run();
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    
    cout << "[main] Application terminated." << endl;
    return 0;
}
