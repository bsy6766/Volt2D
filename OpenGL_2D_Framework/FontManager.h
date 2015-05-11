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
#include "CommonInclude.h"
#include "Director.h"

class FontManager{
protected:
private:
    FontManager();
    
    std::map<std::string, Font*> fontMap;
public:
    static const std::string defaultFontName;
    
    static FontManager& getInstance(){
        static FontManager instance;
        return instance;
    }
    
    ~FontManager();
    FontManager(FontManager const&) = delete;
    void operator=(FontManager const&) = delete;
    
    void addFont(std::string fontName, int fontSize);
    Font* getFont(std::string fontName);
};

#endif /* defined(__OpenGL_2D_Framework__FontManager__) */
