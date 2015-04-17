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
//opengl
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "CommonInclude.h"

#include "Shader.h"
#include "Program.h"
#include "Camera.h"

#include <string>
#include <unordered_map>
#include "Timer.h"

//2D and 3D size is scaled down to 10. 
//ex) 1280 x 640 pixels texture -> 128 * 64 vertex length quad
const int SCREEN_TO_WORLD_SCALE = 10;
const float static GLOBAL_Z_VALUE = 0;

//limit the maximum scene queue to 5. 
const int MAX_SCENE_QUEUE_SIZE = 5;

struct WinSize{
	float w;
	float h;
};

class Director{
protected:
    //no one derives from this class!
private:
    WinSize winSize;
    
    glm::vec2 prevMousePos;
    bool leftClicked;
    
    //GLFW window
    GLFWwindow* window;
//
//    //Scene queue. FIFO. Only the first element gets updated and rendered.
    Scene* runningScene;
    Scene* nextScene;
//    Scene* dyingScene;
//    
    //shader & program
    std::unordered_map<std::string, Program*> programs;

    //camera
    Camera* mainCamera;

    void initOpenGL();
    void initGLEW();
    void initGLFW();
    void createWindow(const int& screenWidth, const int& screenHeight, const std::string& windowTitle);
    
    //basic functions
    Director();
    ~Director();
    Director(Director const& other);
    void operator=(Director const&);
    
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_move_callback(GLFWwindow* window, double xPos, double yPos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void glfw_error_callback(int error, const char *description);
    
public:
    static Director& getInstance(){
        static Director instance;
        return instance;
    }
    
//    /**
//     *	init the application.
//     *	init OpenGL
//     *	init GLEW
//     *	init GLFW
//     *	throw error exception if fail to initialize.
//     */
    void initApp(const int screenWidth, const int screenHeight, const std::string& windowTitle);

    void terminateApp();
    
    /**
     *	Run game loop
     */
    void run();
    
    void render();
    void update();
//
//    /**
//     *	Pause game loop
//     */
//    void pause();
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
    
//    /**
//     *  Terminate current running scene,
//     */
//    void popScene();
//    
//    /**
//     *	Load the next scene, pop the current one and set the next scene to current scene
//     */
//    void transitionToNextScene(bool wait);
//    
//    /**
//     *
//     */
//    void transitionSceneWith(Scene* newScene);

    void addProgramWithShader(const std::string programName, const std::string vertexShaderPath, const std::string fragmentShaderPath);

    
    WinSize getWindowSize();
    void setWindowSize(float width, float height);
    
    Program* getProgramPtr(std::string programName="Default");

//    void releaseShaders();
//    void releasePrograms();
//    void releaseScenes();
};

#endif /* defined(__OpenGL_2D_Framework__Director__) */
