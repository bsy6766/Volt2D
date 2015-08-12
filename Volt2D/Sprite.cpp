
//
//  Sprite.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 11/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

/**
 *  Sprite class
 *  
 *  Sprite class is the most basic object that exists in this system.
 *  Since the system is targeted to 2D, Sprite will only use 2 coordinates x and y
 *  but because the underlying implementation is 3D, it is always possible to
 *  apply z coordinate to Sprite object.
 *
 *  Like said above, x and y coordinate is the primary coordinate that Sprite object
 *  uses and initial creation will only set these two coordinate and use shared z
 *  coordinate for vertices data. However, like other object, z coordinate in vertices
 *  merely represent the origin state/position of object and it won't affect 
 *  rendering order, which is z-order.
 *
 *  Sprite class originally created to have it's own texture object for rendering,
 *  but now it supports sprite sheet. If sprite is created with sprite sheet, then
 *  sprite object will not release the sprite sheet texture on destruction while 
 *  normal sprite object does.
 */

#include "Sprite.h"
#include "Director.h"

using namespace Volt2D;

Sprite::Sprite():
RenderableObject(),
texture(0),
textureWidth(0),
textureHeight(0)
{
    
}

Sprite::~Sprite(){
    //if Sprite uses SpriteSheet, just release reference to texture pointer
	if (useSpriteSheet){
        texture = nullptr;
	}
    //else, delete texture if Sprite is using own texture.
    else{
        if(this->texture != nullptr){
            delete this->texture;
            this->texture = nullptr;
        }
    }
    //just making sure. Set action running flag to false
    actionRunning = false;
}

Sprite* Sprite::create(std::string objectName, std::string fileName, GLenum textureTarget){
    //Create new Sprite. This creation will use own texture.
    Sprite* newSprite = new Sprite();
    if(newSprite->initTexture(fileName, textureTarget)){
        //successfully initialized sprite with texture.
        //set the object name and return the instance pointer.
        newSprite->setName(objectName);
        return newSprite;
    }
    else{
        //failed to initialize. Delete instance and return null pointer
        delete newSprite;
        return nullptr;
    }
}

Sprite* Sprite::createWithSpriteSheet(std::string objectName, std::string frameName, std::string imageFileName){
    //Creating sprite with SpriteSheet.
    //First check if system has the SpriteSheet
    if(Volt2D::Director::getInstance().hasSpriteSheetFrameName(frameName)) {
        //if exists, check if we can get the SpriteSheet and check if it's valid
        if(SpriteSheet* const ssPtr = Volt2D::Director::getInstance().getSpriteSheet(frameName)){
            //and get the specific sprite's texture image infos.
            const ImageEntry* ie = ssPtr->getImageEntry(imageFileName);
            //if image data instance is valid,
            if(ie){
                //Create instance.
                Sprite* newSprite = new Sprite();
                //get the sprite sheet texture pointer
                Texture* ssTex = ssPtr->getTexture();
                newSprite->setName(objectName);
                newSprite->initSpriteWithSpriteSheet(ie, ssTex);
                return newSprite;
            }
            //Image data instance is not valid. nullptr?
            else{
                cout << "[SYSTEM::ERROR] \"" << imageFileName << "\" does not exists in \"" << frameName << "\" SpriteSheet." << endl;
                return nullptr;
            }
        }
        //sprite sheet is not valid. nullptr?
        else{
            cout << "[SYSTEM::ERROR] SpriteSheet called \"" << frameName << "\" does not exists in the system." << endl;
            return nullptr;
        }
    }
    //Sprite sheet not found
    else{
        cout << "[SYSTEM::ERROR] SpriteSheet called \"" << frameName << "\" does not exists in the system." << endl;
        return nullptr;
    }
}

Sprite* Sprite::createCustom(std::string objectName, Volt2D::Texture *texture, float width, float height){
    Sprite* newSprite = new Sprite();
    newSprite->setName(objectName);
    newSprite->initCustom(texture, width, height);
    return newSprite;
}

bool Sprite::initTexture(const std::string& fileName, GLenum textureTarget){
    this->texture = Texture::createTextureWithFile(fileName, textureTarget);
    
    //the only case failing is that when it fails to read texture.
    if(texture == nullptr){
        return false;
    }
    //store texture size
    this->texture->getTextureSize(this->textureWidth, this->textureHeight);
    
    //compute vertex data and load to vao
    computeVertexData();
    loadVertexData();
    
    //init bouding box
    this->boundingBox = new Volt2D::BoundingBox(-(float)this->textureWidth/2.0f,
                                        -(float)this->textureHeight/2.0f,
                                        (float)this->textureWidth/2.0f,
                                        (float)this->textureHeight/2.0f);
    return true;
}

void Sprite::initCustom(Volt2D::Texture *texture, float width, float height){
    this->texture = texture;
//    this->texture->getTextureSize(this->textureWidth, this->textureHeight);
    //redirect desired size of quad.
    this->textureWidth = width;
    this->textureHeight = height;
    
    computeVertexData();
    loadVertexData();
    
    this->boundingBox = new Volt2D::BoundingBox(-(float)this->textureWidth/2.0f,
                                                -(float)this->textureHeight/2.0f,
                                                (float)this->textureWidth/2.0f,
                                                (float)this->textureHeight/2.0f);
}

void Sprite::initSpriteWithSpriteSheet(const ImageEntry* ie, Texture* texture){
    //store texture for binding
    this->texture = texture;
    
    //store texture(the portion of using image) size
    this->textureWidth = ie->w;
    this->textureHeight = ie->h;
    
    //set the flag
    this->useSpriteSheet = true;
    
    //compute vertices.
    computeVertices();
    //for texturer coordinate, use Image data's uv positions
    computeTextureCoordinates(
                              glm::vec2(ie->ImageEntry::uvOriginX,
                                        ie->ImageEntry::uvOriginY),
                              glm::vec2(ie->ImageEntry::uvEndX,
                                        ie->ImageEntry::uvEndY)
                              );
    //indices.
    computeIndices();
    //load to vao
    loadVertexData();
    
    //init bounding box
    this->boundingBox = new Volt2D::BoundingBox(-(float)this->textureWidth/2.0f,
                                        -(float)this->textureHeight/2.0f,
                                        (float)this->textureWidth/2.0f,
                                        (float)this->textureHeight/2.0f);
}

void Sprite::render(){
    if(!visible) return;
    if(!texture) return;
    
    //Camera
    glUseProgram(progPtr->getObject());
    
    if(this->texture->canBoundThisTexture()){
        texture->bind(GL_TEXTURE0);
    }
    
    const glm::mat4 cameraMat = Volt2D::Director::getInstance().getProjectiveViewMatrix();
    matrixUniformLocation("cameraMat", cameraMat);
    
    glm::mat4 parentMat = glm::mat4();
    if(this->parent)
        parentMat = this->parent->getTransformMat();
    
    matrixUniformLocation("parentMat", parentMat);
    matrixUniformLocation("modelMat", modelMat);
    matrixUniformLocation("rotateMat", rotateMat);
    matrixUniformLocation("translateMat", translateMat);
    matrixUniformLocation("scaleMat", scaleMat);
    floatUniformLocation("opacity", opacity);
    
    //bind vertex array.
    glBindVertexArray(this->bufferObject.vao);
    
    //enable attribs
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
    
    //draw based on indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Sprite::computeVertexData(){
    computeVertices();
    computeTextureCoordinates();
    computeIndices();
}

void Sprite::computeVertices(){
    float width = (float)this->textureWidth / Volt2D::SCREEN_TO_WORLD_SCALE;
    float height = (float)this->textureHeight / Volt2D::SCREEN_TO_WORLD_SCALE;
    
    this->Object::scaledWidth = width;
    this->Object::scaledHeight = height;
    
    /*
     
     Quad
     Vertex								UV coordinate
					(width, height)						(1,1)
     *------------*						*------------*
     |		     |						|			 |
     |			 |						|			 |
     |	 		 |						|			 |
     |			 |					  v	|			 |
     *------------*						*------------*
     (0,0)								(0,0)   u
     
     */
    vertexData.push_back(glm::vec3(-(width/2), -(height/2), Volt2D::GLOBAL_Z_VALUE));	//bot left
    vertexData.push_back(glm::vec3(-(width/2), height/2, Volt2D::GLOBAL_Z_VALUE));		//top left
    vertexData.push_back(glm::vec3(width/2, -(height/2), Volt2D::GLOBAL_Z_VALUE));		//bot right
    vertexData.push_back(glm::vec3(width/2, height/2, Volt2D::GLOBAL_Z_VALUE));			//top right
}

void Sprite::computeTextureCoordinates(glm::vec2 origin, glm::vec2 end){
    //origin is top left corner. origin
    //left x = origin.x
    //right x = end.x
    //top y = origin.y
    //bot y = end.y
    origin.y = 1.0 - origin.y;
    end.y = 1.0 - end.y;
    
    if(useSpriteSheet) {
        uvVertexData.push_back(glm::vec2(origin.x, end.y));	//bot left
        uvVertexData.push_back(origin);	//top left
        uvVertexData.push_back(end);	//bot right
        uvVertexData.push_back(glm::vec2(end.x, origin.y));	//top right
    }
    else{
        uvVertexData.push_back(glm::vec2(0, 0));	//bot left
        uvVertexData.push_back(glm::vec2(0, 1));	//top left
        uvVertexData.push_back(glm::vec2(1, 0));	//bot right
        uvVertexData.push_back(glm::vec2(1, 1));	//top right
    }
}

void Sprite::computeIndices(){
    //NOTE: if you don't flip the texture and want to handle with UV coordinate, go on this order
    //top left->bot left->top right->bot right
    
    indicesData.push_back(0);
    indicesData.push_back(1);
    indicesData.push_back(2);
    indicesData.push_back(1);
    indicesData.push_back(2);
    indicesData.push_back(3);
}

void Sprite::loadVertexData(){
    //generate vertex array object and bind it
    glGenVertexArrays(1, &this->bufferObject.vao);
    glBindVertexArray(this->bufferObject.vao);
    
    //generate vertex buffer object for quad
    glGenBuffers(1, &this->bufferObject.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate texture uv buffer object for quad
    glGenBuffers(1, &this->bufferObject.uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate indices buffer
    glGenBuffers(1, &this->bufferObject.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferObject.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

void Sprite::addChild(Object* child){
    //\todo reject scene and layer.
    this->Object::addChild(child, this, false);
}