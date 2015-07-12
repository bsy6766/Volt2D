//
//  Scene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Scene__
#define __OpenGL_2D_Framework__Scene__

//#define GLM_FORCE_RADIANS

#include "CommonInclude.h"
#include "RenderableObjectManager.h"
#include "Layer.h"

#include <map>
#include <glm/glm.hpp>


struct GLFWwindow;

class Scene{
protected:
    RenderableObjectManager* renderableObjectManager;
    GLFWwindow* window;
    glm::vec2 prevMousePos;
    glm::vec2 curMousePos;
private:
    std::multimap<int/*z order*/, Layer*> layerMap;
    std::map<std::string, bool> inputReceived;
    
public:
	Scene();
	virtual ~Scene();
//	Scene(Scene const& other);
//	void operator=(Scene const& other);
    
    bool canMoveCamera;
    
    virtual void init() = 0;
    virtual void exit();
    virtual void update();
    virtual void render();
    //these are input callback functions
	virtual void keyPressed(int key, int mods);
	virtual void keyReleased(int key, int mods);
    virtual void mouseButton(double x, double y, int button, int action);
    virtual void mouseMove(double x, double y);
    //these are the function that are used to implement own key and mouse handler. this runs every iteration
    virtual void injectKey() = 0;
    virtual void injectMouseMove() = 0;
    
    RenderableObjectManager* getRenderableObjectManager();
    
    void run();
    
    void boundWindow(GLFWwindow* window);
    
    void addLayer(Layer* childLayer);
    void addObject(std::string objectName, RenderableObject* object);
    
};

#endif /* defined(__OpenGL_2D_Framework__Scene__) */
