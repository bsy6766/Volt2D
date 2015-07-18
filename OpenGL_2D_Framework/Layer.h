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
//#include "RenderableObjectManager.h"
#include "CommonInclude.h"
#include "Z_Float.h"
#include "Object.h"

class Layer : public Object{
protected:
private:
//    RenderableObjectManager* renderableObjectManager;
    bool inputListenable;
public:
    Layer();
    ~Layer();
    
    virtual void init();
    virtual void update();
    virtual void render();
    virtual void exit();
    
    //for layer
	virtual void keyPressed(int key, int mods){};
	virtual void keyReleased(int key, int mods){};
    virtual void mouseButton(double x, double y, int button, int action){};
    virtual void mouseMove(double x, double y){};
    
//    void addObject(std::string objectName, RenderableObject* object);
    void addChild(Object* child);
    
    bool isLayerInputListenable();
    void setInputListenable(bool mode);
};

#endif /* defined(__OpenGL_2D_Framework__Layer__) */
