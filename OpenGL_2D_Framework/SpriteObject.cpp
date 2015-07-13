//
//  SpriteObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteObject.h"

SpriteObject::SpriteObject() :
RenderableObject(),
w(0),
h(0),
type(NORMAL_TYPE)
{
    cout << "SpriteObject::SpriteObject()" << endl;
}

SpriteObject::~SpriteObject(){
	cout << "SpriteObject::Deleting...";
	cout << "Done." << endl;
}