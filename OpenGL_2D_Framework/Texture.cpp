//
//  Texture.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Texture.h"
#include "Director.h"
#include "Program.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)

const std::string Texture::wd = Director::getInstance().getWorkingDir() + "/../Texture/";

GLuint Texture::curBoundedTexture = -1;

Texture::Texture(GLenum textureTarget, const std::string& fileName):
textureTarget(textureTarget),
fileName(fileName),
width(0),
height(0),
channel(0),
loaded(false),
textureLocation(-1)
{
    this->textureLocation = glGetUniformLocation(Director::getInstance().getProgramPtr()->getObject(), "tex");
}

Texture::Texture(GLuint texObj, GLenum texTarget):
textureObject(texObj),
textureTarget(texTarget),
textureLocation(-1)
{
    
    this->textureLocation = glGetUniformLocation(Director::getInstance().getProgramPtr()->getObject(), "tex");
}

Texture* Texture::createTextureWithFile(std::string fileName, GLenum textureTarget){
    Texture* newTexture = new Texture(textureTarget, fileName);
    newTexture->initTexture();
    return newTexture;
}

Texture* Texture::createTextureWithFiles(std::string fileName, int size, GLenum textureTarget){
    if(size <= 0){
        cout << "You can not create texture with 0 sized images." << endl;
        return nullptr;
    }
    else{
        Texture* newTexture = new Texture(textureTarget, fileName);
        newTexture->initTextureAtlas(size);
        return newTexture;
    }
}

Texture* Texture::createWithTextureObject(GLuint textureObject, GLenum textureTarget){
    Texture* newTexture = new Texture(textureObject, textureTarget);
    return newTexture;
}

Texture::~Texture(){
	glDeleteTextures(1, &textureObject);
    textureObject = 0;
}

void Texture::initTexture(){
    unsigned char* data = loadImage(this->width, this->height, this->channel, "");
    
    this->generateTexture(this->width, this->height, this->channel, data);

    if(data)
        stbi_image_free(data);
}

void Texture::initTextureAtlas(int size){
    unsigned char** datas[size];
    std::vector<int> widthList;
    std::vector<int> heightList;
    
    float widthSum = 0;
    float maxHeight = 0;
    //all channel must match
    int channel = -1;
    
    //* \todo Break down texture size if it's too wide
    
    for(int i = 0; i < size; i++){
        int width;
        int height;
        int newChannel;
        unsigned char* newData = loadImage(width, height, channel, std::to_string(i));
        
        widthList.push_back(width);
        heightList.push_back(height);
        
        //if channel was initialized ever
        if(channel != -1){
            //check if it's same
            assert(channel == newChannel);
        }
        else{
            channel = newChannel;
        }
        
        widthSum += (float)width;
        if(maxHeight < height)
            maxHeight = height;
        
        datas[i] = &newData;
    }
    
    this->channel = channel;
    
    //find neareast power of 2 for width
    
    this->width = this->findNearestPowTwo(widthSum);
    this->height = this->findNearestPowTwo(maxHeight);
    
    //generate empty texture
    this->generateTexture(this->width, this->height, this->channel);
    GLenum type = this->getTextureType(this->channel);
    
    assert(widthList.size() == size);
    assert(heightList.size() == size);
    assert(type >= 0);
    
    //sub tex image
    int x = 0;  //x offset
    for(int i = 0; i< size; i++){
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, widthList.at(i), heightList.at(i), type, GL_UNSIGNED_BYTE, datas[i]);
        x += widthList[i];
    }
    
    for(int i = 0 ;i <size; i++){
        stbi_image_free(datas[i]);
    }
}

int Texture::findNearestPowTwo(unsigned int num){
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;
    return num;
}

void Texture::bind(GLenum textureUnit){
    glActiveTexture(textureUnit);	//NOTE: This is kind of useless if we are only going to use GL_TEXTRE0
    glBindTexture(textureTarget, textureObject);
    //keep track of the most lately bounded texture
    Texture::curBoundedTexture = this->textureObject;
    glUniform1i(textureLocation, 0);
}

unsigned char* Texture::loadImage(int& width, int& height, int& channel, std::string postfix){
    std::string filePath = wd + this->fileName;
    if(!postfix.empty()){
        filePath += ("_" + postfix);
    }
    FILE *file = fopen(filePath.c_str(), "rb");
    //!!! now texture will be set to "missing texture" if failed to read file
    if(!file){
        //try again with default
        cout << "Failed to load texture on path = " << filePath << endl;
        const std::string defaultPath = "../Texture/default.png";
        file = fopen(defaultPath.c_str(), "rb");
        
        if(!file){
            //default is missing...what's happening?
            throw std::runtime_error("Failed to open default texture.");
        }
    }
	/*
		stbi_load_from_file
		stb_image reads from top-left most in the image. 
		pixel data has y scanelines of x pixels

		But glTexImage2D reads pixal data from bottom left. See initTexture()
	*/
    unsigned char* data = stbi_load_from_file(file, &width, &height, &channel, 0);
    flipImage(data);
    fclose(file);
    return data;
}

void Texture::flipImage(unsigned char* data){
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

void Texture::generateTexture(int width, int height, int channel, unsigned char* data){
    glGenTextures(1, &textureObject);
    glBindTexture(textureTarget, textureObject);
    
    // set texture parameters. Linear and clamp to edge.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    /*
     Apply texture from data.
     Unlikely stb_image, glTexImage2D's pixel data pointer starts from bottom left corner of the image.
     Subsequent pixel elements progress left to right, bottom to top.
     This is why we are flipping the image data.
     */
    switch(channel){
        case Format_Grayscale:
            glTexImage2D(this->textureTarget, 0, GL_RGBA8, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
            break;
        case Format_GrayscaleAlpha:
            glTexImage2D(this->textureTarget, 0, GL_RGBA8, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
            break;
        case Format_RGB:
            //jpg
            glTexImage2D(this->textureTarget, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case Format_RGBA:
            //Has alpha. ex)png
            glTexImage2D(this->textureTarget, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
    }
}

GLenum Texture::getTextureType(int channel){
    GLenum ret = -1;
    
    switch (channel) {
        case Format_Grayscale:
            ret = GL_LUMINANCE;
            break;
        case Format_GrayscaleAlpha:
            ret = GL_LUMINANCE_ALPHA;
            break;
        case Format_RGB:
            //jpg
            ret = GL_RGB;
            break;
        case Format_RGBA:
            //Has alpha. ex)png
            ret = GL_RGBA;
            break;
    }
    return ret;
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

bool Texture::canBoundThisTexture(){
    return this->Texture::curBoundedTexture != this->textureObject;
}