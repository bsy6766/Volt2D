//
//  Texture.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)

Texture::Texture(){
    textureObject = 0;
    data = NULL;
}

Texture::Texture(GLenum _textureTarget, const std::string& _fileName){
    textureTarget = _textureTarget;
    fileName = _fileName;
}

Texture::~Texture(){
    textureObject = 0;
//    stbi_image_free(data);
    data = NULL;
}

bool Texture::load(){
    loadImage(fileName);
    initTexture();
    return true;
}

void Texture::bind(GLenum textureUnit){
    glActiveTexture(textureUnit);
    glBindTexture(textureTarget, textureObject);
    glUniform1i(textureLocation, 0);
}

void Texture::loadImage(const string& filePath){
    FILE *file = fopen(filePath.c_str(), "rb");
    //!!! now texture will be set to "missing texture" if failed to read file
    if(!file){
        //try again with default
        const string defaultPath = "../Texture/default.png";
        file = fopen(defaultPath.c_str(), "rb");
        
        if(!file){
            //default is missing...what's happening?
            throw runtime_error("Default texture image file cannot be opened");
        }
    }
    
    data = stbi_load_from_file(file, &width, &height, &channel, 0);
    flipImage();
    fclose(file);
}

void Texture::flipImage(){
    unsigned long rowSize = channel * width;
    unsigned char* rowBuffer = new unsigned char[rowSize];
    unsigned halfRows = height / 2;
    
    for(unsigned rowIdx = 0; rowIdx < halfRows; ++rowIdx){
        unsigned char* row = data + ((rowIdx * width + 0) * channel);
        unsigned char* oppositeRow = data + (((height - rowIdx - 1) * width + 0) * channel);
        
        memcpy(rowBuffer, row, rowSize);
        memcpy(row, oppositeRow, rowSize);
        memcpy(oppositeRow, rowBuffer, rowSize);
    }
    
    delete rowBuffer;
}

void Texture::initTexture(){
    glGenTextures(1, &textureObject);
    glBindTexture(GL_TEXTURE_2D, textureObject);
    
    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    switch(channel){
        case Format_Grayscale:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
            break;
        case Format_GrayscaleAlpha:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
            break;
        case Format_RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case Format_RGBA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
    }
}

GLuint Texture::getObject(){
    return textureObject;
}

void Texture::getImageSize(int &w, int &h){
    w = width;
    h = height;
}

GLenum Texture::getTextureTarget(){
    return textureTarget;
}
