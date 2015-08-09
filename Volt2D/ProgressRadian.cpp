//
//  ProgressRadian.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 1/26/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ProgressRadian.h"
#include "Director.h"

using namespace Volt2D;

ProgressRadian::ProgressRadian():
ProgressObject()
{
    
}

ProgressRadian::~ProgressRadian(){
    
}

ProgressRadian* ProgressRadian::create(std::string objectName, const char *radianTextureName, GLenum textureTarget){
    ProgressRadian* newProgressRadian = new ProgressRadian();
    newProgressRadian->init(radianTextureName, textureTarget);
    return newProgressRadian;
}

ProgressRadian* ProgressRadian::createWithSpriteSheet(std::string objectName, std::string frameName, std::string textureName){
    if(Volt2D::Director::getInstance().hasSpriteSheetFrameName(frameName)) {
        if(SpriteSheet* const ssPtr = Volt2D::Director::getInstance().getSpriteSheet(frameName)){
            const ImageEntry* ie = ssPtr->getImageEntry(textureName);
            if(ie){
                ProgressRadian* newProgressRadian = new ProgressRadian();
                Texture* ssTex = ssPtr->getTexture();
                newProgressRadian->setName(objectName);
                newProgressRadian->initWithSpriteSheet(ie, ssTex);
                return newProgressRadian;
            }
            else{
                cout << "[SYSTEM::ERROR] \"" << textureName << "\" does not exists in \"" << frameName << "\" SpriteSheet." << endl;
                return nullptr;
            }
        }
        else{
            cout << "[SYSTEM::ERROR] SpriteSheet called \"" << frameName << "\" does not exists in the system." << endl;
            return nullptr;
        }
    }
    else{
        cout << "[SYSTEM::ERROR] SpriteSheet called \"" << frameName << "\" does not exists in the system." << endl;
        return nullptr;
    }
}

void ProgressRadian::init(const std::string barTextureName, GLenum textureTarget){
    this->texture = Volt2D::Texture::createTextureWithFile(barTextureName, textureTarget);
    this->texture = Volt2D::Texture::createTextureWithFile(barTextureName, textureTarget);
    texture->getImageSize(this->textureWidth, this->textureHeight);
    
    computeVertexData(glm::vec2(0), glm::vec2(1.0f));
    loadVertexData();
    
    this->boundingBox = new Volt2D::BoundingBox(-this->textureWidth/2.0f,
                                                -this->textureHeight/2.0f,
                                                this->textureWidth/2.0f,
                                                this->textureHeight/2.0f);
}

void ProgressRadian::initWithSpriteSheet(const Volt2D::ImageEntry *ie, Volt2D::Texture *texture){
    this->texture = texture;
    //    this->texture->getImageSize(this->w, this->h);
    this->textureWidth = ie->w;
    this->textureHeight = ie->h;
    
    this->useSpriteSheet = true;
    
    computeVertexData(glm::vec2(ie->ImageEntry::uvOriginX,
                                ie->ImageEntry::uvOriginY),
                      glm::vec2(ie->ImageEntry::uvEndX,
                                ie->ImageEntry::uvEndY));

    loadVertexData();
    
    this->boundingBox = new Volt2D::BoundingBox(-(float)this->textureWidth/2.0f,
                                                -(float)this->textureHeight/2.0f,
                                                (float)this->textureWidth/2.0f,
                                                (float)this->textureHeight/2.0f);
}

void ProgressRadian::computeVertexData(glm::vec2 origin, glm::vec2 end){
    //need to compute the gap for vertex width and height. dividing width and height by 3.6 degrees will not work!
    std::vector<float> widthGapList;
    std::vector<float> heightGapList;
    std::vector<float> uvWidthGapList;
    std::vector<float> uvHeightGapList;
    
    this->Object::scaledWidth = this->textureWidth / Volt2D::SCREEN_TO_WORLD_SCALE;
    this->Object::scaledHeight = this->textureHeight / Volt2D::SCREEN_TO_WORLD_SCALE;
    
    float width = this->scaledWidth;
    float height = this->scaledHeight;
    
    float angle = 0;
    //compute vertex width and height gap
    //Note: 12 is hardcoded. 100 / 8 sides
    for(int i = 0; i<12; i++){
        //angle is also hardcoded as well.
        angle+=3.6;
		//Windows need to define M_PI
        float radianAngle = angle * M_PI / 180;
        float curWidthGap = tan(radianAngle) * (width/2);
        widthGapList.push_back(curWidthGap);
        float curHeightGap = tan(radianAngle) * (height/2);
        heightGapList.push_back(curHeightGap);
    }
    
    //reset
    angle = 0;
    //compute uv gaps
    if(this->useSpriteSheet){
        int textureWidth = 0;
        int textureHeight = 0;
        this->texture->getTextureSize(textureWidth, textureHeight);
        float uvWidthHalf = this->textureWidth / static_cast<float>(textureWidth) / 2.0f;
        float uvHeightHalf = this->textureHeight / static_cast<float>(textureHeight) / 2.0f;
        
        for(int i = 0; i<12; i++){
            angle += 3.6f;
            float radianAngle = angle * M_PI / 180;
            float widthGap = tan(radianAngle) * uvWidthHalf;
            uvWidthGapList.push_back(widthGap);
            float heightGap = tan(radianAngle) * uvHeightHalf;
            uvHeightGapList.push_back(heightGap);
        }
    }
    else{
        for(int i = 0; i<12; i++){
            //for single texture
            angle += 3.6f;
            float radianAngle = angle * M_PI / 180;
            float curUvGap = tan(radianAngle) * 0.5;
            uvWidthGapList.push_back(curUvGap);
            uvHeightGapList.push_back(curUvGap);
        }
    }

    int sectionIndex = 0;
    int gapIndex = 0;
    
    /*
                  (0, h/2)       (w/2, h/2)
        *------4-----*-----0------*
        |            |           /|
        |            |        /   |
        |            |      /     |
        |            |    /       |
        |            | /          |
        3            *------------|
        |                         1
        |                         |
        |                         |
        |                         |
        |                         |
        *------------*------2-----*
     (-w/2, -h/2)               (w/2, -h/2)
     */
    
    glm::vec2 uvOrigin;
    float uMax, vMax;   //x,y
    float uMin, vMin;   //x,y
    
    if(this->useSpriteSheet){
        origin.y = 1.0 - origin.y;
        end.y = 1.0 - end.y;
        uvOrigin = glm::vec2(origin.x + ((end.x - origin.x) / 2.0f), end.y + ((origin.y - end.y) / 2.0f));
        uMax = end.x;
        vMax = origin.y;
        uMin = origin.x;
        vMin = end.y;
    }
    else{
        uvOrigin = glm::vec2(0.5, 0.5);
        uMax = vMax = 1.0f;
        uMin = vMin = 0;
    }
    //share this for all
    vertexData.push_back(glm::vec3(0));
    uvVertexData.push_back(uvOrigin);
    
    int indicesIndex = 0;
    //iterate through 100 step and compute vertex
    for(int i = 0; i<100; i++){
        //check corner
        if(i == 12){
            //(2)first corner (top right);
            sectionIndex++;
            //set the index to the last element to list.
            gapIndex = (int)heightGapList.size() - 1;
            //add corner point.
            vertexData.push_back(glm::vec3(width/2, height/2, 0));
            //add point after corner point. use the last element of height gap and decrement index for next
            vertexData.push_back(glm::vec3(width/2, heightGapList.at(gapIndex), 0));
            //same here. add corner point for uv
            uvVertexData.push_back(glm::vec2(uMax, vMax));
            //add point after corner. use the last element in uvGapList. share index since size of lists are same.
            uvVertexData.push_back(glm::vec2(uMax, uvOrigin.y + uvHeightGapList.at(gapIndex)));
            
            //now we decrement index
            gapIndex--;
           
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            indicesIndex++;
            
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            indicesIndex++;
        }
        else if(i == 37){
            //bot right corner
            sectionIndex++;
            //next section need to reverse width gap list.
            gapIndex = (int)widthGapList.size() - 1;
            //add the corner point
            vertexData.push_back(glm::vec3(width/2, -height/2, 0));
            //add the one next from corner point.(height remains same)
            vertexData.push_back(glm::vec3(widthGapList.at(gapIndex), -height/2, 0));
            
            //same here. add corner point for uv
            uvVertexData.push_back(glm::vec2(uMax, vMin));
            uvVertexData.push_back(glm::vec2(uvOrigin.x + uvWidthGapList.at(gapIndex), vMin));
            
            //now we decrement index
            gapIndex--;
            
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            indicesIndex++;
            
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            indicesIndex++;
        }
        else if(i == 62){
            //bot left corner
            sectionIndex++;
            //next section need to reverse with gap list
            gapIndex = (int)heightGapList.size() - 1;
            
            vertexData.push_back(glm::vec3(-width/2, -height/2, 0));
            vertexData.push_back(glm::vec3(-width/2, (-1) * heightGapList.at(gapIndex), 0));
            
            uvVertexData.push_back(glm::vec2(uMin, vMin));
            uvVertexData.push_back(glm::vec2(uMin, uvOrigin.y - uvHeightGapList.at(gapIndex)));
            
            gapIndex--;
            
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            indicesIndex++;
            
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            indicesIndex++;
        }
        else if(i == 87){
            //top left corner
            sectionIndex++;
            //next section need to reverse with width gap list
            gapIndex = (int)widthGapList.size() - 1;

            vertexData.push_back(glm::vec3(-width/2, height/2, 0));
            vertexData.push_back(glm::vec3( (-1) * widthGapList.at(gapIndex), height/2, 0));
            
            uvVertexData.push_back(glm::vec2(uMin, vMax));
            uvVertexData.push_back(glm::vec2(uvOrigin.x - uvWidthGapList.at(gapIndex), vMax));
            
            gapIndex--;
            
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            indicesIndex++;
            
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            indicesIndex++;
        }
        else{
            //not corner.
            switch (sectionIndex) {
                case 0:
                {
                    //(1)top right side
                    if(i == 0){
                        //(1-1)starting point
                        vertexData.push_back(glm::vec3(0, height/2, 0));
                        vertexData.push_back(glm::vec3(widthGapList.at(0), height/2, 0));
                        
                        uvVertexData.push_back(glm::vec2(uvOrigin.x, vMax));
                        uvVertexData.push_back(glm::vec2(uvOrigin.x + uvWidthGapList.at(0), vMax));
                    }
                    else{
                        //(1-2)from the starting point to right before the top right corner
                        vertexData.push_back(glm::vec3(widthGapList.at(gapIndex), height/2, 0));
                        uvVertexData.push_back(glm::vec2(uvOrigin.x + uvWidthGapList.at(gapIndex), vMax));
                    }
                    gapIndex++;
                    break;
                }
                case 1:
                {
                    //right side. Same width, height varies(reverse gap).
                    //gapIndex must be the second last element on the list atm.
                    if(gapIndex == -1){
                        //add right mid point
                        vertexData.push_back(glm::vec3(width/2, 0, 0));
                        uvVertexData.push_back(glm::vec2(uMax, uvOrigin.y));
                        //now increment index
                        gapIndex++;
                    }
                    else{
                        if(i <= 23){
                            //top of right side.
                            vertexData.push_back(glm::vec3(width/2, heightGapList.at(gapIndex), 0));
                            uvVertexData.push_back(glm::vec2(uMax, uvOrigin.y + uvHeightGapList.at(gapIndex)));
                            gapIndex--;
                        }
                        else{
                            //bottom of right side. gap Index should be 0 at starting here.
                            vertexData.push_back(glm::vec3(width/2, (-1) * heightGapList.at(gapIndex) , 0));
                            uvVertexData.push_back(glm::vec2(uMax, uvOrigin.y - uvHeightGapList.at(gapIndex)));
                            gapIndex++;
                        }
                    }

                    break;
                }
                case 2:
                {
                    //bottom side. Same -height, width varies
                    //gapIndex must be the second last element on the list atm.
                    if(gapIndex == -1){
                        //add bottom mid point
                        vertexData.push_back(glm::vec3(0, -height/2, 0));
                        uvVertexData.push_back(glm::vec2(uvOrigin.x, vMin));
                        gapIndex++;
                    }
                    else{
                        if(i <= 48){
                            //right of bottom side
                            vertexData.push_back(glm::vec3(widthGapList.at(gapIndex), -width/2, 0));
                            uvVertexData.push_back(glm::vec2(uvOrigin.x + uvWidthGapList.at(gapIndex), vMin));
                            gapIndex--;
                        }
                        else{
                            //left of bototm side
                            vertexData.push_back(glm::vec3( (-1) * widthGapList.at(gapIndex), -width/2, 0));
                            uvVertexData.push_back(glm::vec2(uvOrigin.x - uvWidthGapList.at(gapIndex), vMin));
                            gapIndex++;
                        }
                    }
                    break;
                }
                case 3:
                {
                    //left side. Same -width, height varies
                    if(gapIndex == -1){
                        //Left mid-point
                        vertexData.push_back(glm::vec3(-width/2, 0, 0));
                        uvVertexData.push_back(glm::vec2(uMin, uvOrigin.y));
                        gapIndex++;
                    }
                    else{
                        if(i <= 73){
                            vertexData.push_back(glm::vec3(-width/2, (-1) * heightGapList.at(gapIndex), 0));
                            uvVertexData.push_back(glm::vec2(uMin, uvOrigin.y - uvHeightGapList.at(gapIndex)));
                            gapIndex--;
                        }
                        else{
                            vertexData.push_back(glm::vec3(-width/2, heightGapList.at(gapIndex), 0));
                            uvVertexData.push_back(glm::vec2(uMin, uvOrigin.y + uvHeightGapList.at(gapIndex)));
                            gapIndex++;
                        }
                    }
                    break;
                }
                case 4:
                {
                    //top left side
                    if(i != 99){
                        vertexData.push_back(glm::vec3( -widthGapList.at(gapIndex), height/2, 0));
                        uvVertexData.push_back(glm::vec2(uvOrigin.x - uvWidthGapList.at(gapIndex), vMax));
                        gapIndex--;
                    }
//                    else{
//                        //last point is same as starting pos.
//                    }
                    
                    break;
                }
                default:
                {
                    assert(false);
                    break;
                }
            }//switch end
            
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            if(i == 99){
                indicesData.push_back(1);
            }
            else{
                indicesData.push_back(indicesIndex+2);
            }
            
            indicesIndex++;
        }//if end
    }//for end
}

void ProgressRadian::loadVertexData(){
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

void ProgressRadian::render(){
    glUseProgram(progPtr->getObject());
    
    const glm::mat4 cameraMat = Volt2D::Director::getInstance().getProjectiveViewMatrix();
    matrixUniformLocation("cameraMat", cameraMat);
    
    glm::mat4 parentMat;
    if(this->parent){
        parentMat = this->parent->getTransformMat();
    }
    
    
    matrixUniformLocation("parentMat", parentMat);
    matrixUniformLocation("modelMat", modelMat);
    matrixUniformLocation("rotateMat", rotateMat);
    matrixUniformLocation("translateMat", translateMat);
    matrixUniformLocation("scaleMat", scaleMat);
    floatUniformLocation("opacity", opacity);
    
    glBindVertexArray(this->bufferObject.vao);
    
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
    
    this->texture->bind(GL_TEXTURE0);
    
    int offsetIndex = 0;

    for(int i = 0; i < this->currentPercentage; i+=this->percentageRate){
        glDrawRangeElements(
                            GL_TRIANGLES/*Rendering mode. draw 2 triangles for 1 quad*/,
                            //index * 0/*start*/,
                            //index * 0/*end*/,
                            //Not sure what start and end do. Gonna try static number
                            0/*start*/,
                            3/*end*/,
                            3/*Count. Number of elements to be rendered. Single quad contains 6 vertexes.*/,
                            GL_UNSIGNED_SHORT/*indices type*/,
                            VOID_OFFSET(offsetIndex * 3 * sizeof(GLushort))/*offset of each char(6 vertexes)*/
                            );
        if(i == 12 || i == 37 || i == 62 || i == 87){
            offsetIndex++;
            glDrawRangeElements(
                                GL_TRIANGLES/*Rendering mode. draw 2 triangles for 1 quad*/,
                                //index * 0/*start*/,
                                //index * 0/*end*/,
                                //Not sure what start and end do. Gonna try static number
                                0/*start*/,
                                3/*end*/,
                                3/*Count. Number of elements to be rendered. Single quad contains 6 vertexes.*/,
                                GL_UNSIGNED_SHORT/*indices type*/,
                                VOID_OFFSET(offsetIndex * 3 * sizeof(GLushort))/*offset of each char(6 vertexes)*/
                                );
        }
        offsetIndex++;
    }
    
    glBindVertexArray(0);
    glUseProgram(0);
}