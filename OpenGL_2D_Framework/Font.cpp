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
        delete[] it->second.bitmap_buffer;
    }
}

bool Font::initFont(std::string fontName, int fontSize){
    FT_Face face;
    std::string workingDir = Director::getInstance().getWorkingDir();
    std::string fontPath = workingDir + "/../Font/" + fontName;
    if(FT_New_Face(library, fontPath.c_str(), 0, &face)){
        cout << "TextManager::Failed to load face. " << endl;
        return false;
    }
    
    size = fontSize;
    if(size == 0)
        size = 1;
    
    FT_Set_Pixel_Sizes(face, 0, size);
    
    this->lineSpace = (face->height >> 6);

    //load all char
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
//
//        gData.bitmap_width = bitmap.width; // copy texture width
//        gData.bitmap_rows = bitmap.rows; // copy texture height
//        gData.bitmap_left = slot->bitmap_left; // copy glyph width (pixels)
//        gData.bitmap_top = slot->bitmap_top; // copy glyph height (pixels)
//        gData.advance = glyph->advance; // copy the advance vector (note this isn't c++ vector, this is real vector)
        //        gData.c = (char)i; // set the character
        gData.c = i;
//        gData.size = size; // set the size
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
//        const unsigned char* texData = gData.bitmap_buffer;
//        unsigned int charLen = (unsigned int)strlen((char*)texData);
//        cout << "len = " << charLen << endl;
//        cout << strlen((char*)texData) << endl;
//        printf("%s\n", texData);
//        for(unsigned int i = 0; i<charLen; i++){
////            cout << texData[i] << endl;
//            printf("%i", (short)texData[i]);
//        }
//        unsigned char* temp;
//        int tw = (int)(gData.metrics.width >> 6);
//        int th = (int)(gData.metrics.height >> 6)/2;
//        cout << gData.c << ", w = " << tw << ", h = " << th << endl;
//        temp = new unsigned char[tw*th];
//        for(int i = 0; i<tw*th; i++){
//            temp[i] = 127;
////            temp[i+1] = 0;
////            temp[i+2] = 0;
//        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, gData.bitmap_buffer);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, temp);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        
        glyphMap.insert(std::pair<char,GlyphData>(gData.c, gData));
    }
    
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