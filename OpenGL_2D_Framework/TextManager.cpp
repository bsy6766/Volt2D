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

