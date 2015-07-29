
//
//  Sprite.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 11/7/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

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
    cout << "[SYSTEM::RELEASE] Deleting Sprite object" << endl;
	if (texture && !useSpriteSheet){
		delete texture;
		texture = nullptr;
	}
    else{
        texture = 0;
    }
    
    actionRunning = false;
}

Sprite* Sprite::createSprite(std::string objectName, const char *fileName, GLenum textureTarget){
    std::cout << "[SYSTEM::INFO] Initializing sprite with texture. \"" << fileName << "\"" << endl;
    
    Sprite* newSprite = new Sprite();
    newSprite->setName(objectName);
    newSprite->initTexture(fileName, textureTarget);
    return newSprite;
}

Sprite* Sprite::createSpriteWithFrameName(std::string objectName, std::string frameName, std::string imageFileName){
    if(Volt2D::Director::getInstance().hasSpriteSheetFrameName(frameName)) {
        if(SpriteSheet* const ssPtr = Volt2D::Director::getInstance().getSpriteSheet(frameName)){
            const ImageEntry* ie = ssPtr->getImageEntry(imageFileName);
            if(ie){
                Sprite* newSprite = new Sprite();
                Texture* ssTex = ssPtr->getTexture();
                newSprite->setName(objectName);
                newSprite->initSpriteWithSpriteSheet(ie, ssTex);
                return newSprite;
            }
            else{
                return nullptr;
            }
        }
        else{
            return nullptr;
        }
    }
    else{
        return nullptr;
    }
}

Sprite* Sprite::createWith2DTexture(std::string objectName, Volt2D::Texture *texture){
    Sprite* newSprite = new Sprite();
    newSprite->setName(objectName);
    newSprite->setTexture(texture);
    return newSprite;
}

void Sprite::initTexture(const std::string& fileName, GLenum textureTarget){
    std::string textureDir = Volt2D::Director::getInstance().getWorkingDir() + "/../Texture/";
    this->texture = Texture::createTextureWithFile(fileName, textureTarget);
//    texture->getImageSize(w, h);
    this->texture->getTextureSize(this->textureWidth, this->textureHeight);
    
    computeVertexData();
    loadVertexData();
    
    this->boundingBox = new Volt2D::BoundingBox(-(float)this->textureWidth/2.0f,
                                        -(float)this->textureHeight/2.0f,
                                        (float)this->textureWidth/2.0f,
                                        (float)this->textureHeight/2.0f);
}

void Sprite::setTexture(Volt2D::Texture *texture){
    this->texture = texture;
    this->texture->getTextureSize(this->textureWidth, this->textureHeight);
    
    computeVertexData();
    loadVertexData();
    
    this->boundingBox = new Volt2D::BoundingBox(-(float)this->textureWidth/2.0f,
                                                -(float)this->textureHeight/2.0f,
                                                (float)this->textureWidth/2.0f,
                                                (float)this->textureHeight/2.0f);
}

void Sprite::initSpriteWithSpriteSheet(const ImageEntry* ie, Texture* texture){
    this->texture = texture;
//    this->texture->getImageSize(this->w, this->h);
    this->textureWidth = ie->w;
    this->textureHeight = ie->h;
    
    this->useSpriteSheet = true;
    
    computeVertices();
    computeTextureCoordinates(
                              glm::vec2(ie->ImageEntry::uvOriginX,
                                        ie->ImageEntry::uvOriginY),
                              glm::vec2(ie->ImageEntry::uvEndX,
                                        ie->ImageEntry::uvEndY)
                              );
    computeIndices();
    loadVertexData();
    
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

    glm::mat4 cameraMat = Volt2D::Director::getInstance().getCameraPtr()->getMatrix();
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
    
    this->RenderableObject::width = width;
    this->RenderableObject::height = height;
    
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