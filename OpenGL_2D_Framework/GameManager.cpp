//
//  GameManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/2/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "GameManager.h"

void glfwErrorCallback(int error, const char *description){
    std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

GameManager::GameManager(){
    std::cout << "GameManager created" << std::endl;
}

GameManager::~GameManager(){
    //delete window and terminate
    glfwDestroyWindow(window);
    window = 0;
    glfwTerminate();
    std::cout << "GameManager deleted" << std::endl;
}

void GameManager::initEssentials(){
    dayBackground = 0;
    vertexShader = 0;
    fragmentShader = 0;
    program = 0;
    camera = 0;
    window = 0;
    
    prevMousePos = glm::vec2(-1, -1);
    leftClicked = false;
    printFPS = false;
    
    loading = true;
    loadingFading = false;
    
    windowSize = Scene::getInstance().getWindowSize();
}

void GameManager::initKeyLock(){
    spaceKeyLock = false;
}

void GameManager::initOpenGL(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
//    glDepthFunc(GL_LESS);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GameManager::initGLEW(){
    //init glew, return if fails. NOTE: this must be called after window is created since it requires opengl info(?)
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    
    if (GLEW_OK != err){
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        throw std::runtime_error("glew init failed");
    }
    
    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    
    if(!GLEW_VERSION_4_1){
        throw std::runtime_error("OpenGL 4.1 API is not available");
    }
}

void GameManager::initGLFW(){
    if(glfwInit() != GL_TRUE){
        throw std::runtime_error("glfw init fail");
    }
}

void GameManager::createWindow(int _screenWidth, int _screenHeight, std::string &title){
    //set to OpenGL 4.1
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    
    //Set the color info
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    
    //borderless. Lets just show border to see the window title
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    
    glfwSetErrorCallback(glfwErrorCallback);
    
    //create window with size and title.
    window = glfwCreateWindow(_screenWidth, _screenHeight, title.c_str(), NULL, NULL);

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
    if(!window){
        glfwTerminate();
        throw std::runtime_error("ERROR: Can not create window.");
    }
    
    //if window is successfully made, make it current window
    glfwMakeContextCurrent(window);
}

void GameManager::render(){
    glClearColor(1, 1, 1, 1); //black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(program->getObject());
    
    //Camera Matrix. Projection * view.
    GLuint cameraUniformLocation = glGetUniformLocation(program->getObject(), "cameraMat");
    glm::mat4 cameraMat = camera->getMatrix();
    glUniformMatrix4fv(cameraUniformLocation, 1, GL_FALSE, &cameraMat[0][0]);
    
    if(loading){
//        loadingSpriteManager->render();
    }
    else{
        spriteManager->render();
        
        if(loadingFading){
            loadingSpriteManager->render();
		}
		particleSystemManager->render();
    }

    glUseProgram(0);
}

void GameManager::startGame(){
//    double startTime = glfwGetTime();
    double initialTime, singleLoopTime, elapsedTime, oneSecond = 0, fpsCounter = 0;
    Timer::getInstance().recordTime();
    
    while(Timer::getInstance().getTotalElapsedTime() < 2){
        Timer::getInstance().recordTime();
    }
    
    //start game loop
    while (!glfwWindowShouldClose(window)){
        Timer::getInstance().recordTime();
        initialTime = glfwGetTime();
        //run schedule update
        if(loading){
            //load main loop and update loading icon spin
            loadingSpriteManager->update();
            render();
            glfwSwapBuffers(window);
            glfwPollEvents();
            
            initSprites();
            
            loadingSpriteManager->update();
            render();
            glfwSwapBuffers(window);
            glfwPollEvents();
            
            initCharacter();
            
            loadingSpriteManager->update();
            render();
            glfwSwapBuffers(window);
            glfwPollEvents();
            
            initSpriteActions();
            
            loadingSpriteManager->update();
            render();
            glfwSwapBuffers(window);
            glfwPollEvents();
            
//            initParticle();
            spriteManager->update();
            render();
            glfwSwapBuffers(window);
            glfwPollEvents();
            
            finishLoading();
        }
        else{
            if(loadingFading){
                loadingSpriteManager->update();
            }
            //mainloop
            //handle inputs
            input();
            
            //update sprite data
            particleSystemManager->update();

            character->updateFrame();
            spriteManager->update();
        }
        
        //handle outputs
        render();
        
        //swap buffer
        glfwSwapBuffers(window);
        //get events(input)
        glfwPollEvents();
        
        //increment FPS counter
        fpsCounter++;
        singleLoopTime = glfwGetTime();
        elapsedTime = singleLoopTime - initialTime;
        oneSecond += elapsedTime;
        
        if(oneSecond > 1){
            if(printFPS)
                std::cout << "Current FPS = " << fpsCounter << std::endl;
            oneSecond -=1 ;
            fpsCounter = 0;
        }
    }
}

void GameManager::input(){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    //Left mouse click
    if(!leftClicked && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        leftClicked = true;
        double curMouseX, curMouseY;
        glfwGetCursorPos(window, &curMouseX, &curMouseY);
//        checkMouseClick(curMouseX, curMouseY);
    }
    
    if(!spaceKeyLock && character->canJump && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        std::cout << "space key pressed" << std::endl;
        spaceKeyLock = true;
        character->canJump = false;
        if(!jumpAction->alive && !jumpAction->running){
            jumpAction->revive();
        }
        character->addAction(jumpAction);
        character->runAction();
    }
    else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE){
        if(spaceKeyLock){
            std::cout << "space key released" << std::endl;
            spaceKeyLock = false;
        }
    }
    
    //W,S
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera->moveFoward();
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera->moveBackward();
    }
    
    //A,D
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera->moveLeft();
    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera->moveRight();
    }
    
    //Lshift, space
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
        camera->moveDown();
    }
    else if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
        camera->moveUp();
    }
    
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        camera->increaseSpeed();
    }
    else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        camera->decreaseSpeed();
    }
    
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        camera->setPosition(glm::vec3(0, 0, -77.25));
    }
    
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        glm::vec3 cameraPosition = camera->getPosition();
        std::cout << "(" << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << ")" << std::endl;
    }
    
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        double curMouseX, curMouseY;
        glfwGetCursorPos(window, &curMouseX, &curMouseY);
        glm::vec2 newMousePos = glm::vec2((float)curMouseX, (float)curMouseY);
        //!!!update camera movement by mouse. Please move this function in to camera class later!!!!!
        glm::vec2 mouseDelta = newMousePos - prevMousePos;
        
        camera->changeAngle(0.15f * mouseDelta.y, 0.15f * mouseDelta.x);
        
        prevMousePos = newMousePos;
    }
    else{
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        prevMousePos = glm::vec2((float)x, (float)y);
    }
    
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        if(!leftClicked){
            leftClicked = true;
            double cur_x, cur_y;
            glfwGetCursorPos(window, &cur_x, &cur_y);
            std::cout << "Left mouse button clicked on (" << cur_x << ", " << cur_y <<")" << std::endl;
//            windowCoordToOpenGLCoordinate(cur_x, cur_y);
        }
    }
    else{
        leftClicked = false;
    }
    
    if(!printFPS && glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        printFPS = true;
    }
    else if(printFPS && glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        printFPS = false;
    }
}

void GameManager::initSpriteManager(){
    spriteManager = new SpriteManager();
    loadingSpriteManager = new SpriteManager();
}

void GameManager::releaseSpriteManager(){
    delete spriteManager;
}

void GameManager::initLoading(){
//    loadingBG = new Sprite(program);
//    loadingBG->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/loading/loading background.png");
//    loadingBG->setZ_Depth(z_loading_BG);
//    loadingBG->setPosition(glm::vec2(640, 360));
    
    loadingIcon = new Sprite(program);
    loadingIcon->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/loading/loading icon.png");
    loadingIcon->setZ_Depth(z_loading_hud);
    loadingIcon->setPosition(glm::vec2(990, 40));
    
    loadingText = new Sprite(program);
    loadingText->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/loading/loading text.png");
    loadingText->setZ_Depth(z_loading_hud);
    loadingText->setPosition(glm::vec2(1150, 40));
    
//    loadingSpriteManager->addSprite(loadingBG);
    loadingSpriteManager->addSprite(loadingIcon);
    loadingSpriteManager->addSprite(loadingText);
    
    ActionRotateBy loadingIconRotateAction;
    loadingIconRotateAction.initRoateBy(360, 1);
    
    SpriteActionSchedule loadingIconSchedule;
    
    std::vector<SpriteAction*> loadingSequence{
        &loadingIconRotateAction
    };
    
    loadingIconSchedule.createSchedule(loadingSequence, REPEAT_FOREVER);
    loadingIcon->addActions(loadingIconSchedule);
    loadingIcon->runAction();
}

void GameManager::finishLoading(){
    loading = false;
    loadingFading = true;
    
    ActionFadeTo *fadeOutLoadingIcon = new ActionFadeTo();
    fadeOutLoadingIcon->initFadeTo(0, 2.0);
    
    ActionFadeTo *fadeOutLoadingText = new ActionFadeTo();
    fadeOutLoadingText->initFadeTo(0, 2.0);
//
//    ActionDelay delayBG;
//    delayBG.initDelay(2);
//    
//    ActionFadeTo fadeOutLoadingBG;
//    fadeOutLoadingBG.initFadeTo(0, 1);
    
//    SpriteActionSchedule loadingBGSchedule;
//    
//    std::vector<SpriteAction*> bgSequence{
//        &delayBG,
//        &fadeOutLoadingBG
//    };
//    
//    loadingBGSchedule.createSchedule(bgSequence, 0);
    
//    loadingBG->addActions(loadingBGSchedule);
    loadingIcon->addAction(fadeOutLoadingIcon);
    loadingText->addAction(fadeOutLoadingText);

//    loadingBG->runAction();
    loadingIcon->runAction();
    loadingText->runAction();
}

void GameManager::releaseLoading(){
    delete loadingSpriteManager;
}

void GameManager::initSprites(){
    dayBackground = new Sprite(program);
    dayBackground->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/day background.png");
    dayBackground->setZ_Depth(z_dayBackground);
    
    nightBackground = new Sprite(program);
    nightBackground->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/night background.png");
    nightBackground->setZ_Depth(z_nightBackground);
    nightBackground->setPosition(glm::vec2(640, 360));
    
    star1 = new Sprite(program);
    star1->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/star.png");
    star1->setZ_Depth(z_stars);
    star1->setPosition(glm::vec2(437, 633));
    
    star2 = new Sprite(program);
    star2->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/star.png");
    star2->setZ_Depth(z_stars);
    star2->setPosition(glm::vec2(960, 458));
    
    ground_1 = new Sprite(program);
    ground_1->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/ground.png");
    ground_1->setZ_Depth(z_ground);
    ground_1->setPosition(glm::vec2(640, 43));
    
    ground_2 = new Sprite(program);
    ground_2->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/ground_test.png");
    ground_2->setZ_Depth(z_ground);
    ground_2->setPosition(glm::vec2(1920, 43));
    
    buildingSilhouette1_1 = new Sprite(program);
    buildingSilhouette1_1->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/building silhouette 1.png");
    buildingSilhouette1_1->setZ_Depth(z_silhouette1);
    buildingSilhouette1_1->setPosition(glm::vec2(640, 187));
    
    buildingSilhouette1_2 = new Sprite(program);
    buildingSilhouette1_2->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/building silhouette 1.png");
    buildingSilhouette1_2->setZ_Depth(z_silhouette1);
    buildingSilhouette1_2->setPosition(glm::vec2(1920, 187));
    
    buildingSilhouette2_1 = new Sprite(program);
    buildingSilhouette2_1->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/building silhouette 2.png");
    buildingSilhouette2_1->setZ_Depth(z_silhouette2);
    buildingSilhouette2_1->setPosition(glm::vec2(640, 275));
    
    buildingSilhouette2_2 = new Sprite(program);
    buildingSilhouette2_2->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/building silhouette 2.png");
    buildingSilhouette2_2->setZ_Depth(z_silhouette2);
    buildingSilhouette2_2->setPosition(glm::vec2(1920, 275));
    
    buildingSilhouette3_1 = new Sprite(program);
    buildingSilhouette3_1->initSpriteWithTexture(GL_TEXTURE_2D, "../Texture/environment/building silhouette 3.png");
    buildingSilhouette3_1->setZ_Depth(z_silhouette3);
    buildingSilhouette3_1->setPosition(glm::vec2(868, 347));

    spriteManager->addSprite(dayBackground);
    spriteManager->addSprite(nightBackground);
    spriteManager->addSprite(star1);
    spriteManager->addSprite(star2);
    spriteManager->addSprite(buildingSilhouette1_1);
    spriteManager->addSprite(buildingSilhouette1_2);
    spriteManager->addSprite(buildingSilhouette2_1);
    spriteManager->addSprite(buildingSilhouette2_2);
    spriteManager->addSprite(buildingSilhouette3_1);
    spriteManager->addSprite(ground_1);
    spriteManager->addSprite(ground_2);
}

void GameManager::initCharacter(){
    character = new SpriteAnimation(program);
    character->init("run", "run", 8, 0.1);
    character->setZ_Depth(z_character);
    character->setPosition(glm::vec2(260, 150));
    spriteManager->addSprite(character);
}

void GameManager::releaseCharacter(){
    delete character;
}

void GameManager::initSpriteActions(){
    /* -------------------------Background Action------------------------------- */
    ActionFadeTo fadeOutDay;
    fadeOutDay.initFadeTo(0, 60);
    
    ActionDelay delayBtwFade;
    delayBtwFade.initDelay(5);
    
    ActionFadeTo fadeInDay;
    fadeInDay.initFadeTo(255, 60);
    
    SpriteActionSchedule dayBGSchedule;
    
    std::vector<SpriteAction*> actionBackgroundSequence
    {
        &delayBtwFade,
        &fadeOutDay,
        &delayBtwFade,
        &fadeInDay
    };
    
    dayBGSchedule.createSchedule(actionBackgroundSequence, REPEAT_FOREVER);
    dayBackground->addActions(dayBGSchedule);
    dayBackground->runAction();
    /* -------------------------Background Action------------------------------- */
    
    /* ---------------------------Ground Action--------------------------------- */
    ActionMoveTo moveGroundMiddleToLeft;
    moveGroundMiddleToLeft.initMoveTo(glm::vec2(-640, 43), 5.0);
    
    ActionMoveTo moveGroundBackToRight;
    moveGroundBackToRight.initMoveTo(glm::vec2(1920, 43), 0);
    
    ActionMoveTo moveGroundRightToMiddle;
    moveGroundRightToMiddle.initMoveTo(glm::vec2(640, 43), 5.0);
    
    SpriteActionSchedule groundOneSchedule;
    
    std::vector<SpriteAction*> actionSequenceOne
    {
        &moveGroundMiddleToLeft,
        &moveGroundBackToRight,
        &moveGroundRightToMiddle
    };

    groundOneSchedule.createSchedule(actionSequenceOne, REPEAT_FOREVER);
    
    SpriteActionSchedule groundTwoSchedule;
    
    std::vector<SpriteAction*> actionSequenceTwo{
        &moveGroundRightToMiddle,
        &moveGroundMiddleToLeft,
        &moveGroundBackToRight
    };
    
    groundTwoSchedule.createSchedule(actionSequenceTwo, REPEAT_FOREVER);
    
    ground_1->addActions(groundOneSchedule);
    ground_2->addActions(groundTwoSchedule);
    
    ground_1->runAction();
    ground_2->runAction();
    /* ---------------------------Ground Action--------------------------------- */
    
    /* -------------------Building Silhouette 1_1 Action------------------------ */
    
    float bsOneYPos = buildingSilhouette1_1->getPosition().y;
    
    ActionMoveTo moveBSOne_OneToLeft;
    moveBSOne_OneToLeft.initMoveTo(glm::vec2(-640, bsOneYPos), 15.0);
    ActionMoveTo moveBSOne_OneBackToRight;
    moveBSOne_OneBackToRight.initMoveTo(glm::vec2(1920, bsOneYPos), 0);
    ActionMoveTo moveBSOne_OneToMiddle;
    moveBSOne_OneToMiddle.initMoveTo(glm::vec2(640, bsOneYPos), 15.0);
    
    SpriteActionSchedule bsOne_OneSchedule;
    std::vector<SpriteAction*> bsOne_OneSeq{
        &moveBSOne_OneToLeft,
        &moveBSOne_OneBackToRight,
        &moveBSOne_OneToMiddle
    };
    bsOne_OneSchedule.createSchedule(bsOne_OneSeq, REPEAT_FOREVER);
    
    buildingSilhouette1_1->addActions(bsOne_OneSchedule);
    buildingSilhouette1_1->runAction();
    
    /* -------------------Building Silhouette 1_1 Action------------------------ */
    
    /* -------------------Building Silhouette 1_2 Action------------------------ */
    
    ActionMoveTo moveBSOne_TwoToMiddle;
    moveBSOne_TwoToMiddle.initMoveTo(glm::vec2(640, bsOneYPos), 15);
    ActionMoveTo moveBSOne_TwoToLeft;
    moveBSOne_TwoToLeft.initMoveTo(glm::vec2(-640, bsOneYPos), 15);
    ActionMoveTo moveBSOne_TwoBackToRight;
    moveBSOne_TwoBackToRight.initMoveTo(glm::vec2(1920, bsOneYPos), 0);
    
    SpriteActionSchedule bsOne_TwoSchedule;
    std::vector<SpriteAction*> bsOne_TwoSeq{
        &moveBSOne_TwoToMiddle,
        &moveBSOne_TwoToLeft,
        &moveBSOne_TwoBackToRight
    };
    bsOne_TwoSchedule.createSchedule(bsOne_TwoSeq, REPEAT_FOREVER);
    
    buildingSilhouette1_2->addActions(bsOne_TwoSchedule);
    buildingSilhouette1_2->runAction();
    
    /* -------------------Building Silhouette 1_2 Action------------------------ */
    
    /* -------------------Building Silhouette 2_1 Action------------------------ */
    
    float bsTwoYPos = buildingSilhouette2_1->getPosition().y;
    
    ActionMoveTo moveBSTwo_OneToLeft;
    moveBSTwo_OneToLeft.initMoveTo(glm::vec2(-640, bsTwoYPos), 35.0);
    ActionMoveTo moveBSTwo_OneBackToRight;
    moveBSTwo_OneBackToRight.initMoveTo(glm::vec2(1920, bsTwoYPos), 0);
    ActionMoveTo moveBSTwo_OneToMiddle;
    moveBSTwo_OneToMiddle.initMoveTo(glm::vec2(640, bsTwoYPos), 35.0);
    
    SpriteActionSchedule bsTwo_OneSchedule;
    std::vector<SpriteAction*> bsTwo_OneSeq{
        &moveBSTwo_OneToLeft,
        &moveBSTwo_OneBackToRight,
        &moveBSTwo_OneToMiddle
    };
    bsTwo_OneSchedule.createSchedule(bsTwo_OneSeq, REPEAT_FOREVER);
    
    buildingSilhouette2_1->addActions(bsTwo_OneSchedule);
    buildingSilhouette2_1->runAction();
    
    /* -------------------Building Silhouette 2_1 Action------------------------ */
    
    /* -------------------Building Silhouette 2_2 Action------------------------ */
    
    ActionMoveTo moveBSTwo_TwoToLeftDouble;
    moveBSTwo_TwoToLeftDouble.initMoveTo(glm::vec2(-640, bsTwoYPos), 70.0);
    ActionMoveTo moveBSTwo_TwoBackToRight;
    moveBSTwo_TwoBackToRight.initMoveTo(glm::vec2(1920, bsTwoYPos), 0);
    
    SpriteActionSchedule bsTwo_TwoSchedule;
    std::vector<SpriteAction*> bsTwo_TwoSeq{
        &moveBSTwo_TwoToLeftDouble,
        &moveBSTwo_TwoBackToRight
    };
    bsTwo_TwoSchedule.createSchedule(bsTwo_TwoSeq, REPEAT_FOREVER);
    
    buildingSilhouette2_2->addActions(bsTwo_TwoSchedule);
    buildingSilhouette2_2->runAction();
    
    /* -------------------Building Silhouette 2_2 Action------------------------ */
    
    /* -------------------Building Silhouette 3_1 Action------------------------ */
    float bsThreeYPos = buildingSilhouette3_1->getPosition().y;
    ActionMoveTo moveBSThree_OneToLeftDouble;
    moveBSThree_OneToLeftDouble.initMoveTo(glm::vec2(-100, bsThreeYPos), 140.0);
    ActionMoveTo moveBSThree_OneBackToRight;
    moveBSThree_OneBackToRight.initMoveTo(glm::vec2(1400, bsThreeYPos), 0);
    
    SpriteActionSchedule bsThree_OneSchedule;
    std::vector<SpriteAction*> bsThree_OneSeq{
        &moveBSThree_OneToLeftDouble,
        &moveBSThree_OneBackToRight
    };
    bsThree_OneSchedule.createSchedule(bsThree_OneSeq, REPEAT_FOREVER);
    
    buildingSilhouette3_1->addActions(bsThree_OneSchedule);
    buildingSilhouette3_1->runAction();
    
    /* -------------------Building Silhouette 3_1 Action------------------------ */
    
    /* ------------------------Character Jump Action---------------------------- */
    jumpAction = new ActionJumpBy();
    jumpAction->initJumpBy(glm::vec2(0, 30), 1);
    //this action won't be deleted by update. but removed from
    jumpAction->isProtected = true;
    /* ------------------------Character Jump Action---------------------------- */
}

void GameManager::releaseUndeadActions(){
    if(jumpAction){
        delete jumpAction;
        jumpAction = 0;
    }
}

void GameManager::initParticleSystemManager(){
    particleSystemManager = new ParticleSystemManager();
}

void GameManager::releaseParticleSystemManager(){
    delete particleSystemManager;
}

void GameManager::initParticleSystem(){
    testParticle = ParticleSystem::initWithParticleSize(100);
    testParticle->setPosition(glm::vec2(300, 360));
    testParticle->initParticleSystem(
                                     10.0,	//duration
                                     3.0,	//life time
                                     1.0,	//life time var
                                     10.0,	//speed
                                     5.0,	//speed var
                                     90.0,	//emit angle
                                     360.0,	//emit angle var
                                     0.0,	//gravity X
                                     0.0	//gravity Y
                                     );
    testParticle->initParticleTexture(GL_TEXTURE_2D, "../Texture/knife.jpg", program);
    
    particleSystemManager->addParticleSystem(testParticle);
}

void GameManager::loadShader(const std::string& filePath, GLenum shaderType){
    if(shaderType == GL_VERTEX_SHADER){
        //vertex shader
        vertexShader = new Shader();
        vertexShader->createShader(filePath, shaderType);
    }
    else if(shaderType == GL_FRAGMENT_SHADER){
        //fragment shader
        fragmentShader = new Shader();
        fragmentShader->createShader(filePath, shaderType);
    }
    else{
        throw std::runtime_error("Wrong type of (GLenum) shader");
    }
}

void GameManager::releaseShader(){
    if(vertexShader){
        std::cout << "Deleting vertex shader...";
        delete vertexShader;
        vertexShader = 0;
        std::cout << "Done." << std::endl;
    }
    
    if(fragmentShader){
        std::cout << "Deleting fragment shader...";
        delete fragmentShader;
        fragmentShader = 0;
        std::cout << "Done." << std::endl;
    }
}

void GameManager::loadProgram(){
    if(!program){
        program = new Program();
        program->createProgram(vertexShader, fragmentShader);
    }
    else{
        throw std::runtime_error ("Program is already created");
    }
}

void GameManager::releaseProgram(){
    std::cout << "Releasing program...id#" << program->getObject() << std::endl;
    
    if(program){
        GLuint vertexShaderObject = vertexShader->getObject();
        GLuint fragmentShaderObject = fragmentShader->getObject();
        std::cout << "Detaching shaders from program...";
        glDetachShader(program->getObject(), vertexShaderObject);
        glDetachShader(program->getObject(), fragmentShaderObject);
        glDeleteShader(vertexShaderObject);
        glDeleteShader(fragmentShaderObject);
        std::cout << "Done." << std::endl;
        std::cout << "Deleting program...";
        glDeleteProgram(program->getObject());
        std::cout << "Done." << std::endl;
        
        delete program;
        program = 0;
    }
    else{
        program = 0;
    }
}

void GameManager::loadCamera(){
    camera = new Camera();
}

void GameManager::releaseCamera(){
    if(camera)
        delete camera;
}