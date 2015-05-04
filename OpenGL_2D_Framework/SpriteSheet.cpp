//
//  SpriteSheet.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(){
    
}

SpriteSheet::~SpriteSheet(){
    
}

void SpriteSheet::initSpriteSheetWithXML(std::string xmlFileName){
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> * root_node;
    // Read the xml file into a vector
    std::ifstream theFile ("../texture/sprite sheet/" + xmlFileName);
    std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
    theFile.close();
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);
    // Find our root node
    root_node = doc.first_node("TextureAtlas");
    // Iterate over the brewerys
    spriteName = root_node->first_attribute("imagePath")->value();
    
    std::cout << "imagePath: " << spriteName << std::endl;
    
    w = atoi(root_node->first_attribute("width")->value());
    h = atoi(root_node->first_attribute("height")->value());
    
    std::cout << "width: " << w << std::endl;
    std::cout << "height: " << h << std::endl;
    
    for (rapidxml::xml_node<> * sprite_node = root_node->first_node("sprite"); sprite_node; sprite_node = sprite_node->next_sibling())
    {
        std::cout << "Sprite. name: " << sprite_node->first_attribute("n")->value()
        << ", (x,y): (" << sprite_node->first_attribute("x")->value() << ", " << sprite_node->first_attribute("y")->value() << "), (w,h): (" << sprite_node->first_attribute("w")->value() << ", " << sprite_node->first_attribute("h")->value() << "), (pX, pY): (" << sprite_node->first_attribute("pX")->value() << ", " << sprite_node->first_attribute("pY")->value() << ")" << std::endl;
    }
    
    std::cout << "imagePath: " << root_node->first_attribute("imagePath")->value() << std::endl;
}