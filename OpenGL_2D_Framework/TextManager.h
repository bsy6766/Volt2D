//
//  TextManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__TextManager__
#define __OpenGL_2D_Framework__TextManager__

#include <list>
#include "TextObject.h"

class TextManager{
private:
    std::list<TextObject*> textObjectList;
public:
    TextManager();
    ~TextManager();
    
    void render();
    void addText(TextObject* textObj);
};

#endif /* defined(__OpenGL_2D_Framework__TextManager__) */