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
window(0)
{
    cout << "Scene()" << endl;
}

Scene::~Scene(){
    cout << "~Scene()" << endl;
}

void Scene::bindWindow(GLFWwindow *window){
    this->window = window;
}

void Scene::update(){
    this->updateChild();
}

void Scene::render(){
    this->renderChild();
}

void Scene::addChild(Object *child){
    this->Object::addChild(child, this);
}

void Scene::keyPressed(int key, int mods){
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
