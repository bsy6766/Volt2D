//
//  RenderableObjectManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/8/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__RenderableObjectManager__
#define __OpenGL_2D_Framework__RenderableObjectManager__

#include "CommonInclude.h"
#include <map>
#include <unordered_set>

class RenderableObject;
class Scene;

class RenderableObjectManager{
private:
    std::multimap<std::string, RenderableObject*> objNameLUT; //look up table
    std::multimap<float, RenderableObject*> objMap;
    
public:
    RenderableObjectManager();
    ~RenderableObjectManager();
    
    bool addObject(Scene* scenePtr, std::string objectName, RenderableObject* object, bool replace);
    bool removeObject(RenderableObject* object, bool deleteObject);
    bool removeObject(std::string objectName);
    void update();
    void render();
    void changeZ(RenderableObject* object, float z);
};

#endif /* defined(__OpenGL_2D_Framework__RenderableObjectManager__) */
