//
//  Texture.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Texture.h"
#include "Director.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)

using namespace Volt2D;

const std::string Texture::textureFolderPath = Volt2D::Director::getInstance().getWorkingDir() + "/../Texture/";

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
    this->textureLocation = glGetUniformLocation(Volt2D::Director::getInstance().getProgramPtr()->getObject(), "tex");
}

Texture::Texture(GLuint texObj, GLenum texTarget):
textureObject(texObj),
textureTarget(texTarget),
textureLocation(-1)
{
    
    this->textureLocation = glGetUniformLocation(Volt2D::Director::getInstance().getProgramPtr()->getObject(), "tex");
}

Texture* Texture::createTextureWithFile(std::string textureName, GLenum textureTarget){
    Texture* newTexture = new Texture(textureTarget, textureName);
    newTexture->initTexture();
    return newTexture;
}

//unused
//Texture* Texture::createTextureWithFiles(std::string fileName, int size, GLenum textureTarget){
//    if(size <= 0){
//        cout << "You can not create texture with 0 sized images." << endl;
//        return nullptr;
//    }
//    else{
//        Texture* newTexture = new Texture(textureTarget, fileName);
//        newTexture->initTextureAtlas(size);
//        return newTexture;
//    }
//}

Texture* Texture::create2DTextureArrayWithFiles(std::string textureName, int size){
    if(size <= 0){
        cout << "You can not create texture with 0 sized images." << endl;
        return nullptr;
    }
    else{
        //force to use GL_TEXTURE_2D_ARRAY
        Texture* newTexture = new Texture(GL_TEXTURE_2D_ARRAY, textureName);
        newTexture->initTextureArray(size);
        return newTexture;
    }
}

Texture* Texture::createCustom2DTexture(unsigned int width, unsigned int height, unsigned char *data, int channel){
    if(!Volt2D::isPowerOfTwo(width)){
        width = Volt2D::findNearestPowTwo(width);
    }
    
    if(!Volt2D::isPowerOfTwo(height)){
        height = Volt2D::findNearestPowTwo(height);
    }
    
    Texture* newCustomTexture = new Texture(GL_TEXTURE_2D, std::string());
    newCustomTexture->generate2DTexture(width, height, channel, data);
    
    return newCustomTexture;
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
    
    this->generate2DTexture(this->width, this->height, this->channel, data);

    if(data)
        stbi_image_free(data);
}

/*
//unused
//void Texture::initTextureAtlas(int size){
//    std::vector<unsigned char*> datas;
//    std::vector<int> widthList;
//    std::vector<int> heightList;
//    
//    float widthSum = 0;
//    float maxHeight = 0;
//    //all channel must match
//    int channel = -1;
//    
//    // ß\todo Break down texture size if it's too wide
//    
//    for(int i = 0; i < size; i++){
//        int width;
//        int height;
//        int newChannel;
//        unsigned char* newData = loadImage(width, height, newChannel, std::to_string(i+1));
//        
//        widthList.push_back(width);
//        heightList.push_back(height);
//        
//        //if channel was initialized ever
//        if(channel != -1){
//            //check if it's same
//            assert(channel == newChannel);
//        }
//        else{
//            channel = newChannel;
//        }
//        
//        widthSum += (float)width + 2; //padding = 2 pixels
//        if(maxHeight < height)
//            maxHeight = height;
//        
//        datas.push_back(newData);
//    }
//    
//    this->channel = channel;
//    
//    //find neareast power of 2 for width
//    
//    this->width = this->findNearestPowTwo(widthSum);
//    this->height = this->findNearestPowTwo(maxHeight);
//    
//    //generate empty texture
//    this->generate2DTexture(this->width, this->height, this->channel);
//    GLenum type = this->getTextureType(this->channel);
//    
//    assert(widthList.size() == size);
//    assert(heightList.size() == size);
//    assert(type >= 0);
//    
//    //sub tex image
//    int x = 0;  //x offset
//    for(int i = 0; i< size; i++){
//        //update texture
//        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, widthList.at(i), heightList.at(i), type, GL_UNSIGNED_BYTE, datas.at(i));
//        //update Image data
//        Image& image = imageDataMap.find(this->fileName + "_" + std::to_string(i))->second;
//        image.x = x;
//        
//        //move x
//        x += (widthList[i] + 2); //including padding
//    }
//    
//    for(auto it : datas){
//        stbi_image_free(it);
//    }
//    
//}
 */

void Texture::initTextureArray(int layer){
    std::vector<unsigned char*> datas;
    
    //all channel must match
    int channel = -1;
    
    //* \todo Break down texture size if it's too wide
    int width = -1;
    int height = -1;
    for(int i = 0; i < layer; i++){
        int newChannel;
        unsigned char* newData = loadImage(width, height, newChannel, std::to_string(i+1));
        flipImage(newData);
        
        //if channel was initialized ever
        if(channel != -1){
            //check if it's same
            assert(channel == newChannel);
        }
        else{
            channel = newChannel;
        }

        datas.push_back(newData);
    }
    
    this->channel = channel;
    
    assert(width >= 0);
    assert(height >= 0);
    //find neareast power of 2 for width
    
    this->width = Volt2D::findNearestPowTwo(width);
    this->height = Volt2D::findNearestPowTwo(height);
    
    //generate empty texture
    this->generate2DArrayTexture(this->width, this->height, layer, this->channel);
    GLenum type = this->getTextureType(this->channel);

    assert(type >= 0);
    
    for(int i = 0; i< layer; i++){
        //update texture
        glTexSubImage3D(this->textureTarget,    //GL_TEXTURE_2D_ARRay
                        0,                      //level(mipmap)
                        0, 0, i,                //x,y,z offset
                        width,            //texture width
                        height,           //texture height
                        1,                      //texture depth
                        type,                //format
                        GL_UNSIGNED_BYTE,       //type
                        datas.at(i)
                        );
    }
    
    for(auto it : datas){
        stbi_image_free(it);
    }
    
    this->textureLocation = glGetUniformLocation(Volt2D::Director::getInstance().getProgramPtr()->getObject(), "texArray");
}

void Texture::bind(GLenum textureUnit, int uniform){
    glActiveTexture(textureUnit);	//NOTE: This is kind of useless if we are only going to use GL_TEXTRE0
    glBindTexture(textureTarget, textureObject);
    //keep track of the most lately bounded texture
    Texture::curBoundedTexture = this->textureObject;
    glUniform1i(textureLocation, uniform);
}

void Texture::bindArray(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(this->textureTarget, this->textureObject);
    Texture::curBoundedTexture = this->textureObject;
    glUniform1i(textureLocation, 0);
}

unsigned char* Texture::loadImage(int& width, int& height, int& channel, std::string postfix){
    string fileNameCopy = this->fileName;
    
    if(!postfix.empty()){
        string delimeter = ".";
        size_t extIndex = fileNameCopy.find(delimeter);
        
        assert(extIndex <= fileNameCopy.size());
        
        string absFileName = fileNameCopy.substr(0, extIndex);
        string fileExt = fileNameCopy.substr(extIndex);
        fileNameCopy = absFileName;
        fileNameCopy += ("_" + postfix + fileExt);
    }
    std::string filePath = this->textureFolderPath + fileNameCopy;
    
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
    
    Image newImageData;
    newImageData.width = (float)width;
    newImageData.height = (float)height;
    newImageData.channel = channel;
    newImageData.name = this->fileName;
    
    this->imageDataMap[this->fileName] = newImageData;
    
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

void Texture::generate2DTexture(int width, int height, int channel, unsigned char* data){
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

void Texture::generate2DArrayTexture(int width, int height, int layerSize, int channel, unsigned char* data){
    glGenTextures(1, &this->textureObject);
    glBindTexture(this->textureTarget, this->textureObject);
    
    glTexParameteri(this->textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(this->textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    switch (channel) {
        case Format_Grayscale:
            glTexImage3D(this->textureTarget, 1, GL_RGBA8, width, height, layerSize, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
            break;
        case Format_GrayscaleAlpha:
            glTexImage3D(this->textureTarget, 1, GL_RGBA8, width, height, layerSize, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
            break;
        case Format_RGB:
            //jpg
            glTexImage3D(this->textureTarget, 1, GL_RGBA8, width, height, layerSize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case Format_RGBA:
            //Has alpha. ex)png
//            glTexImage3D(this->textureTarget, 1, GL_RGBA8, width, height, layerSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glTexStorage3D(this->textureTarget, 1, GL_RGBA8, width, height, layerSize);
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
    Image* imgPtr = &imageDataMap.begin()->second;
    w = (int)imgPtr->width;
    h = (int)imgPtr->height;
}

void Texture::getTextureSize(int &w, int &h){
    w = this->width;
    h = this->height;
}

GLenum Texture::getTextureTarget(){
    return textureTarget;
}

bool Texture::canBoundThisTexture(){
    return this->Texture::curBoundedTexture != this->textureObject;
}