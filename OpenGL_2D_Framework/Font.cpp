//
//  Font.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Font.h"

FT_Library Font::library = 0;

Font::Font(){
    if(!library){
        if( FT_Init_FreeType( &library ) ){
            library = 0;
            cout << "Failed to init FreeType." << endl;
            return;
        }
    }
}

Font::~Font(){
    //no need to release glyph storage anymore. They die together.
    glDeleteTextures(1, &this->textureObject);
    this->textureObject = 0;
}

Font* Font::createTTF_Font(std::string fontName, int fontSize){
    Font* newFont = new Font();
    if(newFont->initFont(fontName, fontSize)){
        return newFont;
    }
    else{
        delete newFont;
        return nullptr;
    }
}

bool Font::initFont(std::string fontName, int fontSize){
    //load the font with Freetype
    FT_Face face;
    std::string workingDir = Director::getInstance().getWorkingDir();
    std::string fontPath = workingDir + "/../Font/" + fontName;
    if(FT_New_Face(library, fontPath.c_str(), 0, &face)){
        cout << "Font::initFont Failed to load face. " << endl;
        return false;
    }
    
    //store font size
    size = fontSize;
    if(size == 0)
        size = 1;
    
    //Set font size. Bigger = Higher res texture
    FT_Set_Pixel_Sizes(face, 0, size);
    
    //Store linespace.
    this->lineSpace = (face->height >> 6);
    
    /*
    //한글 캐릭터 체크. '백' = 0xBC31
//    if(FT_Load_Char(face, 0xBC31, FT_LOAD_RENDER)){
//        cout << "Failed to load char: " << (char)0xBC31 << endl;
//    }
//    
    
    //korean
//    for(int i = 0xAC00; i <= 0xD7A3; i++){
//        if(FT_Load_Char(face, i, FT_LOAD_RENDER)){
//            cout << "Failed to load char: " << (char)i << endl;
//            continue;
//        }
//        
//        FT_Glyph glyph;
//        if(FT_Get_Glyph(face->glyph, &glyph)){
//            cout << "Failed to get glyph" << endl;
//            continue;
//        }
//    }
    */
    
    //Optimizing font texture.
    //iterate all chars and compute max width. (You can divide to make more even sized texture, but since it won't exceed max texture lenght, it's good)
    FT_GlyphSlot g = face->glyph;
    int widthSum = 0;
    int maxHeight = 0;
    
    //iterate over chars and compute width sum and max height
    for(size_t i = ' '; i < '~'; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            fprintf(stderr, "Loading character %c failed!\n", (char)i);
            continue;
        }
        
        widthSum += g->bitmap.width + 2; //2 pixels padding
        if(maxHeight < g->bitmap.rows){
            maxHeight = g->bitmap.rows;
        }
    }
    
    //find neareast power of 2 for width
    unsigned int uiWidth = Utility::findNearestPowTwo(widthSum);
    
    //find neareast power of 2 for height
    unsigned int uiHeight = Utility::findNearestPowTwo(maxHeight);
    
    //store texture size (power of 2)
    this->texAtlasWidth = (float)uiWidth;
    this->texAtlasHeight = (float)uiHeight;
    
    //allocate blank texture.
    glGenTextures(1, &this->textureObject);
    glBindTexture(GL_TEXTURE_2D, this->textureObject);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    //Generate empty texture.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texAtlasWidth, this->texAtlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    
    //Create texture instance
    this->textureAtlas = Texture::createWithTextureObject(this->textureObject, GL_TEXTURE_2D);
    
    //iterate over char map(space to wave dash)
    //x offset
    float x = 0;
    for(size_t i = ' '; i <= '~'; ++i){
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)){
            cout << "Failed to load char: " << (char)i << endl;
            continue;
        }
        
        //substitude pre allocated texture with each char's bitmap buffer.
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
        
        //compute uv and store
        GlyphData gData;
        gData.valid = true;
        gData.c = i;
        gData.metrics = g->metrics;
        
        //conmpute top left uv point.
        gData.uvTopLeft = glm::vec2(x / this->texAtlasWidth, 0);
        
        //move x by width
        x += g->bitmap.width;
        
        //compute bot right uv point
        gData.uvBotRight = glm::vec2(x / this->texAtlasWidth, (g->bitmap.rows / this->texAtlasHeight));
        
        //store in map
        glyphMap[gData.c] = gData;
        
        x += 2; //add padding at the end
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    
    //make sure release face.
    FT_Done_Face(face);
    
    return true;
}

GlyphData* Font::getGlyphDataFromChar(char c){
    auto it = glyphMap.find(c);
    if(it == glyphMap.end())
        return nullptr;
    else
        return &glyphMap[c];
}

int Font::getLineSpace(){
    return lineSpace;
}

void Font::bindTextTextureAtlas(){
    if(this->textureAtlas->canBoundThisTexture())
        this->textureAtlas->bind(GL_TEXTURE0);
}