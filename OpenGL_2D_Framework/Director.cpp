//
//  Director.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Director.h"
#include "Timer.h"

#pragma mark Constructor & Destructor
Volt2D::Director::Director():
winSize({ 0, 0 }),
runningScene(0),
nextScene(0),
soundManager(0),
ps3Joysticks(),   //init all to 0,
joystickEnabled(false),
paused(false),
waitingForSceneTransition(false),
clearBufferColor(glm::vec3()),
vsync(false),
//By default, window will be created as fullscreen(not windowed and boderless)
fullscreen(true),
borderless(false),
cursorHidden(false)
{
    char cCurrentPath[FILENAME_MAX];
    
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
//        return errno;
    }
    
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    
    workingDirectory = cCurrentPath;
    std::cout << "[SYSTEM::INFO] Working directory = " << workingDirectory << std::endl;
}

Volt2D::Director::~Director(){
    cout << "[SYSTEM::RELEASE] Deleting Director" << endl;
    
    cout << "[SYSTEM::RELEASE] Deleting OpenGL program and attached shaders" << endl;
    for(auto it = programs.begin(); it != programs.end(); ++it )
        delete it->second;
    
    cout << "[SYSTEM::RELEASE]  Deleting cached sprite sheets" << endl;
    for(auto it : spriteSheets){
        delete it.second;
    }
    
    cout << "[SYSTEM::RELEASE] Deleting camera" << endl;
    if(camera)
        delete camera;
    
    cout << "[SYSTEM::RELEASE] Destorying glfw window" << endl;
    //delete window and terminate. This must be processed at last.
    if (window){
        glfwDestroyWindow(window);
        window = 0;
    }
    glfwTerminate();
    
    cout << "[SYSTEM::RELEASE] Deleting sounds" << endl;
    if(soundManager){
        soundManager->release();
        delete soundManager;
    }
    
    cout << "[SYSTEM::RELEASE] Deleting scene" << endl;
    //delete all remaing scenes
    if(runningScene){
        runningScene->exit();
        delete runningScene;
    }

    if(nextScene){
        delete nextScene;
    }
    
    cout << "[SYSTEM::RELEASE] Removing joysticks" << endl;
    for(int i = 0; i < MAX_JOYSTICK; i++){
        if(ps3Joysticks[i])
            delete ps3Joysticks[i];
    }
    
    if(mouseCursor)
        delete mouseCursor;
    
    cout << "Done." << endl;
}

#pragma mark Init & Release
void Volt2D::Director::initApp(const int screenWidth, const int screenHeight, const std::string windowTitle, glm::vec3 clearBuffColor, bool vsync, bool fullscreen, bool borderless, bool captureMouse, bool cursorHidden){
    //pre check
    if(screenWidth == 0){
        throw std::runtime_error("Screen width can not be 0.");
    }
    
    if(screenHeight == 0){
        throw std::runtime_error("Screen height can not be 0.");
    }
    
    this->vsync = vsync;
    this->fullscreen = fullscreen;
    this->borderless = borderless;
    this->captureMouse = captureMouse;
    this->cursorHidden = cursorHidden;
    
    //window title can be empty...if you wish...
    
    cout << "[SYSTEM::INFO] Initializing application." << endl;
    cout << "[SYSTEM::INFO] Application title = " << windowTitle << endl;
    cout << "[SYSTEM::INFO] Screen width = " << screenWidth << endl;
    cout << "[SYSTEM::INFO] Screen height = " << screenHeight << endl;
    cout << endl;
    
    initGLFW();
    createWindow(screenWidth, screenHeight, windowTitle);
    winSize = {(float)screenWidth, (float)screenHeight};
    initGLEW();
    initOpenGL();
    
    //create basic shader.
    //Default shader. Used for sprite and default renderable objects
    addProgramWithShader("Default", "vertexShader.glsl", "fragmentShader.glsl");
    //Text shader.
    addProgramWithShader("Text",  "textVertexShader.glsl", "textFragmentShader.glsl");
    //Sprite animation shader. Uses GL_TEXTURE_2D_ARRAY
    addProgramWithShader("SpriteAnimation", "saVertexShader.glsl", "saFragmentShader.glsl");
    //Particle system shader. Uses intancing rendering.
    addProgramWithShader("ParticleSystem", "particleVertexShader.glsl", "particleFragmentShader.glsl");
    
    //create basic camera. It will pos camera to exact place where it perfectly fits screen width and height
    camera = Volt2D::Camera::createCamera();
    
    //create sound manager.
    soundManager = Volt2D::SoundManager::createSoundManager();
    
    //detect joystick. GLFW has max 16 joystick module connections
    //Assume we are only using PS3 for this moment
    for(int i = 0; i<16; i++){
        if(glfwJoystickPresent(i) == GL_TRUE){
            int buttonCount, axisCount;
            glfwGetJoystickButtons(i, &buttonCount);
            glfwGetJoystickAxes(i, &axisCount);
            if(ps3Joysticks[i])
                delete ps3Joysticks[i];
            ps3Joysticks[i] = new Volt2D::PS3ControllerWrapper(i, buttonCount, axisCount);
            cout << "[SYSTEM::INFO] Detected joystick on #" << i << ". Name = " << glfwGetJoystickName(i) << ". button = " << buttonCount << ", axis = " << axisCount << "." << endl;
            joystickEnabled = true;
            //TODO: Remove this for multiple controller
            break;
        }
    }
    
    //Hardcoded sprite.
    mouseCursor = Volt2D::Sprite::createSprite("globalMouseCursor", "mouse_icon.png");
    
    //set clear buffer color
    this->clearBufferColor = clearBuffColor;
}

void Volt2D::Director::terminateApp(){
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Volt2D::Director::initOpenGL(){
    //Disable depth test. Everything will be rendered on same z axis (0)
    glDisable(GL_DEPTH_TEST);
    
    //Used to disable depth func to GL_ALWAYS than GL_LESS, but turns out it didn't need to.
    //    glDepthFunc(GL_ALWAYS);
    
    //Default blending setting.
    glEnable(GL_BLEND);
    //Particle system will have their own belnding option.
    //\todo Give objects option to change blending mode.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //Default matrix mode.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Volt2D::Director::initGLEW(){
    //init glew, return if fails. NOTE: this must be called after window is created since it requires opengl info(?)
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    
    if (GLEW_OK != err){
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        throw std::runtime_error("glew init failed");
    }
    
    cout << "[SYSTEM::INFO] OpenGL and system informations." <<endl;
    // print out some info about the graphics drivers
    cout << "[SYSTEM::INFO] OpenGL version: " << glGetString(GL_VERSION) << endl;
    cout << "[SYSTEM::INFO] GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "[SYSTEM::INFO] Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "[SYSTEM::INFO] Renderer: " << glGetString(GL_RENDERER) << endl << endl;
    
    //@warning Hardcorded
    if (!GLEW_VERSION_4_1){
        throw std::runtime_error("OpenGL 4.1 API is not available");
    }
}

void Volt2D::Director::initGLFW(){
    if (glfwInit() != GL_TRUE){
        throw std::runtime_error("Failed to initialize GLFW");
    }
    else{
        cout << "[SYSTEM::INFO] Succesfully initialized glfw." << endl;
        int vMajor;
        int vMinor;
        int vRev;
        glfwGetVersion(&vMajor, &vMinor, &vRev);
        cout << "[SYSTEM::INFO] GLFW version " << vMajor << "." << vMinor << "." << vRev << endl;
    }
}

void Volt2D::Director::createWindow(const int &screenWidth, const int &screenHeight, const std::string &windowTitle){
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
    
    //check fullscreen mode first.
    if(fullscreen){
        //if fullscreen is true, then windowed and borderless will be forced to false since it doesn't uses it.
        this->borderless = false;
        //Iconify when fullscreen loses focus.
        glfwWindowHint(GLFW_AUTO_ICONIFY, GL_TRUE);
        //Remove window border
        glfwWindowHint(GLFW_DECORATED, GL_FALSE);
        //Create window on primary window
        this->window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), glfwGetPrimaryMonitor(), NULL);
        cout << "[SYSTEM::INFO] Creating window in fullscreen mode." << endl;
    }
    else{
        //if it's not full screen, then it's allways windowed.
        //but it can be borderless windowed or bordered
        //So, since it's windowed, let user can leave app as normal window instead of iconifying when app loses focus
        glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
        
        if(borderless){
            //borderless. Lets just show border to see the window title
            glfwWindowHint(GLFW_DECORATED, GL_FALSE);

        }
        else{
            //borderless. Lets just show border to see the window title
            glfwWindowHint(GLFW_DECORATED, GL_TRUE);
        }
        
        //create window with size and title.
        window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), NULL, NULL);
    }
    
    //set error call back
    glfwSetErrorCallback(glfw_error_callback);
    
    //Need to move app window a bit to right and bottom. Windows only.
    //Mac(Xcode) opens app window on the center of the screen.
//#ifdef _WIN32
//    //set window's position (topleft anchor point) x by 100 and y by 100
//    glfwSetWindowPos(window, 100, 100);
//#endif
    
    //if window wasn't created,
    if (!window){
        glfwTerminate();
        throw std::runtime_error("Can not create glfw window.");
    }
    
    //if window is successfully made, make it current window
    glfwMakeContextCurrent(window);
    
    //disable vsync
    if(!this->vsync)
        glfwSwapInterval(0);
    
    //register key callback func
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    //capture mouse on screen
    if(this->fullscreen){
        //if it's full screen,
        if(this->captureMouse){
            //capturing mouse in fullscreen mode.
            //cursor is hidden by default
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            this->cursorHidden = true;
        }
        else{
            //not capturing mouse cursor.
            //user can freely move mouse cursor around the window even out side of window even while fullscreen.
            //if it's fullscreen, it will iconify window if user click other window.
            //set option for hiding cursor
            if(this->cursorHidden){
                //cursor will be hidden if it's on top of the app's window. Else, it's show as normal.
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }
            //else, use default
        }
    }
    
    glfwSetCursorPos(this->window, 0, 0);
}

#pragma mark Scene Management
void Volt2D::Director::pushScene(Volt2D::Scene* newScene){
    if(!runningScene){
        cout << "No running scene exists. Pushing new scene to running scene" << endl;
        runningScene = newScene;
//        runningScene->bindWindow(window);
        //if no scene exist, call init right now
        runningScene->init();
    }
    else{
        //if there's next scene already, replace it
        if(nextScene){
            delete nextScene;
        }
        
        nextScene = newScene;
//        nextScene->bindWindow(window);
        //call init on switching
        //        nextScene->init();
    }
}

//void Volt2D::Director::popScene(){
//    if(runningScene){
//        cout << "Volt2D::Director::popScene() popping current running scene" << endl;
//        delete runningScene;
//    }
//
//    if(nextScene){
//        cout << "Volt2D::Director::popScene() next scene exists." << endl;
//        runningScene = nextScene;
//        nextScene = 0;
//    }
//}

void Volt2D::Director::transitionToNextScene(bool wait = true){
    //check if there is running scene and next scene
    //first, init next scene and prepare all the materials for that scene
    //if there's any issue, remove the scene and cancel this event
    //else, you are good to go. swap the scene
    //if wait, then don't render and run sprites and actions till the transition is done,
    //else, run as soon as init is done
    //at the end, delete dying scene
    
    waitingForSceneTransition = wait;
}

void Volt2D::Director::doSceneTransition(){
    dyingScene = runningScene;
    runningScene = nextScene;
    nextScene = 0;
    //can show scene transition effect here
    
    //initialize entering scene
    runningScene->init();
    //release leaving scene
    dyingScene->exit();
    //then delete the object
    delete dyingScene;
    dyingScene = 0;
    
    waitingForSceneTransition = false;
}

#pragma mark System
void Volt2D::Director::addProgramWithShader(const std::string programName, const std::string vertexShaderPath, const std::string fragmentShaderPath){
    std::string shaderPath = workingDirectory + "/../Shader/";
    
    Volt2D::Shader* vertexShader = Volt2D::Shader::
    createShader(shaderPath + vertexShaderPath, GL_VERTEX_SHADER);
    
    Volt2D::Shader* fragmentShader = Volt2D::Shader::createShader(shaderPath + fragmentShaderPath, GL_FRAGMENT_SHADER);
    
    Volt2D::Program* newProgram = Volt2D::Program::createProgram(vertexShader, fragmentShader);
    
    programs[programName] = newProgram;
}

void Volt2D::Director::run(){
    int fps = 0;
    double timeCounter=  0;
    
    while (!glfwWindowShouldClose(window)){
        Volt2D::Timer::getInstance().recordTime();
        double elapsedTime = Volt2D::Timer::getInstance().getElapsedTime();
        //update joystick
        if(joystickEnabled){
            for(int i = 0; i<MAX_JOYSTICK; i++){
                if(ps3Joysticks[i]){
                    int buttonCount;
                    const unsigned char* buttonInputs = glfwGetJoystickButtons(i, &buttonCount);
                    if(buttonCount)
                        ps3Joysticks[i]->receiveButtonInput(buttonInputs);
                    
                    int axisCount;
                    const float* axisInputs = glfwGetJoystickAxes(i, &axisCount);
                    if(axisCount)
                        ps3Joysticks[i]->receiveAxisInput(axisInputs);
                    break;
                }
            }
        }
        
        this->update(elapsedTime);
        
        //        if(!paused)
        render();
        
        mouseCursor->render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        timeCounter += elapsedTime;
        if(timeCounter > 1){
            fps++;
            cout << "fps = " << fps << endl;
            fps = 0;
            timeCounter--;
        }
        else{
            fps++;
        }
        
        if(waitingForSceneTransition){
            doSceneTransition();
        }
    }
}

void Volt2D::Director::render(){
    glClearColor(clearBufferColor.r, clearBufferColor.g, clearBufferColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(runningScene)
        runningScene->render();
    glUseProgram(0);
}

void Volt2D::Director::update(double dt){
    if(runningScene){
        runningScene->injectKey();
        runningScene->injectMouseMove();
        if(!paused)
            runningScene->update(dt);
        //at least once per frame. update it
        soundManager->updateSystem();
    }
}

#pragma mark Getters & Setters
Volt2D::WinSize Volt2D::Director::getWindowSize(){
    return winSize;
}

std::string Volt2D::Director::getWorkingDir(){
    return workingDirectory;
}

Volt2D::Program* Volt2D::Director::getProgramPtr(std::string programName){
    if(programs.find(programName) != programs.end())
        return programs.at(programName);
    else
        return 0;
}

Volt2D::Camera* Volt2D::Director::getCameraPtr(){
    return camera;
}

void Volt2D::Director::setWorkingDir(std::string wd){
    workingDirectory = wd;
}

Volt2D::SoundManager* Volt2D::Director::getSoundManager(){
    return this->soundManager;
}

void Volt2D::Director::changeWindowSize(int w, int h){
    glfwSetWindowSize(window, w, h);
}

Volt2D::PS3ControllerWrapper* Volt2D::Director::getJoyStick(int num){
    return this->ps3Joysticks[num];
}

#pragma mark GLFW callbacks
void Volt2D::Director::glfw_error_callback(int error, const char *description){
    std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

void Volt2D::Director::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    Director *directorPtr = static_cast<Director*>(glfwGetWindowUserPointer(window));
    //ESC key won't termiate app unless it's on main screen
    //if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    //    glfwSetWindowShouldClose(window, GL_TRUE);
    //}
    if(action == GLFW_PRESS){
        directorPtr->runningScene->keyPressed(key, mods);
        //        if(key == GLFW_KEY_S){
        //            directorPtr->camera->moveBackward();
        //            glm::vec3 cPos = directorPtr->camera->getPosition();
        //            cout << "cpos = (" << cPos.x << ", " << cPos.y << ", " << cPos.z << ")" << endl;
        //        }
        //        else if(key == GLFW_KEY_W){
        //            directorPtr->camera->moveFoward();
        //            glm::vec3 cPos = directorPtr->camera->getPosition();
        //            cout << "cpos = (" << cPos.x << ", " << cPos.y << ", " << cPos.z << ")" << endl;
        //        }
        //
        //        if(key == GLFW_KEY_A){
        //            directorPtr->camera->moveLeft();
        //            glm::vec3 cPos = directorPtr->camera->getPosition();
        //            cout << "cpos = (" << cPos.x << ", " << cPos.y << ", " << cPos.z << ")" << endl;
        //        }
        //        else if(key == GLFW_KEY_D){
        //            directorPtr->camera->moveRight();
        //            glm::vec3 cPos = directorPtr->camera->getPosition();
        //            cout << "cpos = (" << cPos.x << ", " << cPos.y << ", " << cPos.z << ")" << endl;
        //        }
        //
        //        if(key == GLFW_KEY_R){
        //            directorPtr->camera->moveUp();
        //            glm::vec3 cPos = directorPtr->camera->getPosition();
        //            cout << "cpos = (" << cPos.x << ", " << cPos.y << ", " << cPos.z << ")" << endl;
        //        }
        //        else if(key == GLFW_KEY_F){
        //            directorPtr->camera->moveDown();
        //            glm::vec3 cPos = directorPtr->camera->getPosition();
        //            cout << "cpos = (" << cPos.x << ", " << cPos.y << ", " << cPos.z << ")" << endl;
        //        }
        
        if(key == GLFW_KEY_H){
            glfwSetCursorPos(directorPtr->window, 100, 100);
        }
    }
    else if(action == GLFW_RELEASE){
        directorPtr->runningScene->keyReleased(key, mods);
    }
    else if(action == GLFW_REPEAT){
        
    }
}

void Volt2D::Director::mouse_move_callback(GLFWwindow *window, double xPos, double yPos){
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    Director *directorPtr = static_cast<Director*>(glfwGetWindowUserPointer(window));
    
    float w = directorPtr->winSize.w;
    float h = directorPtr->winSize.h;
//    
//    if(x < 0){
//        x = 0;
//        glfwSetCursorPos(window, x, y);
//    }
//    if(x > w-1){
//        x = w-1;
//        glfwSetCursorPos(window, x, y);
//    }
//    if(y < -1){
//        y = -1;
//        glfwSetCursorPos(window, x, y);
//    }
//    if(y > h-1){
//        y = h-1;
//        glfwSetCursorPos(window, x, y);
//    }
//
    //send raw mouse position instead of world coordinate
    directorPtr->runningScene->mouseMove(x, y);
    directorPtr->mouseCursor->setPosition(glm::vec3(x - (w/2.0f), (h/2.0f) - y, 0));
    
    //camera movement
    //    directorPtr->runningScene->Scene::mouseMove(x, -y);
    //    cout << "(" << x << ", " << y << ")" << endl;
    //    glm::vec2 newMousePos = glm::vec2((float)x, (float)y);
    //    //!!!update camera movement by mouse. Please move this function in to camera class later!!!!!
    //    glm::vec2 mouseDelta = newMousePos - directorPtr->prevMousePos;
    //
    ////    cout << "mD = (" << mouseDelta.x << ", " << mouseDelta.y << ")" << endl;
    //
    //    directorPtr->camera->changeAngle(0.15f * mouseDelta.y, 0.15f * mouseDelta.x);
    //    directorPtr->prevMousePos = newMousePos;
}

void Volt2D::Director::mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
    Director *directorPtr = static_cast<Director*>(glfwGetWindowUserPointer(window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    directorPtr->runningScene->mouseButton(x, -y, button, action);
    cout << "x = " << x <<", y = << " << -y << endl;
}

#pragma mark SpriteSheet caching
bool Volt2D::Director::hasSpriteSheetFrameName(std::string frameName){
    return spriteSheets.find(frameName) != spriteSheets.end();
}

Volt2D::SpriteSheet* const Volt2D::Director::getSpriteSheet(std::string frameName){
    auto it = spriteSheets.find(frameName);
    if(it != spriteSheets.end())
        return it->second;
    else
        return 0;
}

void Volt2D::Director::cacheSpriteSheet(std::string frameName, Volt2D::SpriteSheet *spriteSheet){
    auto find_it = spriteSheets.find(frameName);
    if(find_it == spriteSheets.end()){
        cout << "[System::INFO] Caching \"" << frameName << "\" sprite sheet." << endl;
        spriteSheets[frameName] = spriteSheet;
    }
    else{
        cout << "[SYSTEM::ERROR] Same name(\"" << frameName << "\") of sprite sheet already exists." << endl;
    }
}

void Volt2D::Director::unCacheSpriteSheet(std::string frameName){
    auto find_it = spriteSheets.find(frameName);
    if(find_it == spriteSheets.end()){
        cout << "[SYSTEM::ERROR] No sprite sheet entry called \"" << frameName << "\" found." << endl;
    }
    else{
        spriteSheets.erase(find_it);
    }
}