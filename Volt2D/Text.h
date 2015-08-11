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
#include "Color.h"

#include <vector>

namespace Volt2D {
    /**
     *  @name TEXT_ALIGN
     *  @brief Enum class for text align
     */
    enum class TEXT_ALIGN{
        ALIGN_LEFT = 0,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };
    
    /**
     *  @name TEXT_TYPE
     *  @brief Enum class for text rendering type
     */
    enum class TEXT_TYPE{
        STATIC = 0,
        DYNAMIC
    };
    
    /**
     *  @name Text
     *  @brief Render text
     */
    class Text : public Volt2D::RenderableObject{
    private:
        /** Text label */
        std::string label;
        
        /** Text label spliited by new line */
        std::vector<std::string> splittedLabel;
        
        /** TTF font name */
        std::string font;
        
        /** Text align */
        TEXT_ALIGN align;
        
        /** Text color */
        Color color;
        
        /** Text type */
        TEXT_TYPE type;
        
        /** vertex position buffer object */
        GLuint vpbo;
        
        /** Translation mat to vec3 for all chars */
        std::vector<glm::vec3> translationData;
        
        /** Max width of vertex */
        float maxWidth;
        /** Total height of vertex */
        float totalHeight;
        
        /** Split label by \n char */
        void splitByNewLine();
        
        /** Clear all data and compute new vertices */
        bool computeVertices();
        
        /** Compute origins for current label */
        void computeOrigins(Font* font, std::vector<glm::vec2>& originList);
        
        /** Load and bind data */
        void loadVertexData();
        
        /** Orphan existing buffer objects and rebind */
        void subVertexData();
        
        /** Private constructor */
        Text();
        
        /** Initialize Text */
        bool initText(std::string label, std::string font, TEXT_ALIGN align, Color color, TEXT_TYPE type);
    public:
        /** Create text */
        static Text* create(std::string objectName, std::string label, std::string font, TEXT_ALIGN align, Color color, TEXT_TYPE type);
        
        /** Desturctor */
        ~Text();
        
        /** Set color of text. This doesn't change text vertices */
        void setColor(Color color);
        
        /** Change text label. Only dynamic type can perform this */
        bool setLabel(std::string label);
        
        bool setAlign(TEXT_ALIGN align);
        
        /** Get current label */
        std::string getLabel();
        
        /** Render. Override Object::render() */
        void render() override;
    };
}

#endif /* defined(__Volt2D__Text__) */
