//
//  Texture.h
//  Volt2D
//
//  Created by Seung Youp Baek on 11/4/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Texture__
#define __Volt2D__Texture__

#include <GL/glew.h>
#include <vector>
#include <stdio.h>
#include <stdexcept>
#include <map>
#include "Utility.hpp"
#include "stb_image.h"

namespace Volt2D{
class SpriteAnimation;

/**
 *  @struct Image
 *  @brief Holds basic info for loaded images
 */
struct Image{
    float width;
    float height;
    int channel;
    string name;
    float x;
};

/**
 *  @class Texture
 *  @brief Load and read texture image file and store.
 */
class Texture{
private:
    /**
     *  Can't create empty raw texture object
     */
    Texture() = delete;
    
    /**
     *  Path to texture root folder
     */
    const static std::string textureFolderPath;
    
    /**
     *  Stores Image datas.
     *  This will only handle 1 image
     *  \todo Force SpriteAnimation to use same size of images for each frame and remove Texture::imageDataMap. Just keep 1 for simplicity.
     */
    std::map<string, Image> imageDataMap;
    
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
     *  Load image.
     *  @param width Getter
     *  @param height Getter
     *  @param channel Getter
     *  @param postfix A postfix (numbering) that is used for sprite animation.
     */
    unsigned char* loadImage(int& width, int& height, int& channel, std::string postfix);
    
    /**
     *  Initialize texture. Uses GL_TEXTURE_2D.
     */
    void initTexture();
    
    //unused
//    /**
//     *  Initialzie texture atlas
//     *  @param size Number of texture files
//     */
//    void initTextureAtlas(int size);
    
    /**
     *  Initialize texture array.
     *  @param layer Size of layer for texture array.
     */
    void initTextureArray(int layer);

	/**
	* Initialize texture.
	* Generate the texture and bind the texture object to GL_TEXTRE_2D
	*/
    void generate2DTexture(int width, int height, int channel, unsigned char* data = NULL);
    
    /**
     *  Initailize texture array
     * Generate the texture and bind the texture object to GL_TEXTRE_2D_ARRAY
     */
    void generate2DArrayTexture(int width, int height, int size, int channel, unsigned char* data = NULL);
    
    /**
     *  Get texture type corresponding to channel
     *  @param channel A channel enum for texture type
     */
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
public:
    /**
     *  Create texture with image file.
     *  @param textureName A texture image file name(path)
     *  @param textureTarget A OpenGL texture target. GL_TEXTURE_2D by default.
     */
    static Texture* createTextureWithFile(std::string textureName, GLenum textureTarget = GL_TEXTURE_2D);
    
//    /**
//     *  Create texture with series of files.
//     *  @note All series of files must follow <file name>_<index> format.
//     *  @param fileName Image file name
//     *  @param size Number of files to load
//     *  @param textureTarget A OpenGL texture target. GL_TEXTURE_2D by default.
//     */
//    static Texture* createTextureWithFiles(std::string fileName, int size, GLenum textureTarget = GL_TEXTURE_2D);
    
    /**
     *  Create 2d texture array with fiels
     *  @note This uses GL_TEXTURE_2D_ARRAY
     *  @param fileName A file name
     *  @param size A number of texture files. Must be greater than 0
     *  @return New Texture instance if successfully initialize.
     */
    static Texture* create2DTextureArrayWithFiles(std::string textureName, int size);
    
    /**
     *  Create custom texture.
     *  @param width Width of desired texture. Must be power of 2 or it's forced to nearest next power of 2.
     *  @parma height Height of desired texture. Must be power of 2 or it's forced to nearest next power of 2.
     *  @param data A texture data.
     *  @param channel A texture channel(gray, jpg, png, etc type)
     */
    static Texture* createCustom2DTexture(unsigned int width, unsigned int height, unsigned char* data, int channel);
    
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
    void bind(GLenum textureUnit, int uniform = 0);
    
    /**
     *  Bind texture array
     */
    void bindArray();
    
    /**
     *  Get image size
     *  @param w Int for width
     *  @param h Int for height
     */
    void getImageSize(int &w, int &h);
    
    /**
     *  Get texture size.
     *  @param w Int for width
     *  @param h Int for height
     */
    void getTextureSize(int &w, int &h);
    
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
}   //namespace end

#endif /* defined(__Volt2D__Texture__) */
