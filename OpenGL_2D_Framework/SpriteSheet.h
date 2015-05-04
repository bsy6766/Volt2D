//
//  SpriteSheet.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteSheet__
#define __OpenGL_2D_Framework__SpriteSheet__

#include <rapidxml/rapidxml.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Texture.h"

class SpriteSheet{
private:
    std::string spriteName;
    int w;
    int h;
//    std::map<std::string, 
public:
    SpriteSheet();
    ~SpriteSheet();
    
    void initSpriteSheetWithXML(std::string xmlFileName);
};

#endif /* defined(__OpenGL_2D_Framework__SpriteSheet__) */
