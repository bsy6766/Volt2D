//
//  Text.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Text.h"

Text::Text()
:TextObject()
{
    
}

Text::~Text(){
    
}

std::string Text::getText(){
    return this->text;
}

void Text::setText(std::string newText = ""){
    if (newText != text) {
        this->text = newText;
        computeVertexData();
    }
}

void Text::computeVertexData(){
    //Compute new vertex data based on new text
    if(hasEmptyText())
        return;
    
    //clear vertex data
    vertexData.clear();
    uvVertexData.clear();
    indicesData.clear();
    
    
}

bool Text::hasEmptyText(){
    return text.empty();
}

