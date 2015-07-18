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
Object(),
window(0),
//renderableObjectManager(0),
prevMousePos(glm::vec2()),
curMousePos(glm::vec2()),
canMoveCamera(false)
{
    cout << "Scene()" << endl;
//    renderableObjectManager = new RenderableObjectManager();
}

Scene::~Scene(){
    cout << "~Scene()" << endl;
    exit();
}

void Scene::bindWindow(GLFWwindow *window){
    this->window = window;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    
    prevMousePos = glm::vec2(x, y);
    curMousePos = glm::vec2(x, y);
}

void Scene::update(){
    this->updateChild();
}

void Scene::render(){
    this->renderChild(this->modelMat);
}

void Scene::run(){
//    Timer::getInstance().recordTime();
    update();
    render();
}

void Scene::addChild(Object *child){
    this->Object::addChild(child, this);
}

//void Scene::addObject(std::string objectName, RenderableObject* object){
//    renderableObjectManager->addObject(this, objectName, object, false);
//}
//
//void Scene::addLayer(Layer *childLayer){
//    float layerZ;
//    //get Z. If fails, set z as +1 from highest z to render to the most top of scene
//    if(!childLayer->getZorder(layerZ)){
//        if(layerMap.empty()){
//            layerZ = 0;
//        }
//        else{
//            auto end_it = layerMap.end();
//            end_it--;
//            float lastZ = end_it->first;
//            layerZ = lastZ + 1;
//            //assign z value because it didn't had one
//            childLayer->setZorder(layerZ);
//        }
//    }
//    childLayer->init();
//    layerMap.insert(std::pair<int, Layer*>(layerZ, childLayer));
//}

void Scene::exit(){
}

void Scene::keyPressed(int key, int mods){
//    for(auto it : layerMap){
//        if((it.second)->isLayerInputListenable()){
//			(it.second)->keyPressed(key, mods);
//        }
    //    }
    for (auto it = this->childObjMap.begin(); it != this->childObjMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            this->childObjMap.erase(it);
        }
        else{
            //call mouse move
            if(Layer* childLayer = dynamic_cast<Layer*>((it->second))){
                if(childLayer->isLayerInputListenable())
                    childLayer->keyPressed(key, mods);
            }
            ++it;
        }
    }
}

void Scene::keyReleased(int key, int mods){
//    for(auto it : layerMap){
//        if((it.second)->isLayerInputListenable()){
//			(it.second)->keyReleased(key, mods);
//        }
    //    }
    for (auto it = this->childObjMap.begin(); it != this->childObjMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            this->childObjMap.erase(it);
        }
        else{
            //call mouse move
            if(Layer* childLayer = dynamic_cast<Layer*>((it->second))){
                if(childLayer->isLayerInputListenable())
                    childLayer->keyReleased(key, mods);
            }
            ++it;
        }
    }
}

void Scene::mouseButton(double x, double y, int button, int action){
//    for(auto it : layerMap){
//        if((it.second)->isLayerInputListenable()){
//            (it.second)->mouseButton(x, y, button, action);
//        }
    //    }
    for (auto it = this->childObjMap.begin(); it != this->childObjMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            this->childObjMap.erase(it);
        }
        else{
            //call mouse move
            if(Layer* childLayer = dynamic_cast<Layer*>((it->second))){
                if(childLayer->isLayerInputListenable())
                    childLayer->mouseButton(x, y, button, action);
            }
            ++it;
        }
    }
}

void Scene::mouseMove(double x, double y){
//    for(auto it : layerMap){
//        if((it.second)->isLayerInputListenable()){
//            (it.second)->mouseMove(x, y);
//        }
//    }
    for (auto it = this->childObjMap.begin(); it != this->childObjMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            this->childObjMap.erase(it);
        }
        else{
            //call mouse move
            if(Layer* childLayer = dynamic_cast<Layer*>((it->second))){
                if(childLayer->isLayerInputListenable())
                    childLayer->mouseMove(x, y);
            }
            ++it;
        }
    }

}
