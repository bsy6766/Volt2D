//
//  Director.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Director__
#define __OpenGL_2D_Framework__Director__

//opengl
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "CommonInclude.h"

#include "Shader.h"
#include "Program.h"
#include "Camera.h"
#include "SoundManager.h"

#include <string>
#include <unordered_map>
#include "Timer.h"
#include "PS3ControllerWrapper.h"
#include "Sprite.h"
#include "SpriteSheet.h"

#define MAX_JOYSTICK 16

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#elif __APPLE__
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

const int SCREEN_TO_WORLD_SCALE = 10;
const float static GLOBAL_Z_VALUE = 0;

struct WinSize{
	float w;
	float h;
};

class Director{
private:
    friend class SpriteSheet;
    friend class Sprite;
    SpriteSheet* const getSpriteSheet(std::string frameName);
    void cacheSpriteSheet(std::string frameName, SpriteSheet* spriteSheet);
    void unCacheSpriteSheet(std::string frameName);
    bool debugMovement = false;
    
    //mouse icon
    Sprite* mouseCursor;
    
/// -------------------- OpenGL ---------------------
/// @{
/// @name OpenGL attributes

    /**
     *  Main camera. It's fixed at most of the time.
     */
    Camera* camera;
    
    /**
     *  Unordered map that stores Program object with string ID
     */
    std::unordered_map<std::string, Program*> programs;
    
/// @}
/// -------------------------------------------------

/// -------------------- System ---------------------
/// @{
/// @name OpenGL attributes
    
    //wd
    std::string workingDirectory;
    
    //GLFW window
    GLFWwindow* window;
    
    //SoundManager
    SoundManager* soundManager;
    
    //SpriteSheet
    std::unordered_map<std::string, SpriteSheet*> spriteSheets;
    
    //PS3 Controller.
    bool joystickEnabled;
    PS3ControllerWrapper* ps3Joysticks[16];
    
    //Scens
    /**
    *   Currently running scene
    */
    Scene* runningScene;
    
    /**
     *  Next scene waiting to get pushed
     */
    Scene* nextScene;
    
    /**
     *  Holds previously running scene. Gets deleted.
     */
    Scene* dyingScene;
    
    bool waitingForSceneTransition;
    void doSceneTransition();
    
    bool paused;
    
    WinSize winSize;
    
/// @}
/// -------------------------------------------------
    
/// -------------- Initialize Functions -------------
/// @{
/// @name OpenGL attributes
    
    /**
     *
     */
    void initOpenGL();
    
    /**
     *
     */
    void initGLEW();
    
    /**
     *
     */
    void initGLFW();
    
    /**
     *
     */
    void createWindow(const int& screenWidth, const int& screenHeight, const std::string& windowTitle);
    
    /** constructor */
    Director();
    /** destructo */
    ~Director();
    //Singleton. Do not implement this
    Director(Director const& other);
    //Singleton. Do not implement this
    void operator=(Director const&);
/// @}
/// -------------------------------------------------
    
/// ---------------- GLFW callback ------------------
/// @{
/// @name GLFW input callbuck functions
    
    /**
     *  Key input callback. 
     *  Called whenever there is a key input
     *  @param window GLFW window that receives inputs
     *  @param key A GLFW key value 
     *  @param scancode
     *  @param action State of key. GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT
     *  @param mods State of modifier key. (ex. Shift, alt, etc)
     */
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    /**
     *
     */
    static void mouse_move_callback(GLFWwindow* window, double xPos, double yPos);
    
    /**
     *
     */
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    
    /**
     *
     */
    static void glfw_error_callback(int error, const char *description);
    
/// @}
/// -------------------------------------------------
    
public:
    static Director& getInstance(){
        static Director instance;
        return instance;
    }
    
    /**
     *  Initailize application.
     *  Setups OpenGL and gui window
     */
    void initApp(const int screenWidth, const int screenHeight, const std::string windowTitle);

    void terminateApp();
    
    /**
     *	Run game loop
     */
    void run();
    
    void render();
    void update();
    
    std::string getWorkingDir();
    void setWorkingDir(std::string wd);

    /**
     *	Pause game loop
     */
    void pause(){this->paused = true;}
    bool isScenePaused(){return this->paused;}
    void resume(){this->paused = false;}
//
//    /**
//     *  Stop the game loop
//     */
//    void stop();
    
    /**
     *	Push scene to director's scene.
     *   This will replace the current running scene if exists
     */
    void pushScene(Scene* pScene);
    Scene* getRunningScene(){return this->runningScene;};
    
//    /**
//     *  Terminate current running scene,
//     */
//    void popScene();
//    
    /**
     *	Load the next scene, pop the current one and set the next scene to current scene
     */
    void transitionToNextScene(bool wait);
//
//    /**
//     *
//     */
//    void transitionSceneWith(Scene* newScene);

    void addProgramWithShader(const std::string programName, const std::string vertexShaderPath, const std::string fragmentShaderPath);

    
    WinSize getWindowSize();
    void setWindowSize(float width, float height);
    
    Program* getProgramPtr(std::string programName="Default");
    Camera* getCameraPtr();
    
    SoundManager* getSoundManager();
    
    void changeWindowSize(int w, int h);
    
    PS3ControllerWrapper* getJoyStick(int num);
    bool hasSpriteSheetFrameName(std::string frameName);
};

#endif /* defined(__OpenGL_2D_Framework__Director__) */
