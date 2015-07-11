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
    //make sure release bitmap buffer allocation
    for (std::map<char, GlyphData>::iterator it=glyphMap.begin(); it!=glyphMap.end(); ++it){
        glDeleteTextures(1, &(it->second).texObj);
        delete[] it->second.bitmap_buffer;
    }
}

bool Font::initFont(std::string fontName, int fontSize){
    FT_Face face;
    std::string workingDir = Director::getInstance().getWorkingDir();
    std::string fontPath = workingDir + "/../Font/" + fontName;
    if(FT_New_Face(library, fontPath.c_str(), 0, &face)){
        cout << "Font::initFont Failed to load face. " << endl;
        return false;
    }
    
    size = fontSize;
    if(size == 0)
        size = 1;
    
    FT_Set_Pixel_Sizes(face, 0, size);
    
    this->lineSpace = (face->height >> 6);
    
    
    if(FT_Load_Char(face, 0xBC31, FT_LOAD_RENDER)){
        cout << "Failed to load char: " << (char)0xBC31 << endl;
    }
    
    
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

    //load all char for English only
    for(size_t i = ' '; i <= '~'; ++i){
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)){
            cout << "Failed to load char: " << (char)i << endl;
            continue;
        }
        
        FT_Glyph glyph;
        if(FT_Get_Glyph(face->glyph, &glyph)){
            cout << "Failed to get glyph" << endl;
            continue;
        }
        
        FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
        FT_GlyphSlot slot = face->glyph;
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
        //        FT_Bitmap& bitmap = slot->bitmap;
        FT_Bitmap bitmap = bitmap_glyph->bitmap;
        
        GlyphData gData;
        //update reference
        gData.bitmap_buffer = new unsigned char[bitmap.rows * bitmap.width * sizeof(unsigned char)];
        memcpy(gData.bitmap_buffer, bitmap.buffer, bitmap.rows * bitmap.width * sizeof(unsigned char));

        gData.c = i;
        gData.valid = true;
        gData.metrics = slot->metrics;
        
        GLuint textureObject;
        glGenTextures(1, &textureObject);
        glBindTexture(GL_TEXTURE_2D, textureObject);
        
        gData.texObj = textureObject;
        
        // set texture parameters. Linear and clamp to edge.
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, gData.bitmap_buffer);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        
        glyphMap.insert(std::pair<char, GlyphData>(gData.c, gData));
        FT_Done_Glyph(glyph);
    }
    
    FT_Done_Face(face);
    
    return true;
}

void Font::getGlyphDataFromChar(char c, GlyphData& gData){
    if(glyphMap.count(c)){
        gData = glyphMap.at(c);
    }
}

int Font::getLineSpace(){
    return lineSpace;
}