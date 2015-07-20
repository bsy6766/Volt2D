//
//  Texture.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Texture__
#define __OpenGL_2D_Framework__Texture__

//#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <string>
#include <stdio.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <cstring>
#include "CommonInclude.h"
#include "stb_image.h"

/**
 *  @class Texture
 *  @brief Load and read texture image file and store.
 */
class Texture{
private:
    /**
     *  Placeholder to keep track the latest bounded texture object for optimization
     */
    static GLuint curBoundedTexture;
    
    /**
     *  OpenGL texture object;
     */
    GLuint textureObject;
    
    /**
     *  Texture target. Mostly GL_TEXTURE_2D
     */
    GLenum textureTarget;
    
    /**
     *  Texture location
     */
    GLint textureLocation;
    
    /**
     *  Texture image file name
     */
    std::string fileName;
    
    /**
     *  Image data loaded from stb_image.
     */
    unsigned char* data;
    
    /**
     *  Width and height of texture
     */
    GLsizei width, height;
    
    /**
     *  Image channel.
     */
    int channel;
    
	/**
	*	Loads image.
	* @param filePath a const string represents the path if file(image)
	*/
    void loadImage(const std::string& filePath);

	/**
	* Initialize texture.
	* Generate the texture and bind the texture object to GL_TEXTRE_2D
	*/
    void initTexture();

	/**
	* Flip image data
	* A data loaded by stb_image
	*/
    void flipImage();   //for stb_image
    
public:
	//don't implement. Prevent calling default constructor. Texture must be initialized, else it's useless
    Texture();	

	/**
	* Texture class constructor
	* Initialize the texture object.
	* @param textureTarget a GLenum represents type of texture
	* @param fileName a const string represents the name of file(image)
	*/
    Texture(GLenum textureTarget, const std::string& fileName);

	/**
	* Texture class destructor
	* Release texture.
	*/
    ~Texture();
    
	/**
	* Load texture.
	* Reads the image and initialize the texture
	*/
    void load();

	/**
	* Bind texture.
	*/
    void bind(GLenum textureUnit);
    
    //getter
    void getImageSize(int &w, int &h);
    GLenum getTextureTarget();
    GLint getTextureLocation();
    GLuint getObject();
    
    //Image format
    enum Format {
        Format_Grayscale = 1,			/**< one channel: grayscale */
        Format_GrayscaleAlpha = 2,		/**< two channels: grayscale and alpha */
        Format_RGB = 3,					/**< three channels: red, green, blue */
        Format_RGBA = 4					/**< four channels: red, green, blue, alpha */
    };
    
    /**
     *  Check if passed object matches currently bounded texture.
     *  Since querying OpenGL's setting is expensive, we are keep tracking texture by texture's object ID.
     *  @param textureObject A texture's object to check
     *  @return true if this object is currently bounded.
     */
    bool canBoundThisTexture(GLuint textureObject);
};

#endif /* defined(__OpenGL_2D_Framework__Texture__) */
