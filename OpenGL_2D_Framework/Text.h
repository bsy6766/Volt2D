//
//  Text.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Text__
#define __OpenGL_2D_Framework__Text__

#include "TextObject.h"

class Text : public TextObject{
protected:
private:
    std::string text;

public:
    Text();
    ~Text();
    
    std::string getText();
    void setText(std::string);
    void computeVertexData();
    bool hasEmptyText();
};

#endif /* defined(__OpenGL_2D_Framework__Text__) */
