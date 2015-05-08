//
//  TextManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__TextManager__
#define __OpenGL_2D_Framework__TextManager__

#include "CommonInclude.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype.h>
#include <ftglyph.h>

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"

/// A rectangle at a certain point in space.
struct rect_t
{
    rect_t(float x, float y, int w, int h) : x(x), y(y), w(w), h(h) {}
    rect_t() : x(0.f), y(0.f), w(0), h(0) {}
    
    float x, y;
    int   w, h;
};

class GlyphData {
public:
    bool valid;
    char c;     // the character of this glyph
    int size;   // font size
    
    int bitmap_width;   // texture width
    int bitmap_rows;    // texture height
    unsigned char *bitmap_buffer;   // texture data
    FT_Vector advance;  // this variable contains the information of how much we need to move to the right from the last character
    int bitmap_left;    // width of the glyph in pixels
    int bitmap_top;     // height of the glyph in pixels
    
    //Texture
    GLuint texObj;
    GLuint vao;
    GLuint vbo;
    GLuint uvbo;
    GLuint ibo;
};

class TextManager{
private:
    //just preventing copying and assigning the manager class
    TextManager(TextManager const&);
    TextManager& operator=(TextManager const&);
    
    struct Glyph
    {
        // OpenGL texture handle for the bitmap
        uint32_t texture;
        
        // Dimensions and offsets.
        rect_t dim;
    };
    
    //Freetype.
    FT_Library library;  //Made static so all manager can share one library.
    FT_Face face;
    FT_GlyphSlot glyph;

    int originalSize;
    int currentSize;
    
    /**
     *  Get GlyphData for specific character.
     *  Iterate through glyph map and get GlyphData. Creates new GlyphData if it has never been created with before.
     *  @param char c A char value for specific GlyphData
     *  @param GlyphData& gData A GlyphData reference to get the data.
     */
    void getGlyphForChar(char c, GlyphData& gData);
    
    //TODO: Let the manager handle multiple size of glyphs
    std::map<char, GlyphData> glyphMap;
    std::map<char, Glyph> mp_glyphTextures;
    
    //OpenGL
    Program* prog;  //shader program pointer
    GLuint vao;
    GLuint vbo;
    GLuint uvbo;
    GLuint ibo;
    GLint fontCoords;
    GLuint textTex;
    
    std::vector<glm::vec3> vertexData;
    std::vector<glm::vec2> uvVertexData;
    std::vector<GLushort> indicesData;
    
    std::string currentText;
    
    float screenX = 0;
    float screenY = 0;
    float totalWidth = 0;
    
    std::string fontPath;
public:
    //Constructor and Destructor
    TextManager();
    ~TextManager();
    
    /**
     *  initialize FreeType Library.
     */
    void initFreeType();
    
    /**
     *  Load font with size.
     *  @param string fontPath A std string for font path
     *  @param GLuint size Size of font
     */
    bool loadFreeTypeFont(std::string fontPath, GLuint size);
    void loadFont(std::string path, int height);
    void renderLive(std::string text);
    void setText(std::string text);
    void renderText();
    void renderText(std::string text);
};

#endif /* defined(__OpenGL_2D_Framework__TextManager__) */
