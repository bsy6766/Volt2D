//
//  Director.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Director__
#define __OpenGL_2D_Framework__Director__

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

struct winSize{
	float w;
	float h;
};

class Director{
protected:
	//no one derives from this class!
private:
	winSize WinSize;

	//Scene queue. FIFO. Only the first element gets updated and rendered.
	//First element = current scene
	std::queue<Scene*> sceneQueue;

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
	void initApp();

	/**
	*	Create window with size and title
	*	Default window size is 100 x x100
	*	Default window title is noName
	*/
	bool createWindow(int screenWidth, int screenHeight, std::string& windowTitle);

	/**
	*	Run.
	*	Director runs the scene. 
	*	Game loop goes here
	*/
	void run();

	void stop();

	/**
	*	Push scene to director's scene queue
	*/
	void pushScene(Scene* pScene);

	/**
	*	Load the next scene, pop the current one and set the next scene to current scene
	*/
	void transitionToNextScene();

	winSize getWindowSize();
	void setWindowSize(int screenWidth, int screenHeight);
};

#endif /* defined(__OpenGL_2D_Framework__Director__) */
