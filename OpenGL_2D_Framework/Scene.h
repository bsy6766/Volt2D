//
//  Scene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Scene__
#define __OpenGL_2D_Framework__Scene__

#include "Object.h"
#include "Layer.h"

#include <map>

namespace Volt2D{
/**
 *  @class Scene
 *  @brief A Scene class. Only 1 scene can be run in Director.
 */
class Scene : public Volt2D::Object{
protected:
    
public:
	Scene();
    virtual ~Scene();
    
    /**
     *  Initialize function.
     *  All class that inherite Scene class must declare init.
     *  @note init() gets called when the scene get load up
     */
    virtual void init() = 0;
    
    /**
     *  Exit func. This called when Director deletes old scenes.
     */
    virtual void exit() = 0;
    
    /**
     *  Implement Object::update().
     */
    virtual void update(double dt);
    
    /**
     *  Impelment Object::render().
     */
    virtual void render();
    
    /**
     *  Forwarding key pressed callback from Director.
     *  If you override this, make sure to call Scene::keyPressed(int, int) to foward again to child layers.
     */
    virtual void keyPressed(int key, int mods);
    
    /**
     *  Forwarding key released callback from Director.
     *  If you override this, make sure to call Scene::keyReleased(int, int) to foward again to child layers.
     */
    virtual void keyReleased(int key, int mods);
    
    /**
     *  Forwarding mouse button callback from Director.
     *  If you override this, make sure to call Scene::mouseButton(double, double, int, int) to foward again to child layers.
     */
    virtual void mouseButton(double x, double y, int button, int action);
    
    /**
     *  Forwarding mouse move callback from Director.
     *  If you override this, make sure to call Scene::mouseMove(double, double) to foward again to child layers.
     */
    virtual void mouseMove(double x, double y);
    
    /**
     *  Pure virtual of key input.
     *  This function will be called on every iteration
     */
    virtual void injectKey() = 0;
    
    /**
     *  Pure virtual of mouse input.
     *  This function will be called on every iteration
     */
    virtual void injectMouseMove() = 0;
    
    /**
     *  Bind current window to this scene to get key and mouse input.
     *  Can be used for Scene::injectKey() and Scene::injectMouseMove()
     */
//    void bindWindow(GLFWwindow* window);
    
    /**
     *  Add child wrapper.
     *  This calls Object::addChild(Object*, Object*, bool)
     */
    void addChild(Volt2D::Object* child);
};
}

#endif /* defined(__OpenGL_2D_Framework__Scene__) */
