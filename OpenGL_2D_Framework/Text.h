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
#include <vector>

class Text : public TextObject{
protected:
private:
    std::string text;
    std::vector<std::string> splittedText;
    
    bool dirty;
    bool loaded;
    std::string fontName;
    
    void getMaxValues(Font* font, int& width, int& height,
                      std::vector<glm::vec2>& originList);
    void splitByNewLine();
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
    
    enum TextAlign{
        ALIGN_LEFT = 0,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };
    
    TextAlign align;
};

#endif /* defined(__OpenGL_2D_Framework__Text__) */
