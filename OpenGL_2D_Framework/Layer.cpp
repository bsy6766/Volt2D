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
//    cout << "[SYSTEM::INFO] Creating Layer" << endl;
}

Layer::~Layer(){
//    cout << "[SYSTEM::INFO] Releasing Layer" << endl;
}

void Layer::update(double dt){
    this->updateChild(dt);
}

void Layer::render(){
    this->renderChild();
}

void Layer::addChild(Object *child){
    this->Object::addChild(child, this);
}

bool Layer::isLayerInputListenable(){
    return this->inputListenable;
}

void Layer::setInputListenable(bool mode){
    this->inputListenable = mode;
}