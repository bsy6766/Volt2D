//
//  Director.h
//  Volt2D
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Director__
#define __Volt2D__Director__

// OpenGL. Must include glew first than glfw.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//built in headers
#include <string>
#include <unordered_map>

//utility
#include "Utility.hpp"
#include "PS3ControllerWrapper.h"

//System
#include "Scene.h"
#include "SoundManager.h"
#include "Shader.h"
#include "Program.h"
#include "Camera.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Transition.h"

//Max number of joystick that glfw supports
#define MAX_JOYSTICK 16

//Getting working directory.
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#elif __APPLE__
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace Volt2D{
//Default constant.
//scaling down screen sprite image size to opengl 3d world's coordinate by 10. 100 x 100 pixels sprite will have 10 x 10 length vertex quad.
const float static SCREEN_TO_WORLD_SCALE = 10.0f;
//Global z value. All object has 0 for z.
const float static GLOBAL_Z_VALUE = 0;

//Simple window size pack
struct WinSize{
	float w;
	float h;
};
/**
 *  @class Director
 *  @brief Manages scene and underlying systems
 *  @note Singleton
 */
class Director{
private:
    //Friends
    friend class Volt2D::SpriteSheet;
    friend class Volt2D::Sprite;
    friend class Volt2D::Transition;
    
    //mouse icon
    Volt2D::Sprite* mouseCursor;
    
    glm::vec2 prevMousePos = glm::vec2();
    
/// -------------------- OpenGL ---------------------
/// @{
/// @name OpenGL attributes

    /**
     *  Main camera. It's fixed at most of the time.
     */
    Volt2D::Camera* camera;
    
    /**
     *  Unordered map that stores Program object with string ID
     */
    std::unordered_map<std::string, Volt2D::Program*> programs;
    
    //Buffer clearing color
    glm::vec3 clearBufferColor;
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
    Volt2D::SoundManager* soundManager;
    
    //@deprecated
    bool paused;
    
    bool vsync;
    bool fullscreen;
    bool borderless;
    bool captureMouse;
    bool cursorHidden;
    
    //Window size
    WinSize winSize;
    
    //SpriteSheet
    std::unordered_map<std::string, Volt2D::SpriteSheet*> spriteSheets;
    
    //PS3 Controller.
    //Enable flag
    bool joystickEnabled;
    //Controller storage.
    //\todo Make one for XBOX controller as well(but I don't have one...)
    Volt2D::PS3ControllerWrapper* ps3Joysticks[MAX_JOYSTICK];
    
    //Scens
    /** Currently running scene */
    Volt2D::Scene* runningScene;
    
    /** Next scene waiting to get pushed */
    Volt2D::Scene* nextScene;
    
    /** Holds previously running scene. Gets deleted. */
    Volt2D::Scene* dyingScene;
    
    void replaceScene(Scene* newScene);
    
    Volt2D::Transition* sceneTransition;
    
    bool transitioning = false;
    
    /**
     *  Get chached sprite sheet by name
     *  @param frameNAme
     */
    Volt2D::SpriteSheet* const getSpriteSheet(std::string frameName);
    
    /**
     *  Cache sprite sheet to system
     *  @param frameName A frame name for sprtie sheet
     *  @param spriteSheet SpriteSheet object pointer to store.
     */
    void cacheSpriteSheet(std::string frameName, Volt2D::SpriteSheet* spriteSheet);
    
    /**
     *  Remove sprite sheet from the system
     *  @param frameName
     */
    void unCacheSpriteSheet(std::string frameName);
    
    /**
     *  Check if there is sprite sheet with frame name.
     *  @param frameName A frame name to check
     *  @return true if there is sprite sheet with same name. Else, false.
     */
    bool hasSpriteSheetFrameName(std::string frameName);
/// @}
/// -------------------------------------------------
    
/// -------------- Initialize Functions -------------
/// @{
/// @name OpenGL attributes
    
    /**
     *  Initialize OpenGL. Depth, blending mode, etc
     */
    void initOpenGL();
    
    /**
     *  Initialize glew
     */
    void initGLEW();
    
    /**
     *  Initialize GLFW
     */
    void initGLFW();
    
    /**
     *  Create GLFW window.
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
     *  Mouse move call back.
     *  Called whenever mouse moves.
     *  @param window GLFW window that received inputs
     *  @param x X position of moved mouse cursor
     *  @param y Y position of moved mouse cursor
     */
    static void mouse_move_callback(GLFWwindow* window, double x, double y);
    
    /**
     *  Mouse button click call back
     *  Called whenever mouse is clicked.
     *  @param window GLFW window that receives inputs
     *  @param button A GLFW button value
     *  @param action State of key. (left, right, middle, etc)
     *  @param mods State of modifier key. (ex. Shift, alt, etc)
     */
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    
    /**
     *  GLFW error call back.
     *  Called whenever glfw throws error with code and description.
     */
    static void glfw_error_callback(int error, const char *description);
/// @}
/// -------------------------------------------------
    
public:
    //Instance getter
    static Director& getInstance(){
        static Director instance;
        return instance;
    }
    
    /// @{
    /// @Application related
    /**
     *  Initialize app.
     *  @note throws runtime error if fails to initialize.
     *  @param screenWidth Width of window to create
     *  @param screenHeight Height of window to create
     *  @param windowTitle A string for window's title
     *  @param vsync true to enable vsync. Else, false.
     *  @param fullscreen true if application is fullscreen. Else, false.
     *  @param borderless true if application is borderless. Else, false. Will forced to true if fullscreen is true.
     *  @param captureMouse true if want to capture mouse cursor.
     */
    void initApp(const int screenWidth, const int screenHeight, const std::string windowTitle , glm::vec3 clearBuffColor, bool vsync, bool fullscreen, bool borderelss, bool captureMouse, bool cursorHidden);
    
    // closw GLFW window
    void terminateApp();
    // Run application
    void run();
    /// @}
    
    /// @{
    /// @name Window sie
    //get window size
    WinSize getWindowSize();
    //change window size
    void changeWindowSize(int w, int h);
    /// @}
    
    /// @{
    /// @name Scene management
    //push scene to next scene
    void pushScene(Volt2D::Scene* pScene);
    //get currently running scene
    Volt2D::Scene* getRunningScene(){return this->runningScene;};
    //transition to next scene.
//    void transitionToNextScene(bool wait);
    void transitionToNextScene(Transition* transition);
    /// @}
    
    /// @{
    /// @name Working directory
    //wd getter
    std::string getWorkingDir();
    //wd setter
    void setWorkingDir(std::string wd);
    /// @}
    
    /**
     *  Render the scene
     */
    void render();
    /**
     *  Update the scene.
     *  @param dt Elapsed time since last iteration
     */
    void update(double dt);
    
    //Add opengl program
    void addProgramWithShader(const std::string programName, const std::string vertexShaderPath, const std::string fragmentShaderPath);
    //get opengl program
    Volt2D::Program* getProgramPtr(std::string programName="Default");
    
    //get camera
    Volt2D::Camera* getCameraPtr();
    
    //get sound manager
    Volt2D::SoundManager* getSoundManager();
    
    //get ps3 controller
    Volt2D::PS3ControllerWrapper* getJoyStick(int num);
    //    void pause(){this->paused = true;}
    //    bool isScenePaused(){return this->paused;}
    //    void resume(){this->paused = false;}
    //    //stop game loop
    //    void stop();
    //    void popScene();
};
}

#endif /* defined(__Volt2D__Director__) */
