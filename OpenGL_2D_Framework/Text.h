//
//  Text.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Text__
#define __OpenGL_2D_Framework__Text__

//#include "TextObject.h"
#include "FontManager.h"
#include "RenderableObject.h"
#include <vector>

class Text : public RenderableObject{
protected:
private:
    std::string text;
    std::vector<std::string> splittedText;
    
    bool dirty;
    bool loaded;
    std::string fontName;
    int start;
    int end;
    
    void getMaxValues(Font* font, int& width, int& height,
                      std::vector<glm::vec2>& originList);
    void splitByNewLine();
    glm::vec3 fontColor;    //RGB
    
    //vertex trnslate matrix buffer object
//    GLuint vtbo;
    std::vector<glm::mat4> translationData;
    
public:
    Text();
    ~Text();
    
    void initText(std::string label, std::string fontName);
    
    std::string getText();
    void setText(std::string);
    bool hasEmptyText();
    void setColor(glm::vec3 textColor);
    
    //virtual
    virtual void computeVertexData();
    virtual void loadVertexData();
    virtual void render();
    
    enum TextAlign{
        ALIGN_LEFT = 0,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };
    
    TextAlign align;
    void setTextAlign(TextAlign mode);
    void setTextRange(int start, int end);
};

#endif /* defined(__OpenGL_2D_Framework__Text__) */
