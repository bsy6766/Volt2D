//
//  Director.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Director.h"
#include "Sprite.h"

Director::Director():
winSize({ 0, 0 }),
runningScene(0),
nextScene(0)
//dyingScene(0)
{
    char cCurrentPath[FILENAME_MAX];
    
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
//        return errno;
    }
    
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    
    //    printf ("The current working directory is %s\n", cCurrentPath);
    workingDirectory = cCurrentPath;
    std::cout << "The current working directory is " << workingDirectory << std::endl;
}

Director::~Director(){
    cout << "Director::Deleting...";
    //delete all remaing scenes
    if(runningScene) delete runningScene;
//    if(nextScene) delete nextScene;
    
    for(auto it = programs.begin(); it != programs.end(); ++it )
        delete it->second;
        
    if(camera)
        delete camera;
    
    SoundManager::getInstance().terminateSoundManager();
    
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

std::string Director::getWorkingDir(){
    return workingDirectory;
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
        runningScene->boundWindow(window);
        runningScene->init();
    }
    else{
        //if there's next scene already, replace it
        if(nextScene){
            delete nextScene;
        }
        
        nextScene = newScene;
        nextScene->boundWindow(window);
        nextScene->init();
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
    addProgramWithShader("Text", "../Shader/textVertexShader.glsl", "../Shader/textFragmentShader.glsl");
    
    //create basic camera
    camera = new Camera();
    
    SoundManager::getInstance().initSoundManager();
}

void Director::terminateApp(){
    glfwSetWindowShouldClose(window, GL_TRUE);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    
    prevMousePos = glm::vec2(winSize.w/2, winSize.h/2);
    curMousePos = glm::vec2(winSize.w/2, winSize.h/2);
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
        directorPtr->runningScene->keyPressed(key);
//        directorPtr->runningScene->Scene::keyPressed(key);
    }
    else{
        directorPtr->runningScene->keyReleased(key);
//        directorPtr->runningScene->Scene::keyReleased(key);
    }
}

void Director::mouse_move_callback(GLFWwindow *window, double xPos, double yPos){
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    Director *directorPtr = static_cast<Director*>(glfwGetWindowUserPointer(window));
    directorPtr->prevMousePos = glm::vec2((float)x, (float)y);
    
    if(x <= -640){
        x = -640;
        glfwSetCursorPos(window, x, y);
    }
    if(x >= 640){
        x = 640;
        glfwSetCursorPos(window, x, y);
    }
    if(y <= -360){
        y = -360;
        glfwSetCursorPos(window, x, y);
    }
    if(y >= 360){
        y = 360;
        glfwSetCursorPos(window, x, y);
    }
    
    directorPtr->runningScene->mouseMove(x, -y);
//    directorPtr->runningScene->Scene::mouseMove(x, -y);
//    cout << "(" << x << ", " << y << ")" << endl;
}

void Director::mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
    Director *directorPtr = static_cast<Director*>(glfwGetWindowUserPointer(window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    directorPtr->runningScene->mouseButton(x, -y, button, action);
    
//    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
//        double curMouseX, curMouseY;
//        glfwGetCursorPos(window, &curMouseX, &curMouseY);
//        glm::vec2 newMousePos = glm::vec2((float)curMouseX, (float)curMouseY);
//        //!!!update camera movement by mouse. Please move this function in to camera class later!!!!!
//        glm::vec2 mouseDelta = newMousePos - directorPtr->prevMousePos;
//        
//        cout << "mD = (" << mouseDelta.x << ", " << mouseDelta.y << ")" << endl;
//        
//        directorPtr->camera->changeAngle(0.15f * mouseDelta.y, 0.15f * mouseDelta.x);
//        
//        directorPtr->prevMousePos = newMousePos;
//    }

}


void Director::transitionToNextScene(bool wait = true){
    //check if there is running scene and next scene
    //first, init next scene and prepare all the materials for that scene
    //if there's any issue, remove the scene and cancel this event
    //else, you are good to go. swap the scene
    //if wait, then don't render and run sprites and actions till the transition is done,
    //else, run as soon as init is done
    //at the end, delete dying scene
    dyingScene = runningScene;
    runningScene = nextScene;
    nextScene = 0;
    
    delete dyingScene;
}

void Director::run(){
    int fps = 0;
    double timeCounter=  0;
    
    while (!glfwWindowShouldClose(window)){
        Timer::getInstance().recordTime();
        
        update();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
        
        timeCounter += Timer::getInstance().getElapsedTime();
        if(timeCounter > 1){
            fps++;
            cout << "fps = " << fps << endl;
            fps = 0;
            timeCounter--;
        }
        else{
            fps++;
        }
    }
}

void Director::render(){
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(runningScene)
        runningScene->render();
    glUseProgram(0);
}

void Director::update(){
    if(runningScene){
        runningScene->injectKey();
        runningScene->injectMouseMove();
        runningScene->update();
    }
}

Program* Director::getProgramPtr(std::string programName){
    if(programs.find(programName) != programs.end())
        return programs.at(programName);
    else
        return 0;
}

Camera* Director::getCameraPtr(){
    return camera;
}