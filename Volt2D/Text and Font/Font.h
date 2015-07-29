//
//  Font.h
//  Volt2D
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Font__
#define __Volt2D__Font__

#ifdef _WIN32
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype.h>
#elif __APPLE__
#include <freetype/ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#endif
#include <ftglyph.h>
#include "Director.h"

/**
 *  @class GlyphData
 *  @brief Contains each character's glyph metric and texture data in font.
 *  @note This class uses FreeType library.
 */
class GlyphData {
public:
    /**
     *  True if this character's data loaded
     */
    bool valid;
    
    /**
     *  Character of this data
     */
    char c;
    
    /**
     *  Glyph metrics that contains glyph data(width, height, advance, etc).
     */
    FT_Glyph_Metrics metrics;
    
    /**
     *  Top left texture coordinate for this char
     */
    glm::vec2 uvTopLeft;
    
    /**
     *  Bottom right texture coordinate for this char
     */
    glm::vec2 uvBotRight;
};

/**
 *  @class Font
 *  @brief Read TTF font file and loads data.
 */
class Font{
private:
    /**
     *  Texture object
     */
    GLuint textureObject;
    
    /**
     *  Texture atlas
     */
    Volt2D::Texture* textureAtlas;
    
    /**
     *  Freetype Library. Read library.
     */
    static FT_Library library;
    
    /**
     *  Font size
     */
    int size;
    
    /**
     *  Line space for this font.
     */
    int lineSpace;
    
    /**
     *  Texture atlas width
     */
    float texAtlasWidth;
    
    /**
     *  Texture atlas height
     */
    float texAtlasHeight;
    
    /**
     *  Glyph storage
     */
    std::map<char, GlyphData> glyphMap;
    
    //Private Constructor
    Font();
    
    /**
     *  Initialize font.
     *  @param fontName A font file name
     *  @param fontSize A font size
     *  @return true if successfully load font. Else, false.
     */
    bool initFont(std::string fontName, int fontSize);
public:
    /**
     *  Create font
     *  @param fontName TTF font name to load
     *  @param fontSize A font size to load. Higher number of size means higher resolution font texture.
     *  @return New font instance if success to initialize. Else, nullptr.
     */
    static Font* createTTF_Font(std::string fontName, int fontSize);
    
    //Desturctor
    ~Font();
    
    /**
     *  Get corresponding GlyphData to character
     *  @return GlyphData for char
     */
    GlyphData* getGlyphDataFromChar(char c);
    
    /**
     *  Get linespace of this font
     */
    int getLineSpace();
    
    /**
     *  Bind texture atlas to OpenGL
     */
    void bindTextTextureAtlas();
};

#endif /* defined(__Volt2D__Font__) */
