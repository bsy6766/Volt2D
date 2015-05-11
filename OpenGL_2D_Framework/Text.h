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
#include "FontManager.h"

class Text : public TextObject{
protected:
private:
    std::string text;
    bool dirty;
    bool loaded;
    std::string fontName;
    
    void getMaxValues(Font* font, int& width, int& height, glm::vec2& origin);
    glm::vec3 fontColor;    //RGB
    
public:
    Text();
    ~Text();
    
    void initText(std::string label, std::string fontName);
    
    std::string getText();
    void setText(std::string);
    void computeVertexData();
    bool hasEmptyText();
    void setColor(glm::vec3 textColor);
    virtual void render();
};

#endif /* defined(__OpenGL_2D_Framework__Text__) */
