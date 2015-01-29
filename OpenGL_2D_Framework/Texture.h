//
//  Texture.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Texture__
#define __OpenGL_2D_Framework__Texture__

#include <GL/glew.h>
#include <string>
#include <stdio.h>
#include <stdexcept>
#include <glm/glm.hpp>

#include "stb_image.h"

using namespace std;

class Texture{
private:
    GLuint textureObject;
    GLenum textureTarget;
    GLint textureLocation;
    
    std::string fileName;
    unsigned char* data;
    GLsizei width, height;
    
    int channel;
    
    void loadImage(const string& filePath);
    void initTexture();
    void flipImage();   //for stb_image
    
public:
    Texture();
    Texture(GLenum _textureTarget, const std::string& _fileName);
    ~Texture();
    
    bool load();
    void bind(GLenum textureUnit);
    
    //getter
    void getImageSize(int &w, int &h);
    GLenum getTextureTarget();
    GLint getTextureLocation();
    GLuint getObject();
    
    //Image format
    enum Format {
        Format_Grayscale = 1, /**< one channel: grayscale */
        Format_GrayscaleAlpha = 2, /**< two channels: grayscale and alpha */
        Format_RGB = 3, /**< three channels: red, green, blue */
        Format_RGBA = 4 /**< four channels: red, green, blue, alpha */
    };
};

#endif /* defined(__OpenGL_2D_Framework__Texture__) */
