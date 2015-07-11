//
//  Layer.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Layer__
#define __OpenGL_2D_Framework__Layer__

/**
 *  Layer can be inherited by other class or be the class it self
 */

//#include "SpriteManager.h"
#include "RenderableObjectManager.h"
#include "CommonInclude.h"
#include "Z_Float.h"

class Layer{
protected:
private:
    RenderableObjectManager* renderableObjectManager;
    Z_Float z;
    bool inputListenable;
public:
    Layer();
    ~Layer();
    
    virtual void init();
    virtual void update();
    virtual void render();
    virtual void exit();
    
    //for layer
    virtual void keyPressed(int key){};
    virtual void keyReleased(int key){};
    virtual void mouseButton(double x, double y, int button, int action){};
    virtual void mouseMove(double x, double y){};
    
    void setZorder(float z);
    bool getZorder(float& z);
    
    void addObject(std::string objectName, RenderableObject* object);
    
    bool isLayerInputListenable();
    void setInputListenable(bool mode);
};

#endif /* defined(__OpenGL_2D_Framework__Layer__) */
