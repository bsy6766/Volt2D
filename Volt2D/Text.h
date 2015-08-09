//
//  Text.h
//  Volt2D
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Text__
#define __Volt2D__Text__

#include "FontManager.h"
#include "RenderableObject.h"
#include <vector>
#include "Color.h"

namespace Volt2D{
/**
 *  @class Text
 *  @brief Load string text and renders
 *  @note Requires Font
 */
class Text : public Volt2D::RenderableObject{
private:
    /**
     *  A string text to display
     */
    std::string text;
    
    /**
     *  A splitted text by new line
     */
    std::vector<std::string> splittedText;

    /**
     *  A font name to use for rendering and computing data
     */
    std::string fontName;
    
    /**
     *  First string index of text to render
     */
    int start;
    
    /**
     *  Last string index of text to render
     */
    int end;
    
    /**
     *  width of this object's size (max width)
     */
    int width;
    
    /**
     * height of this object's size (max height)
     */
    int height;
    
    /**
     *  Compute origin point of each line to compute vertex data
     */
    void computeOrigins(Font* font, std::vector<glm::vec2>& originList);
    
    /**
     *  Split text with new line
     */
    void splitByNewLine();
    
    /**
     *  A font color to render
     */
    glm::vec3 fontColor;
    
    /**
     *  Store translation matrix for each character from pivot point of objevct
     */
    std::vector<glm::mat4> translationData;
    
    //private constructor
    Text();
    
    /**
     *  Initialize Text.
     */
    void initText(std::string label, std::string fontName = "arial.tff");
public:
    /**
     *  Create Text object
     *  @param objectName An object name
     *  @param label A text to render
     *  @param fontName A font name to use. "arial.ttf" by default.
     */
    static Text* createText(std::string objectName, std::string label, std::string fontName = "arial.tff");
    ~Text();
    
    /**
     *  Get rendering text
     */
    std::string getText();
    
    /**
     *  Set rendering text
     */
    void setText(std::string);
    
    /**
     *  Check if text is empty styring
     */
    bool hasEmptyText();
    
    /**
     *  Set color of font.
     */
    void setColor(Color color);
    
    /**
     *  Compute vertex and indices
     *  @param width Quad width
     *  @param height Quad height
     */
    void computeVertexData();
    
    /**
     *  Load computed vertex.
     */
    void loadVertexData();
    
    /**
     *  Overrides's Object::render();
     *  Render object
     */
    virtual void render() override;
    
    /**
     *  Text align type
     */
    enum TextAlign{
        ALIGN_LEFT = 0,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };
    
    TextAlign align;
    /**
     *  Align setter
     */
    void setTextAlign(TextAlign mode);
    
    /**
     *  Range setter
     */
    void setTextRange(int start, int end);
};
}

#endif /* defined(__Volt2D__Text__) */
