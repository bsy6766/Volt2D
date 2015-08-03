//
//  main.cpp
//  Volt2D
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
        Volt2D::Director::getInstance().setWorkingDir(wd);
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
    

    Volt2D::LuaConfig* systemConfig = Volt2D::LuaConfig::create("systemConfig");
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
    bool fullscreen = systemConfig->getBoolean("system", "window.fullscreen");
    bool windowed = systemConfig->getBoolean("system", "window.borderless");
    bool captureMouse = systemConfig->getBoolean("system", "window.captureMouse");
    bool cursorHidden = systemConfig->getBoolean("system", "window.cursorHidden");
    
    delete systemConfig;
    
    try{
        cout << "[main] Starting application." << endl;
        Volt2D::Director::getInstance().initApp(screenWidth,
                                        screenHeight,
                                        windowTitle,
                                        clearBufferColor,
                                        vsync,
                                        fullscreen,
                                        windowed,
                                        captureMouse,
                                        cursorHidden);
        TitleScene* titleScene = new TitleScene();
        Volt2D::Director::getInstance().replaceScene(titleScene);
        Volt2D::Director::getInstance().run();
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    
    cout << "[main] Application terminated." << endl;
    return 0;
}
