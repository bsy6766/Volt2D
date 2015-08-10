//
//  Scene.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Scene.h"

/**
 *  Scene class is a root object for all objects that exists on the screen.
 *  Only one scene will exist one at a time on system (except scene transition)
 *  and only one scene will exsit through out all object heirarchies. In other words,
 *  Scene object can not have other Scene. 
 */

using namespace Volt2D;

Scene::Scene():
Object()
{}

Scene::~Scene(){}

void Scene::update(double dt){
    //update scene itself first.
    Object::update(dt);
    //then updat child
    this->updateChild(dt);
}

void Scene::render(){
    //Scene has nothing to render but children
    this->renderChild();
}

void Scene::addChild(Object *child){
    this->Object::addChild(child, this);
}

void Scene::keyPressed(int key, int mods){
    for (auto it = this->childObjMap.begin(); it != this->childObjMap.end();/*Manual increment*/){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            this->childObjMap.erase(it);
        }
        else{
            //Only Layer class receives key press callback.
            if(Layer* childLayer = dynamic_cast<Layer*>((it->second))){
                //check if layer can listen to input
                if(childLayer->isLayerInputListenable()){
                    childLayer->keyPressed(key, mods);
                }
            }
            ++it;
        }
    }
}

void Scene::keyReleased(int key, int mods){
    for (auto it = this->childObjMap.begin(); it != this->childObjMap.end();/*Manual increment*/){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            this->childObjMap.erase(it);
        }
        else{
            //Only Layer class receives key release callback.
            if(Layer* childLayer = dynamic_cast<Layer*>((it->second))){
                //check if layer can listen to input
                if(childLayer->isLayerInputListenable()){
                    childLayer->keyReleased(key, mods);
                }
            }
            ++it;
        }
    }
}

void Scene::mouseButton(double x, double y, int button, int action, int mods){
    for (auto it = this->childObjMap.begin(); it != this->childObjMap.end();/*Manual increment*/){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            this->childObjMap.erase(it);
        }
        else{
            //Only Layer class receives mouse click callback.
            if(Layer* childLayer = dynamic_cast<Layer*>((it->second))){
                //check if layer can listen to input
                if(childLayer->isLayerInputListenable()){
                    childLayer->mouseButton(x, y, button, action, mods);
                }
            }
            //else if not a Layer, do nothing.
            ++it;
        }
    }
}

void Scene::mouseMove(double x, double y){
    for (auto it = this->childObjMap.begin(); it != this->childObjMap.end();/*Manual increment*/){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            this->childObjMap.erase(it);
        }
        else{
            //Only Layer class receives mouse move callback.
            if(Layer* childLayer = dynamic_cast<Layer*>((it->second))){
                //check if layer can listen to input
                if(childLayer->isLayerInputListenable()){
                    childLayer->mouseMove(x, y);
                }
            }
            ++it;
        }
    }
}
