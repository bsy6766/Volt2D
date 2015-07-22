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
    const static std::string wd;
    /**
     *  true if texture is loaded and ready to use
     */
    bool loaded;
    
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
    unsigned char* loadImage(int& width, int& height, int& channel, std::string postfix);
    
//    void loadImages(int size);
    void initTexture();
    void initTextureAtlas(int size);

	/**
	* Initialize texture.
	* Generate the texture and bind the texture object to GL_TEXTRE_2D
	*/
    void generateTexture(int width, int height, int channel, unsigned char* data = 0);
    GLenum getTextureType(int channel);
    
	/**
	* Flip image data
	* A data loaded by stb_image
	*/
    void flipImage(unsigned char* data);   //for stb_image
    
    /**
     *  Constructor for texture that already has texture object.
     */
    Texture(GLuint texObj, GLenum texTarget);
    
    /**
     * Texture class constructor
     * Initialize the texture object.
     * @param textureTarget a GLenum represents type of texture
     * @param fileName a const string represents the name of file(image)
     */
    Texture(GLenum textureTarget, const std::string& fileName);
    
    int findNearestPowTwo(unsigned int num);
public:
    /**
     *  Create texture with image file.
     *  @param fileName A texture image file name(path)
     *  @param textureTarget A OpenGL texture target. GL_TEXTURE_2D by default.
     */
    static Texture* createTextureWithFile(std::string fileName, GLenum textureTarget = GL_TEXTURE_2D);
    
    /**
     *  Create texture with series of files.
     *  @note All series of files must follow <file name>_<index> format.
     *  @param fileName Image file name
     *  @param size Number of files to load
     *  @param textureTarget A OpenGL texture target. GL_TEXTURE_2D by default.
     */
    static Texture* createTextureWithFiles(std::string fileName, int size, GLenum textureTarget = GL_TEXTURE_2D);
    
    /**
     *  Create texture with empty buffer with specific size
     *  @param textureObject A OpenGL texture object. Rejects non-positive.
     *  @param textureTarget A OpenGL texture target. GL_TEXTURE_2D by default.
     */
    static Texture* createWithTextureObject(GLuint textureObject, GLenum textureTarget = GL_TEXTURE_2D);

	/**
	* Texture class destructor
	* Release texture.
	*/
    ~Texture();
    
	/**
	* Bind texture.
	*/
    void bind(GLenum textureUnit);
    
    /**
     *  Get texture image size
     *  @param w Int for width
     *  @param h Int for height
     */
    void getImageSize(int &w, int &h);
    
    /**
     *  @return texture target. GL_TEXTURE_2D
     */
    GLenum getTextureTarget();
    
    /**
     *  @return Texture object
     */
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
     *  @return true if this object is currently bounded.
     */
    bool canBoundThisTexture();
};

#endif /* defined(__OpenGL_2D_Framework__Texture__) */
