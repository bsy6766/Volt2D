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
#include "ProgressBar.h"
#include "ProgressRadian.h"
#include "ParticleSystem.h"
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
    friend class Volt2D::ParticleSystem;
    friend class Volt2D::ProgressBar;
    friend class Volt2D::ProgressRadian;
    
    //mouse icon
    Volt2D::Sprite* mouseCursor;
    //temp
    glm::vec2 prevMousePos = glm::vec2();
    
#pragma mark OpenGL
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

#pragma mark System
/// -------------------- System ---------------------
/// @{
/// @name System atrributes
    
    /** Application's working directory */
    std::string workingDirectory;
    
    /** Main GLFW window */
    GLFWwindow* window;
    
    /** SoundManager instance */
    Volt2D::SoundManager* soundManager;
    
    //@deprecated
    bool paused;
    
    
    /// @{
    /// @name Application window & input settings
    bool vsync;
    bool fullscreen;
    bool borderless;
    bool captureMouse;
    bool cursorHidden;
    /// @}
    
    
    /** Window size */
    WinSize winSize;
    
    /** Change window size */
    void changeWindowSize(const int w, const int h);
    
    /// @{
    /// @name SpriteSheets
    /**
     *  Sprite sheet container
     *  Stores SpriteSheet pointer with std::string name as an ID
     */
    std::unordered_map<std::string, Volt2D::SpriteSheet*> spriteSheets;
    
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
    ///@}
    
    
    /// @{
    /// @name Joysticks
    /** true if at least one joystick is connected */
    bool joystickEnabled;
    
    /** Joystick container */
    //\todo Make one for XBOX controller as well(but I don't have one...)
    Volt2D::PS3ControllerWrapper* ps3Joysticks[MAX_JOYSTICK];
    /// @}
    
    /// @{
    /// @name Scene and Transitions
    /** Currently running scene */
    Volt2D::Scene* runningScene;
    
    /** Next scene waiting to get pushed */
    Volt2D::Scene* nextScene;
    
    /** Holds previously running scene. Gets deleted. */
    Volt2D::Scene* dyingScene;
    
    /** Let Transition's swapScene function to access Scene instances */
    friend void Transition::swapScene();
    
    /** Transition object pointer */
    Volt2D::Transition* sceneTransition;
    
    /** true if scene is transitioning. Else, false. */
    bool transitioning;
    /// @}
    
    
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
#pragma mark Init & Release
/// ---------------- Init & Release ------------------
/// @{
/// @Application init & release
    
    /** Instance getter */
    static Director& getInstance(){
        static Director instance;
        return instance;
    }
    
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
    
    /** Terminate GLFW window */
    void terminateApp();
    
    /** Run application (main game loop) */
    void run();
/// @}
/// -------------------------------------------------
    
    
    /** Get window size */
    WinSize getWindowSize();
    
    
    /// @{
    /// @name Scene management
    /** Replace scene */
    void replaceScene(Scene* newScene);
    
    /** Get running scene. Returning scene pointer might be vulnerable from getting deleted or modified, but that's none of my business and user must be able to control the scene freely but Director */
    Volt2D::Scene* getRunningScene();
    
    /**
     *  Transition scene to next scene
     *  @param Transition object to transition
     */
    void transitionToNextScene(Transition* transition);
    /// @}
    
    /// @{
    /// @name Working directory
    /** Get application's working directory */
    std::string getWorkingDir();
    
    /** Set application's working directory */
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
    
    /** Add OpenGL program to system */
    void addProgramWithShader(const std::string programName, const std::string vertexShaderPath, const std::string fragmentShaderPath);
    
    /** Get OpenGL program */
    Volt2D::Program* getProgramPtr(std::string programName="Default");
    
    /** Get Projection * View matrix of screen */
    const glm::mat4 getProjectiveViewMatrix();
    
    /** Get SoundManager instance pointer */
    //\todo Instead of returning pointer, make Director to have wrapper functions to controll sound
    Volt2D::SoundManager* getSoundManager();
    
    /** Get joystick by number ID */
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
