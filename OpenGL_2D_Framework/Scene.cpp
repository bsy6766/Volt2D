//
//  Scene.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Scene.h"

Scene::Scene(){
    cout << "Scene()" << endl;
    spriteManager = new SpriteManager();
}

Scene::~Scene(){
    cout << "~Scene()" << endl;
    exit();
}

void Scene::update(){
    //update scene stuff first
    spriteManager->update();
    
    //update layers
    for(auto it : layerMap){
        (it.second)->update();
    }
}

void Scene::render(){
    //render scene stuff first
    spriteManager->render();
    
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

void Scene::addSprite(SpriteObject* childSprite){
    spriteManager->addSprite(childSprite);
}

void Scene::addLayer(Layer *childLayer){
//    int layerMapSize = layerMap.size();
    layerMap.insert(std::pair<int, Layer*>(childLayer->getZorder(), childLayer));
}

void Scene::exit(){
    delete spriteManager;
    
    for(auto it : layerMap){
        delete it.second;
    }
}
