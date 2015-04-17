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

class Scene{
protected:
    SpriteManager *spriteManager;
private:
    //	std::map<int/*z order*/, Layer*> layerMap;
    virtual void exit();
public:
	Scene();
	virtual ~Scene();
//	Scene(Scene const& other);
//	void operator=(Scene const& other);
    
    virtual void init() = 0;
    virtual void keyPressed(int key) = 0;
    virtual void keyReleased(int key) = 0;
	virtual void update() = 0;
    virtual void render() = 0;
    
    void run();
    
    void addLayer(Layer* childLayer);
    void addSprite(SpriteObject* childSprite);
    void addParticleSystem();
    
};

#endif /* defined(__OpenGL_2D_Framework__Scene__) */
