//
//  main.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/15/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include <iostream>
#include <string>
//#include "GameManager.h"
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
    
    //char buffer[1024];
    //char *answer = getcwd(buffer, sizeof(buffer));
    //string s_cwd;
    //if (answer)
    //{
    //    s_cwd = answer;
    //}
    //
    //std::cout << "The current working directory is " << s_cwd << std::endl;
    
    
    std::string windowTitle = "opengl 2d framework";
    
    SpriteSheet* ss = new SpriteSheet();
    ss->initSpriteSheetWithXML("battle scene.xml");
    delete ss;
    
    
//    GameManager* gm = new GameManager();
    Director::getInstance().setWindowSize(1280, 720);
    
    try{
        Director::getInstance().initApp(1280, 720, "microRaid dev");
        TitleScene* titleScene = new TitleScene();
        Director::getInstance().pushScene(titleScene);
        Director::getInstance().run();
//        gm->initEssentials();
//        
//        //init the game
//        gm->initGLFW();
//        gm->createWindow(1280, 720, windowTitle);
//        
//        
//        gm->initGLEW();
//        gm->initOpenGL();
//        
//        //load shaders
//        gm->loadShader("../Shader/vertexShader.glsl", GL_VERTEX_SHADER);
//        gm->loadShader("../Shader/fragmentShader.glsl", GL_FRAGMENT_SHADER);
//        
//        //create program
//        gm->loadProgram();
//        
//        gm->loadCamera();
//        
//        gm->initSpriteManager();
//        
//        gm->initParticleSystemManager();
//        
//        gm->initParticleSystem();
//        
//        gm->initLoading();
//        
//        gm->startGame();
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    
    //exit app
//    Director::getInstance().terminateApp();
//    gm->releaseProgram();
//    gm->releaseShader();
//    gm->releaseUndeadActions();
//    gm->releaseSpriteManager();
//    gm->releaseParticleSystemManager();
//    gm->releaseCamera();
//    
//    delete gm;
    
    return 0;
}
