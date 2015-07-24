//
//  FontManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__FontManager__
#define __OpenGL_2D_Framework__FontManager__

#include "Font.h"
#include <map>
#include <string>
#include "Director.h"

/**
 *  @class FontManager
 *  @brief Manages font in system
 *  @note Supports TTF only. Singleton class. Has arial.ttf as default font.
 */
class FontManager{
protected:
private:
    //private Constructor
    FontManager();
    
    /**
     *  Stores font with name as an ID
     */
    std::map<std::string, Font*> fontMap;
public:
    /**
     *  Default font name
     */
    static const std::string defaultFontName;
    
    /**
     *  FontManager instance getter
     */
    static FontManager& getInstance(){
        static FontManager instance;
        return instance;
    }
    
    //destructor
    ~FontManager();
    //singleton
    FontManager(FontManager const&) = delete;
    void operator=(FontManager const&) = delete;
    
    /**
     *  Add font to FontManager.
     *  @param fontName Name of font file
     *  @param fontSize Size of font
     */
    void addFont(std::string fontName, int fontSize);
    
    /**
     *  Font getter.
     *  @param fontName Name of font to find
     */
    Font* getFont(std::string fontName);
};

#endif /* defined(__OpenGL_2D_Framework__FontManager__) */
