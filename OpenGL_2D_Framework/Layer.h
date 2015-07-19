//
//  Layer.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Layer__
#define __OpenGL_2D_Framework__Layer__

#include "CommonInclude.h"
#include "Z_Float.h"
#include "Object.h"

/**
 *  @name Layer
 *  @brief A layer that can be added to scene
 *  @note Inherites object
 */

class Layer : public Object{
protected:
    /**
     *  true if this layer can listen inputs (key and mouse)
     */
    bool inputListenable;

public:
    Layer();
    virtual ~Layer();
    
    /**
     *  Pure virtual. This will be called when Layer ojbect is added to other object.
     */
    virtual void init() = 0;
    
    /**
     *  Pure virtual. This will be called when Layer object gets deleted.
     */
    virtual void exit() = 0;
    
    /**
     *  Update Layer. 
     *  Derived class can override this function but it must to call this at some point on their own update function.
     */
    virtual void update();
    
    /**
     *  Render the Layer
     *  Derived class can override this function but it must to call this at some point on their own render function.
     */
    virtual void render();

    /**
     *  Empty virtual class for key press input event
     *  @param key An int GLFW key value.
     *  @param mode An int GLFW modifier value.
     */
    virtual void keyPressed(int key, int mode){};
    
    /**
     *  Empty virtual class for key release input event
     *  @param key An int GLFW key value.
     *  @param mode An int GLFW modifier value.
     */
    virtual void keyReleased(int key, int mode){};
    
    /**
     *  Empty virtual class for mouse button click input event
     *  @param x A x mouse position where it clicked on screen
     *  @param y A y mouse position where it clicked on screen
     *  @param button An int GLFW value for type of button clicked
     *  @param action An int GLFW value for pressing, releasing or repeating
     */
    virtual void mouseButton(double x, double y, int button, int action){};
    
    /**
     *  Empty virtual class for mouse button click input event
     *  @param x A x mouse position where it moved on screen
     *  @param y A y mouse position where it moved on screen
     */
    virtual void mouseMove(double x, double y){};
    
    /**
     *  Add child ot this Layer.
     *  @param child A child object to add to this Layer
     */
    void addChild(Object* child);
    
    /**
     *  Check if this Layer object can listen input
     *  @return true if Layer can listen from input
     */
    bool isLayerInputListenable();
    
    /**
     *  Set Layer's listening mode.
     *  @param mode true to set Layer to listen inputs
     */
    void setInputListenable(bool mode);
};

#endif /* defined(__OpenGL_2D_Framework__Layer__) */
