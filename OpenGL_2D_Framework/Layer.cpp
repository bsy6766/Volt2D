//
//  Layer.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Layer.h"

Layer::Layer():
inputListenable(false)
{
    cout << "Layer()" << endl;
    init();
}

Layer::~Layer(){
    cout << "~Layer()" << endl;
    exit();
}

void Layer::init(){
    cout << "Layer init()" << endl;
    renderableObjectManager = new RenderableObjectManager();
}

void Layer::update(){
    renderableObjectManager->update();
}

void Layer::render(){
    renderableObjectManager->render();
}

void Layer::setZorder(float z){
    this->z.setZ(z);
}

bool Layer::getZorder(float& z){
    if(this->z.dirty){
        this->z.getZ(z);
        return true;
    }
    else{
        return false;
    }
}

void Layer::addObject(std::string objectName, RenderableObject *object){
    renderableObjectManager->addObject(nullptr, objectName, object, false);
}

void Layer::exit(){
    if(renderableObjectManager)
        delete renderableObjectManager;
}

bool Layer::isLayerInputListenable(){
    return this->inputListenable;
}

void Layer::setInputListenable(bool mode){
    this->inputListenable = mode;
}