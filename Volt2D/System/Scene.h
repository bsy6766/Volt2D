//
//  Scene.h
//  Volt2D
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Scene__
#define __Volt2D__Scene__

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
    /** Protected constructor */
    Scene();
public:
    /** Virtual desturctor */
    virtual ~Scene();
    
    /**
     *  Initialize function.
     *  All class that inherite Scene class must declare init.
     *  @note init() gets called when the scene get load up
     */
    virtual void init() = 0;
    
    /** Entering function. Called when Scene enters the screen */
    virtual void onEnter() = 0;
    
    /** Exit func. This called when Director deletes old scenes */
    virtual void exit() = 0;
    
    /** Implements Object::update() */
    virtual void update(double dt);
    
    /** Impelments Object::render() */
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
     *  Add child wrapper.
     *  This calls Object::addChild(Object*, Object*, bool)
     */
    void addChild(Volt2D::Object* child);
};
}

#endif /* defined(__Volt2D__Scene__) */
