//
//  Scene.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Scene.h"
#include <GLFW/glfw3.h>

Scene::Scene():
window(0),
renderableObjectManager(0),
prevMousePos(glm::vec2()),
curMousePos(glm::vec2()),
canMoveCamera(false)
{
    cout << "Scene()" << endl;
    renderableObjectManager = new RenderableObjectManager();
}

Scene::~Scene(){
    cout << "~Scene()" << endl;
    exit();
}

void Scene::boundWindow(GLFWwindow *window){
    this->window = window;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    
    prevMousePos = glm::vec2(x, y);
    curMousePos = glm::vec2(x, y);
}

void Scene::update(){
    renderableObjectManager->update();
    
    //update layers
    for(auto it : layerMap){
        (it.second)->update();
    }
}

void Scene::render(){
    renderableObjectManager->render();
    
    //render layers
    for(auto it : layerMap){
        (it.second)->render();
    }
}

void Scene::run(){
//    Timer::getInstance().recordTime();
    update();
    render();
}

void Scene::addObject(std::string objectName, RenderableObject* object){
    renderableObjectManager->addObject(this, objectName, object, false);
}

void Scene::addLayer(Layer *childLayer){
    float layerZ;
    //get Z. If fails, set z as +1 from highest z to render to the most top of scene
    if(!childLayer->getZorder(layerZ)){
        if(layerMap.empty()){
            layerZ = 0;
        }
        else{
            auto end_it = layerMap.end();
            end_it--;
            float lastZ = end_it->first;
            layerZ = lastZ + 1;
            //assign z value because it didn't had one
            childLayer->setZorder(layerZ);
        }
    }
    childLayer->init();
    layerMap.insert(std::pair<int, Layer*>(layerZ, childLayer));
}

void Scene::exit(){
    if(renderableObjectManager)
        delete renderableObjectManager;
    
    for(auto it : layerMap){
        delete it.second;
    }
}

RenderableObjectManager* Scene::getRenderableObjectManager(){
    return renderableObjectManager;
}

void Scene::keyPressed(int key, int mods){
    for(auto it : layerMap){
        if((it.second)->isLayerInputListenable()){
			(it.second)->keyPressed(key, mods);
        }
    }
}

void Scene::keyReleased(int key, int mods){
    for(auto it : layerMap){
        if((it.second)->isLayerInputListenable()){
			(it.second)->keyReleased(key, mods);
        }
    }
}

void Scene::mouseButton(double x, double y, int button, int action){
    for(auto it : layerMap){
        if((it.second)->isLayerInputListenable()){
            (it.second)->mouseButton(x, y, button, action);
        }
    }
}

void Scene::mouseMove(double x, double y){
    for(auto it : layerMap){
        if((it.second)->isLayerInputListenable()){
            (it.second)->mouseMove(x, y);
        }
    }
}
