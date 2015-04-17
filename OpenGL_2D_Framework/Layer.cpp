//
//  Layer.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Layer.h"

Layer::Layer(){
    cout << "Layer()" << endl;
    init();
}

Layer::~Layer(){
    cout << "~Layer()" << endl;
    exit();
}

void Layer::init(){
    cout << "Layer init()" << endl;
    spriteManager = new SpriteManager();
}

void Layer::update(){
    spriteManager->update();
}

void Layer::render(){
    spriteManager->render();
}

void Layer::setZorder(int z){
    this->z = z;
}

int Layer::getZorder(){
    return this->z;
}

void Layer::addSprite(SpriteObject *childSprite){
    spriteManager->addSprite(childSprite);
}

void Layer::exit(){
    if(spriteManager)
        delete spriteManager;
}