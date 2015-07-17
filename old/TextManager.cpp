//
//  TextManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "TextManager.h"
#include "Text.h"

TextManager::TextManager(){
    
}

TextManager::~TextManager(){
    
}

//void TextManager::addText(TextObject *textObj){
void TextManager::addText(Text *textObj){
    if(textObj)
        textObjectList.push_back(textObj);
}

void TextManager::render(){
    if(!textObjectList.empty())
        for(auto it : textObjectList){
            it->render();
        }
}

void TextManager::update(){
    //iterating through list. update and delete nulls(0)
    for (std::list<Text *>::const_iterator ci = textObjectList.begin(); ci != textObjectList.end();){
        //if pointer is null, delete pointer and remove from the list.
        if((*ci) == 0){
            delete (*ci);
            ci = textObjectList.erase(ci);  //returns next element
        }
        else{
            (*ci)->update();
            ++ci;
        }
    }
}