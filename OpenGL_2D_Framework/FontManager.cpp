//
//  FontManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "FontManager.h"

const std::string FontManager::defaultFontName = "arial.ttf";

FontManager::FontManager(){
    //add default font size of 10
    Font *defaultFont = new Font();
    defaultFont->initFont(defaultFontName, 50);
    fontMap.insert(std::pair<std::string, Font*>(defaultFontName, defaultFont));
}

FontManager::~FontManager(){
    cout << "~FontManager()" << endl;
    for (std::map<std::string, Font*>::iterator it=fontMap.begin(); it!=fontMap.end(); ++it)
        delete it->second;
}

void FontManager::addFont(std::string fontName, int fontSize){
    Font *newFont = new Font();
    //init newFont
    if(fontSize == 0)
        fontSize = 1;
    newFont->initFont(fontName, fontSize);
    fontMap.insert(std::pair<std::string, Font*>(fontName, newFont));
    
}

Font* FontManager::getFont(std::string fontName = defaultFontName){
    if(fontMap.count(fontName)){
        return fontMap.at(fontName);
    }
    else{
        return 0;
    }
}