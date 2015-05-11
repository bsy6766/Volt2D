//
//  Font.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Font__
#define __OpenGL_2D_Framework__Font__

#include "CommonInclude.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype.h>
#include <ftglyph.h>
#include "Director.h"

class GlyphData {
public:
    bool valid;
    char c;     // the character of this glyph
//    int size;   // font size
//    
//    int bitmap_width;   // texture width
//    int bitmap_rows;    // texture height
    unsigned char *bitmap_buffer;   // texture data
//    FT_Vector advance;  // this variable contains the information of how much we need to move to the right from the last character
    FT_Glyph_Metrics metrics;
//    int bitmap_left;    // width of the glyph in pixels
//    int bitmap_top;     // height of the glyph in pixels
//    
    //Texture
    GLuint texObj;
};

class Font{
private:
    //Freetype.
    static FT_Library library;  //Made static so all manager can share one library.
    FT_GlyphSlot glyph;
    int size;

    std::map<char, GlyphData> glyphMap;
    
public:
    Font();
    ~Font();
    //read font file and generate glyph map.
    bool initFont(std::string fontName, int fontSize);
    void getGlyphDataFromChar(char c, GlyphData& gData);
};

#endif /* defined(__OpenGL_2D_Framework__Font__) */
