//
//  TextObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "TextObject.h"

TextObject::TextObject()
:visible(true),
vao(0),
vbo(0),
uvbo(0),
ibo(0),
translateMat(glm::mat4()),
rotateMat(glm::mat4()),
scaleMat(glm::mat4()),
modelMat(glm::mat4()),
position(glm::vec2(0, 0))
{
    
}

TextObject::~TextObject(){
    
}