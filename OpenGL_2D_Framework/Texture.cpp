//
//  Texture.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)

GLuint Texture::curBoundedTexture = -1;

Texture::Texture(GLenum textureTarget, const std::string& fileName):
		textureTarget(textureTarget), 
		fileName(fileName),
		data(NULL),
		width(0),
		height(0),
		channel(0){

}

Texture::~Texture(){
	glDeleteTextures(1, &textureObject);
    textureObject = 0;
    stbi_image_free(data);
    data = NULL;
}

void Texture::load(){
	//load and init the texture
    loadImage(fileName);
    initTexture();
}

void Texture::bind(GLenum textureUnit){
    glActiveTexture(textureUnit);	//NOTE: This is kind of useless if we are only going to use GL_TEXTRE0
    glBindTexture(textureTarget, textureObject);
    //keep track of the most lately bounded texture
    Texture::curBoundedTexture = this->textureObject;
    glUniform1i(textureLocation, 0);
}

void Texture::loadImage(const std::string& filePath){
    FILE *file = fopen(filePath.c_str(), "rb");
    //!!! now texture will be set to "missing texture" if failed to read file
    if(!file){
        //try again with default
        cout << "Failed to load texture on path = " << filePath << endl;
        const std::string defaultPath = "../Texture/default.png";
        file = fopen(defaultPath.c_str(), "rb");
        
        if(!file){
            //default is missing...what's happening?
            throw std::runtime_error("Default texture image file cannot be opened");
        }
    }
	/*
		stbi_load_from_file
		stb_image reads from top-left most in the image. 
		pixel data has y scanelines of x pixels

		But glTexImage2D reads pixal data from bottom left. See initTexture()
	*/
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
        
        std::memcpy(rowBuffer, row, rowSize);
        std::memcpy(row, oppositeRow, rowSize);
        std::memcpy(oppositeRow, rowBuffer, rowSize);
    }
    
    delete rowBuffer;
}

void Texture::initTexture(){
    glGenTextures(1, &textureObject);
	glBindTexture(textureTarget, textureObject);

    // set texture parameters. Linear and clamp to edge. 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
	assert(data != NULL);

	/*
		Apply texture from data.
		Unlikely stb_image, glTexImage2D's pixel data pointer starts from bottom left corner of the image.
		Subsequent pixel elements progress left to right, bottom to top.
		This is why we are flipping the image data.
	*/
    switch(channel){
        case Format_Grayscale:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
            break;
        case Format_GrayscaleAlpha:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
            break;
        case Format_RGB:
			//jpg
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case Format_RGBA:
			//Has alpha. ex)png
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

bool Texture::isThisTextureBounded(GLuint textureObject){
    return this->Texture::curBoundedTexture == textureObject;
}