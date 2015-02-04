//
//  GameManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__GameManager__
#define __OpenGL_2D_Framework__GameManager__

//opengl
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//c++
#include <iostream>
#include <stdexcept>
#include <string>

//system
#include "Shader.h"
#include "Program.h"
#include "Camera.h"
#include "Timer.h"
#include "Director.h"

//sprite
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "SpriteManager.h"

//actions
#include "ActionMoveTo.h"
#include "ActionJumpBy.h"
#include "ActionFadeTo.h"
#include "ActionDelay.h"
#include "ActionRotateBy.h"
#include "SpriteActionSchedule.h"

//particle
#include "ParticleSystem.h"
#include "ParticleSystemManager.h"

class GameManager{
private:
    bool running;
    bool printFPS;
    
    glm::vec2 prevMousePos;
    bool leftClicked;
    
    GLFWwindow *window;
    WinSize windowSize;
    
    /*---------------Loading screen sprites--------------*/
    Sprite *loadingBG;
    Sprite *loadingText;
    Sprite *loadingIcon;
    /*---------------Loading screen sprites--------------*/
    
    /*-----------------Main screen sprites---------------*/
    Sprite *dayBackground;
    Sprite *nightBackground;
    
    Sprite *star1;
    Sprite *star2;
    
    Sprite *buildingSilhouette1_1;
    Sprite *buildingSilhouette1_2;
    
    Sprite *buildingSilhouette2_1;
    Sprite *buildingSilhouette2_2;
    
    Sprite *buildingSilhouette3_1;
    
    Sprite *ground_1;
    Sprite *ground_2;
    
    SpriteAnimation *character;
    /*-----------------Main screen sprites---------------*/
    
    /*--------------------Sprite manager-----------------*/
    SpriteManager *loadingSpriteManager;
    SpriteManager *spriteManager;
    /*---------------------------------------------------*/
    
    ActionJumpBy *jumpAction;
    
    /*----------------------Particles--------------------*/
    ParticleSystem *testParticle;
    ParticleSystemManager *particleSystemManager;
    /*---------------------------------------------------*/
    
    
    //Shader
    Shader *vertexShader;
    Shader *fragmentShader;
    //Program
    Program *program;
    //Camera
    Camera *camera;
    
    //bool flags
    bool spaceKeyLock;
    bool loading;
    bool loadingFading;
    
    //redner sprites
    void render();
    //get input
    void input();
    
    //z depth value for loading loop
    enum z_value_loading{
        z_loading_BG = 0,
        z_loading_hud
    };
    
    //z depth value for main loop sprites
    enum z_value_mainloop{
        z_nightBackground = 0,
        z_stars,
        z_dayBackground,
        z_silhouette3,
        z_silhouette2,
        z_silhouette1,
        z_ground,
        z_character
    };
    
public:
    GameManager();
    ~GameManager();
    void startGame();
    void terminateGame();
    
    /**
     * init OpenGL attributes
     * all enable and settings goes here
     */
    void initOpenGL();
    
    /**
     * init GLEW
     * init with OpenGL version 4.3
     */
    void initGLEW();
    
    /**
     * init GLFW
     * just init...
     */
    void initGLFW();
    
    /**
     * create and initialize GLFW window
     */
    void createWindow(int _screenWidth, int _screenHeight, std::string &title);
    
    void initEssentials();
    
    void initSpriteManager();
    void releaseSpriteManager();
    
    void initLoading();
    void releaseLoading();
    
    void initSprites();
    
    void initSpriteActions();
    void releaseUndeadActions();
    
    void initCharacter();
    void releaseCharacter();
    
    void initActionScheduler();
    void releaseActionScheduler();
    
    void initParticleSystemManager();
    void releaseParticleSystemManager();
    
    void initParticleSystem();
    
    void initKeyLock();
    
    void finishLoading();
    
    /**
     * load Shader
     * resource path -> file Path -> code
     */
    void loadShader(const std::string& filePath, GLenum shaderType);
    
    void releaseShader();
    
    void loadProgram();
    
    void releaseProgram();
    
    void loadCamera();
    
    void releaseCamera();
};

#endif /* defined(__OpenGL_2D_Framework__GameManager__) */
