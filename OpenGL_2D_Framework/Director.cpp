//
//  Director.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Director.h"

Director::Director():
winSize({ 0, 0 }),
runningScene(0),
nextScene(0),
//dyingScene(0)
prevMousePos(glm::vec2(-1, -1))
{
    
}

Director::~Director(){
    cout << "Director::Deleting...";
    //delete all remaing scenes
    if(runningScene) delete runningScene;
//    if(nextScene) delete nextScene;
    
    for(auto it = programs.begin(); it != programs.end(); ++it )
        delete it->second;
        
    if(mainCamera)
        delete mainCamera;
    
    cout << "GLFW window...";
    //delete window and terminate. This must be processed at last.
    if (window){
        glfwDestroyWindow(window);
        window = 0;
    }
    glfwTerminate();

    cout << "Done." << endl;
}

void Director::setWindowSize(float width, float height){
    winSize = {width, height};
}

WinSize Director::getWindowSize(){
    return winSize;
}

void Director::addProgramWithShader(const std::string programName, const std::string vertexShaderPath, const std::string fragmentShaderPath){
    Program* newProgram = new Program();
    
    Shader* vertexShader = new Shader();
    vertexShader->createShader(vertexShaderPath, GL_VERTEX_SHADER);
    
    Shader* fragmentShader = new Shader();
    fragmentShader->createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    
    newProgram->createProgram(vertexShader, fragmentShader);
    programs[programName] = newProgram;
}

void Director::pushScene(Scene* newScene){
    if(!runningScene){
        cout << "No running scene exists. Pushing new scene to running scene" << endl;
        runningScene = newScene;
        runningScene->init();
    }
    else{
        //if there's next scene already, replace it
        if(nextScene){
            delete nextScene;
        }
        
        nextScene = newScene;
    }
}

//void Director::popScene(){
//    if(runningScene){
//        cout << "Director::popScene() popping current running scene" << endl;
//        delete runningScene;
//    }
//    
//    if(nextScene){
//        cout << "Director::popScene() next scene exists." << endl;
//        runningScene = nextScene;
//        nextScene = 0;
//    }
//}

void Director::initApp(const int screenWidth = 100, const int screenHeight = 100, const std::string& windowTitle = "noName"){
    std::cout << "Director: initializing app" << std::endl;
    initGLFW();
    createWindow(screenWidth, screenHeight, windowTitle);
    winSize = {(float)screenWidth, (float)screenHeight};
    initGLEW();
    initOpenGL();
    
    //create basic shader
    addProgramWithShader("Default", "../Shader/vertexShader.glsl", "../Shader/fragmentShader.glsl");
    
    //create basic camera
    mainCamera = new Camera();
}

void Director::terminateApp(){
    
}

void Director::initOpenGL(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    //    glDepthFunc(GL_LESS);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Director::initGLEW(){
    //init glew, return if fails. NOTE: this must be called after window is created since it requires opengl info(?)
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    
    if (GLEW_OK != err){
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        throw std::runtime_error("glew init failed");
    }
    
    // print out some info about the graphics drivers
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    
    if (!GLEW_VERSION_4_1){
        throw std::runtime_error("OpenGL 4.1 API is not available");
    }
}

//GLFW call back
//void glfwErrorCallback(int error, const char *description){
//	std::cerr << "GLFW error " << error << ": " << description << std::endl;
//}

void Director::initGLFW(){
    if (glfwInit() != GL_TRUE){
        throw std::runtime_error("DIRECTOR::Failed to init GLFW");
    }
}

void Director::createWindow(const int &screenWidth, const int &screenHeight, const std::string &windowTitle){
    
    //set to OpenGL 4.1
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    //Set the color info
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    
    //borderless. Lets just show border to see the window title
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    
    glfwSetErrorCallback(glfw_error_callback);
    
    //create window with size and title.
    window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), NULL, NULL);
    
    //Need to move app window a bit to right and bottom. Windows only.
    //Mac(Xcode) opens app window on the center of the screen.
#ifdef _WIN32
    //set window's position (topleft anchor point) x by 100 and y by 100
    glfwSetWindowPos(window, 100, 100);
#endif
    
    //store screen size. Use Scene instead
    //screenWidth = _screenWidth;
    //screenHeight = _screenHeight;
    
    //if window wasn't created,
    if (!window){
        glfwTerminate();
        throw std::runtime_error("ERROR: Can not create window.");
    }
    
    //if window is successfully made, make it current window
    glfwMakeContextCurrent(window);
    
    //register key callback func
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void Director::glfw_error_callback(int error, const char *description){
    std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

void Director::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    Director *directorPtr = static_cast<Director*>(glfwGetWindowUserPointer(window));
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if(action == GLFW_PRESS){
        cout << "Keyboard pressed" << endl;
        //W,S
        if(key == GLFW_KEY_W){
            directorPtr->mainCamera->moveFoward();
        }
        else if(key == GLFW_KEY_S){
            directorPtr->mainCamera->moveBackward();
        }
        
        //A,D
        if(key == GLFW_KEY_A){
            directorPtr->mainCamera->moveLeft();
        }
        else if(key == GLFW_KEY_D){
            directorPtr->mainCamera->moveRight();
        }
        
        //Lshift, space
        if(key == GLFW_KEY_F){
            directorPtr->mainCamera->moveDown();
        }
        else if(key == GLFW_KEY_R){
            directorPtr->mainCamera->moveUp();
        }
        
        if(key == GLFW_KEY_1){
            directorPtr->mainCamera->increaseSpeed();
        }
        else if(key == GLFW_KEY_2){
            directorPtr->mainCamera->decreaseSpeed();
        }
        
        if(key == GLFW_KEY_C){
            directorPtr->mainCamera->setPosition(glm::vec3(0, 0, -77.25));
        }
    }
    else if(action == GLFW_RELEASE){
//        directorPtr->runningScene->keyPressed();
        cout << "Keyboard released" << endl;
    }
}

void Director::mouse_move_callback(GLFWwindow *window, double xPos, double yPos){
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    Director *directorPtr = static_cast<Director*>(glfwGetWindowUserPointer(window));
    directorPtr->prevMousePos = glm::vec2((float)x, (float)y);
}

void Director::mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        Director *directorPtr = static_cast<Director*>(glfwGetWindowUserPointer(window));
        double curMouseX, curMouseY;
        glfwGetCursorPos(window, &curMouseX, &curMouseY);
        glm::vec2 newMousePos = glm::vec2((float)curMouseX, (float)curMouseY);
        //!!!update camera movement by mouse. Please move this function in to camera class later!!!!!
        glm::vec2 mouseDelta = newMousePos - directorPtr->prevMousePos;
        
        directorPtr->mainCamera->changeAngle(0.15f * mouseDelta.y, 0.15f * mouseDelta.x);
        
        directorPtr->prevMousePos = newMousePos;
    }

}

//
//void Director::transitionToNextScene(bool wait = true){
//    //check if there is running scene and next scene
//    //first, init next scene and prepare all the materials for that scene
//    //if there's any issue, remove the scene and cancel this event
//    //else, you are good to go. swap the scene
//    //if wait, then don't render and run sprites and actions till the transition is done,
//    //else, run as soon as init is done
//    //at the end, delete dying scene
//}

void Director::run(){
    while (!glfwWindowShouldClose(window)){
        Timer::getInstance().recordTime();
        
        update();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
}

void Director::render(){
    glClearColor(0, 0, 0, 1); //black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Camera
    glUseProgram(programs.at("Default")->getObject());
    //Camera Matrix. Projection * view.
    GLuint cameraUniformLocation = glGetUniformLocation(programs.at("Default")->getObject(), "cameraMat");
    glm::mat4 cameraMat = mainCamera->getMatrix();
    glUniformMatrix4fv(cameraUniformLocation, 1, GL_FALSE, &cameraMat[0][0]);
    
    
    if(runningScene)
        runningScene->render();
    
    glUseProgram(0);
}

void Director::update(){
    if(runningScene)
        runningScene->update();
}

Program* Director::getProgramPtr(std::string programName){
    return programs.at(programName);
}