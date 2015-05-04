//
//  Scene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Scene__
#define __OpenGL_2D_Framework__Scene__

#include "CommonInclude.h"
#include "SpriteManager.h"
#include "Layer.h"

#include <map>
#include <glm/glm.hpp>

class GLFWwindow;

class Scene{
protected:
    SpriteManager *spriteManager;
    GLFWwindow* window;
    glm::vec2 prevMousePos;
    glm::vec2 curMousePos;
private:
    std::multimap<int/*z order*/, Layer*> layerMap;
    virtual void exit();
public:
	Scene();
	virtual ~Scene();
//	Scene(Scene const& other);
//	void operator=(Scene const& other);
    
    virtual void init() = 0;
    virtual void update();
    virtual void render();
    virtual void keyPressed(int key) = 0;
    virtual void keyReleased(int key) = 0;
    virtual void mouseButton(int button, int action) = 0;
    virtual void mouseMove(double x, double y) = 0;
    virtual void injectKey() = 0;
    virtual void injectMouseMove() = 0;
    
    void run();
    
    void boundWindow(GLFWwindow* window);
    
    void addLayer(Layer* childLayer);
    void addSprite(SpriteObject* childSprite);
//    void addParticleSystem();
    
};

#endif /* defined(__OpenGL_2D_Framework__Scene__) */
