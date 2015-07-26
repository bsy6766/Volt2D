//
//  Color.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/14/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Color__
#define __OpenGL_2D_Framework__Color__

#include "CommonInclude.hpp"

/**
 *  @class Color
 *  @brief Color class with preset colors
 *  @note Java's enum class-ish class.
 */
class Color{
private:    
    /**
     *  Red
     */
    float r;
    
    /**
     *  Green
     */
    float g;
    
    /**
     *  Blue
     */
    float b;
    
    /**
     *  Alpha(opacity)
     */
    float a;
    
    //private constructor with color value
    Color(float r, float g, float b, float a);
    
public:
    static Color createWithRGB(float r, float g, float b);
    /**
     *  Create color with specific RGBA value.
     *  @return Color instance
     */
    static Color createWithRGBA(float r, float g, float b, float a);
   
    /**
     *  Get red color value
     *  @return Red color value for this color
     */
    float getR();
    
    /**
     *  Get green color value
     *  @return Green color value for this color
     */
    float getG();
    
    /**
     *  Get blue color value
     *  @return Blue color value for this color
     */
    float getB();
    
    /**
     *  Get alpha value
     *  @return Alpha color value for this color
     */
    float getA();
    
    /**
     *  Set red color
     *  @param r Red Color value
     */
    void setR(float r);
    
    /**
     *  Set green color
     *  @param g Green Color value
     */
    void setG(float g);
    
    /**
     *  Set blue color
     *  @param b Blue Color value
     */
    void setB(float b);
    
    /**
     *  Set alpha color
     *  @param a Alpha Color value
     */
    void setA(float a);
    
    /**
     *  Get color as RGB
     *  @return glm::vec3 value of RGB
     */
    glm::vec3 getRGB();
    
    /**
     *  Get color as RGBA
     *  @return glm::vec4 value of RGBA
     */
    glm::vec4 getRGBA();
    
    /**
     *  == operator
     */
    bool friend operator==(const Color& lhs, const Color& rhs){
        return (lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b == rhs.b) && (lhs.a == rhs.a);
    }
    
    Color friend operator-(const Color& lhs, const Color& rhs){
        float r = lhs.r - rhs.r;
        Utility::wrapColor(r);
        float g = lhs.g - rhs.g;
        Utility::wrapColor(g);
        float b = lhs.b - rhs.b;
        Utility::wrapColor(b);
        float a = lhs.a - rhs.a;
        Utility::wrapColor(a);
        return Color::createWithRGBA(r, g, b, a);
    }
    
    Color friend operator+(const Color& lhs, const Color& rhs){
        float r = lhs.r + rhs.r;
        Utility::wrapColor(r);
        float g = lhs.g + rhs.g;
        Utility::wrapColor(g);
        float b = lhs.b + rhs.b;
        Utility::wrapColor(b);
        float a = lhs.a + rhs.a;
        Utility::wrapColor(a);
        return Color::createWithRGBA(r, g, b, a);
    }
    
    /// @{
    /// @name Static constant for built-in color
    static const Color MAROON;
    static const Color DARKRED;
    static const Color BROWN;
    static const Color FIREBRICK;
    static const Color CRIMSON;
    static const Color RED;
    static const Color TOMATO;
    static const Color CORAL;
    static const Color INDIANRED;
    static const Color LIGHTCORAL;
    static const Color DARKSALMON;
    static const Color SALMON;
    static const Color LIGHTSALMON;
    static const Color ORANGERED;
    static const Color DARKORANGE;
    static const Color ORANGE;
    static const Color GOLD;
    static const Color DARKGOLDENROD;
    static const Color GOLDENROD;
    static const Color PALEGOLDENROD;
    static const Color DARKKHAKI;
    static const Color KHAKI;
    static const Color OLIVE;
    static const Color YELLOW;
    static const Color YELLOWGREEN;
    static const Color DARKOLIVEGREEN;
    static const Color OLIVEDRAB;
    static const Color LAWNGREEN;
    static const Color CHARTREUSE;
    static const Color GREENYELLOW;
    static const Color DARKGREEN;
    static const Color GREEN;
    static const Color FORESTGREEN;
    static const Color LIME;
    static const Color LIMEGREEN;
    static const Color LIGHTGREEN;
    static const Color PALEGREEN;
    static const Color DARKSEAGREEN;
    static const Color MEDIUMSPRINGGREEN;
    static const Color SPRINGGREEN;
    static const Color SEAGREEN;
    static const Color MEDIUMAQUAMARINE;
    static const Color MEDIUMSEAGREEN;
    static const Color LIGHTSEAGREEN;
    static const Color DARKSLATEGRAY;
    static const Color TEAL;
    static const Color DARKCYAN;
    static const Color AQUA;
    static const Color CYAN;
    static const Color LIGHTCYAN;
    static const Color DARKTURQUOISE;
    static const Color TURQUOISE;
    static const Color MEDIUMTURQUOISE;
    static const Color PALETURQUOISE;
    static const Color AQUAMARINE;
    static const Color POWDERBLUE;
    static const Color CADETBLUE;
    static const Color STEELBLUE;
    static const Color CORNFLOWERBLUE;
    static const Color DEEPSKYBLUE;
    static const Color DODGERBLUE;
    static const Color LIGHTBLUE;
    static const Color SKYBLUE;
    static const Color LIGHTSKYBLUE;
    static const Color MIDNIGHTBLUE;
    static const Color NAVY;
    static const Color DARKBLUE;
    static const Color MEDIUMBLUE;
    static const Color BLUE;
    static const Color ROYALBLUE;
    static const Color BLUEVIOLET;
    static const Color INDIGO;
    static const Color DARKSLATEBLUE;
    static const Color SLATEBLUE;
    static const Color MEDIUMSLATEBLUE;
    static const Color MEDIUMPURPLE;
    static const Color DARKMAGENTA;
    static const Color DARKVIOLET;
    static const Color DARKORCHID;
    static const Color MEDIUMORCHID;
    static const Color PURPLE;
    static const Color THISTLE;
    static const Color PLUM;
    static const Color VIOLET;
    static const Color MAGENTA;
    static const Color ORCHID;
    static const Color MEDIUMVIOLETRED;
    static const Color PALEVIOLETRED;
    static const Color DEEPPINK;
    static const Color HOTPINK;
    static const Color LIGHTPINK;
    static const Color PINK;
    static const Color ANTIQUEWHITE;
    static const Color BEIGE;
    static const Color BISQUE;
    static const Color BLANCHEDALMOND;
    static const Color WHEAT;
    static const Color CORNSILK;
    static const Color LEMONCHIFFON;
    static const Color LIGHTGOLDENRODYELLOW;
    static const Color LIGHTYELLOW;
    static const Color SADDLEBROWN;
    static const Color SIENNA;
    static const Color CHOCOLATE;
    static const Color PERU;
    static const Color SANDYBROWN;
    static const Color BURLYWOOD;
    static const Color TAN;
    static const Color ROSYBROWN;
    static const Color MOCCASIN;
    static const Color NAVAJOWHITE;
    static const Color PEACHPUFF;
    static const Color MISTYROSE;
    static const Color LAVENDERBLUSH;
    static const Color LINEN;
    static const Color OLDLACE;
    static const Color PAPAYAWHIP;
    static const Color SEASHELL;
    static const Color MINTCREAM;
    static const Color SLATEGRAY;
    static const Color LIGHTSLATEGRAY;
    static const Color LIGHTSTEELBLUE;
    static const Color LAVENDER;
    static const Color FLORALWHITE;
    static const Color ALICEBLUE;
    static const Color GHOSTWHITE;
    static const Color HONEYDEW;
    static const Color IVORY;
    static const Color AZURE;
    static const Color SNOW;
    static const Color BLACK;
    static const Color DIMGRAY;
    static const Color GRAY;
    static const Color DARKGRAY;
    static const Color SILVER;
    static const Color LIGHTGRAY;
    static const Color GAINSBORO;
    static const Color WHITESMOKE;
    static const Color WHITE;
    static const Color NONE;
    ///@}
};

#endif /* defined(__OpenGL_2D_Framework__Color__) */
