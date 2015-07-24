//
//  SpriteSheet.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "SpriteSheet.h"
#include "Director.h"

SpriteSheet::SpriteSheet(){
    
}

SpriteSheet::~SpriteSheet(){
    if (texture){
        delete texture;
        texture = nullptr;
    }
}

void SpriteSheet::createSpriteSheet(std::string frameName, const char *textureName, const char *xmlFileName){
    if(!Director::getInstance().hasSpriteSheetFrameName(frameName)) {
        SpriteSheet* newSpriteSheet = new SpriteSheet();
        if(newSpriteSheet->initSpriteSheetWithXML(textureName, xmlFileName)){
            Director::getInstance().cacheSpriteSheet(frameName, newSpriteSheet);
        }
        else{
            cout << "[SYSTEM::ERROR] Failed to initialize sprite sheet." << endl;
            delete newSpriteSheet;
        }
    }
}

bool SpriteSheet::initSpriteSheetWithXML(std::string texturePath, std::string xmlFileName){
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> * root_node;
    // Read the xml file into a vector
    std::string wd = Director::getInstance().getWorkingDir();
    std::ifstream theFile (wd + "/../Texture/" + xmlFileName);
    if(theFile) {
        std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
        //close the file.
        theFile.close();
        buffer.push_back('\0');
        
        // Parse the buffer using the xml file parsing library into doc
        doc.parse<0>(&buffer[0]);
        
        // Find our root node
        root_node = doc.first_node("TextureAtlas");
        
        // Iterate over the brewerys
        textureName = texturePath;
        
        cout << "imageName: " << textureName << endl;
        
        this->w = atoi(root_node->first_attribute("width")->value());
        this->h = atoi(root_node->first_attribute("height")->value());
        
        cout << "width: " << this->w << endl;
        cout << "height: " << this->h << endl;
        
        this->texture = Texture::createTextureWithFile(texturePath);
        this->texture->getImageSize(this->w, this->h);
        
        for (rapidxml::xml_node<> * sprite_node = root_node->first_node("sprite"); sprite_node; sprite_node = sprite_node->next_sibling())
        {
            ImageEntry newEntry;
            //vertex coordinates
            newEntry.x = std::stof(std::string(sprite_node->first_attribute("x")->value()));
            newEntry.y = std::stof(std::string(sprite_node->first_attribute("y")->value()));
            newEntry.w = std::stof(std::string(sprite_node->first_attribute("w")->value()));
            newEntry.h = std::stof(std::string(sprite_node->first_attribute("h")->value()));
            //uv coordinates
            newEntry.uvOriginX = newEntry.x / (float)this->w;
            newEntry.uvOriginY = newEntry.y / (float)this->h;
            newEntry.uvEndX = (newEntry.x + newEntry.w) / (float)this->w;
            newEntry.uvEndY = (newEntry.y + newEntry.h) / (float)this->h;
            
            entryMap[std::string(sprite_node->first_attribute("n")->value())] = newEntry;
            
            cout
                 << "Sprite. name: " << sprite_node->first_attribute("n")->value()
                 << ",\t (x,y): (" << newEntry.x << ", " << newEntry.y
                 << "),\t (w,h): (" << newEntry.w << ", " << newEntry.h
                 << ")" <<
            endl;
        }
        return true;
    }
    else{
        cout << "[SYSTEM::ERROR] Sprite sheet XML data file \"" << xmlFileName << "\" does not exist" << endl;
        return false;
    }
}

const ImageEntry* SpriteSheet::getImageEntry(std::string imageName){
    auto it = entryMap.find(imageName);
    if(it != entryMap.end()){
        return &it->second;
    }
    else{
        return 0;
    }
}

Texture* SpriteSheet::getTexture(){
    return this->texture;
}