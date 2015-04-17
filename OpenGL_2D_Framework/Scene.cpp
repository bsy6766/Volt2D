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

void Scene::exit(){
    delete spriteManager;
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
    
}