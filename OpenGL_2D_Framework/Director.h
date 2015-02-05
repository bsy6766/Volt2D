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

#include <string>
#include <queue>

/**
*	Director class
*	Singleton
*	This class manages scenes. 
*/

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

	//GLFW window
	GLFWwindow* window;

	//Scene queue. FIFO. Only the first element gets updated and rendered.
	//First element = current scene
    std::queue<Scene* > sceneQueue;

	/**
	*	init OpenGL
	*/
	void initOpenGL();

	/**
	*	init GLEW
	*	This must be called after initializing GLFW. 
	*	See initGLFW()
	*/
	void initGLEW();

	/**
	*	init GLFW and create window
	*	@param screenWidth screen width
	*	@param screenHeight screen height
	*	@param windowTitle window title
	*/
	void initGLFW(const int& screenWidth, const int& screenHeight, const std::string& windowTitle);

	//basic functions
	Director();
	~Director();
	Director(Director const& other);
	void operator=(Director const&);

public:
	static Director& getInstance(){
		static Director instance;
		return instance;
	}

	/**
	*	init the application.
	*	init OpenGL
	*	init GLEW
	*	init GLFW
	*	throw error exception if fail to initialize.
	*/
	void initApp(const int screenWidth, const int screenHeight, const std::string& windowTitle);

	/**
	*	Run game loop
	*/
	void run();

	/**
	*	Pause game loop
	*/
	void pause();

    /**
     *  Stop the game loop
     */
	void stop();

	/**
	*	Push scene to director's scene queue
	*/
	void pushScene(Scene* pScene);

	/**
	*	Load the next scene, pop the current one and set the next scene to current scene
	*/
	void transitionToNextScene();
    
    /**
     *
     */
    void transitionSceneWith(Scene* pScene);
    

	WinSize getWindowSize();
	void setWindowSize(int width, int height){
		winSize = { (float)width, (float)height };
	}
};

#endif /* defined(__OpenGL_2D_Framework__Director__) */
