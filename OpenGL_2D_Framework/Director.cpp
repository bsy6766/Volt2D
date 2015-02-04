//
//  Director.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Director.h"

Director::Director() :winSize({ 0, 0 }){

}

Director::~Director(){
	cout << "Director::Deleting...";
	cout << "Scene queue...";
	//delete all remaing scenes
	while (!sceneQueue.empty()){
		delete sceneQueue.front();
		sceneQueue.pop();
	}

	assert(sceneQueue.empty());

	cout << "GLFW window...";
	//delete window and terminate. This must be processed at last. 
	if (window){
		glfwDestroyWindow(window);
			window = 0;
	}
	glfwTerminate();

	cout << "Done." << endl;
}

WinSize Director::getWindowSize(){
	return winSize;
}

void Director::pushScene(Scene* pScene){
	if (sceneQueue.size() < MAX_SCENE_QUEUE_SIZE)
		sceneQueue.push(pScene);
	else
		cout << "Director::Failed to push scene. Scene queue is full." << endl;
}

void Director::initApp(const int screenWidth = 100, const int screenHeight = 100, const std::string& windowTitle = "noName"){
	initGLFW(screenWidth, screenHeight, windowTitle);
	initGLEW();
	initOpenGL();
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

void Director::initGLFW(const int& screenWidth, const int& screenHeight, const std::string& windowTitle){
	if (glfwInit() != GL_TRUE){
		throw std::runtime_error("DIRECTOR::Failed to init GLFW");
	}

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

	//glfwSetErrorCallback(glfwErrorCallback);

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
}

void Director::run(){

}