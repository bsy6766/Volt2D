//
//  ProgressRadian.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/26/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ProgressRadian.h"
#include "Director.h"

ProgressRadian::ProgressRadian():
ProgressObject()
{
    
}

ProgressRadian::~ProgressRadian(){
    
}

ProgressRadian* ProgressRadian::createProgressRadian(std::string objectName, const char *radianTextureName, GLenum textureTarget){
    ProgressRadian* newProgressRadian = new ProgressRadian();
    newProgressRadian->initProgressRadian(radianTextureName, textureTarget);
    return newProgressRadian;
}

void ProgressRadian::initProgressRadian(const std::string barTextureName, GLenum textureTarget){
    this->texture = Texture::createTextureWithFile(barTextureName, textureTarget);
    texture->getImageSize(w, h);
    
    computeVertexData();
    loadVertexData();
    
    this->boundingBox = new BoundingBox(-this->w/2, -this->h/2, this->w/2, this->h/2);
}

void ProgressRadian::computeVertexData(){
    //need to compute the gap for vertex width and height. dividing width and height by 3.6 degrees will not work!
    std::vector<float> widthGapList;
    std::vector<float> heightGapList;
    std::vector<float> uvGapList;   //since u and v have same range of value(0~1), only need 1 for both width and height
    
    width /= SCREEN_TO_WORLD_SCALE;
    height /= SCREEN_TO_WORLD_SCALE;
    
    this->RenderableObject::width = w / SCREEN_TO_WORLD_SCALE;
    this->RenderableObject::height = h / SCREEN_TO_WORLD_SCALE;
    
    float angle = 0;
    for(int i = 0; i<12; i++){
        angle+=3.6;
		//Windows need to define M_PI
        float radianAngle = angle * M_PI / 180;
        float curWidthGap = tan(radianAngle) * (width/2);
        widthGapList.push_back(curWidthGap);
        float curHeightGap = tan(radianAngle) * (height/2);
        heightGapList.push_back(curHeightGap);
        float curUvGap = tan(radianAngle) * 0.5;
        uvGapList.push_back(curUvGap);
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
    
    glm::vec3 origin = glm::vec3();
    glm::vec2 uvOrigin = glm::vec2(0.5, 0.5);
    //share this for all
    vertexData.push_back(origin);
    uvVertexData.push_back(uvOrigin);
    int indicesIndex = 0;
    //iterate through 100 step and compute vertex
    for(int i = 0; i<100; i++){
//        cout << "i = " << i << endl;
        //check corner
        if(i == 12){
            //(2)first corner (top right);
//            cout << "------ Top Right Corner -------" << endl;
            sectionIndex++;
            //set the index to the last element to list.
            gapIndex = (int)heightGapList.size() - 1;
            //add corner point.
            vertexData.push_back(glm::vec3(width/2, height/2, 0));
            //add point after corner point. use the last element of height gap and decrement index for next
            vertexData.push_back(glm::vec3(width/2, heightGapList.at(gapIndex), 0));
            
//            cout << "pos " << indicesIndex << " = (" << width/2 << ", " << height/2 << ", " << 0 << ")" << endl;
//            cout << "pos " << indicesIndex+1 << " = (" << width/2 << ", " << heightGapList.at(gapIndex) << ", " << 0 << ")" << endl;
            //same here. add corner point for uv
            uvVertexData.push_back(glm::vec2(1.0, 1.0));
            //add point after corner. use the last element in uvGapList. share index since size of lists are same.
            uvVertexData.push_back(glm::vec2(1.0, 0.5 + uvGapList.at(gapIndex)));
            
//            cout << "uv pos " << indicesIndex << " = (" << 1.0 << ", " << 1.0 << ")" << endl;
//            cout << "uv pos " << indicesIndex << " = (" << 1.0 << ", " << 0.5 + uvGapList.at(gapIndex) << ")" << endl;
            
            //now we decrement index
            gapIndex--;
            
           
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
//            cout << "Adding indices" << endl;
//            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
//            cout << "Adding indices" << endl;
//            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
        }
        else if(i == 37){
            //bot right corner
//            cout << "------ Bottom Right Corner -------" << endl;
            sectionIndex++;
            //next section need to reverse width gap list.
            gapIndex = (int)widthGapList.size() - 1;
            //add the corner point
            vertexData.push_back(glm::vec3(width/2, -height/2, 0));
            //add the one next from corner point.(height remains same)
            vertexData.push_back(glm::vec3(widthGapList.at(gapIndex), -height/2, 0));
            
//            cout << "pos " << indicesIndex << " = (" << width/2 << ", " << -height/2 << ", " << 0 << ")" << endl;
//            cout << "pos " << indicesIndex+1 << " = (" << widthGapList.at(gapIndex) << ", " << -height/2 << ", " << 0 << ")" << endl;
            
            //same here. add corner point for uv
            uvVertexData.push_back(glm::vec2(1.0, 0));
            uvVertexData.push_back(glm::vec2(0.5 + uvGapList.at(gapIndex), 0));
            
//            cout << "uv pos " << indicesIndex << " = (" << 1.0 << ", " << 0 << ")" << endl;
//            cout << "uv pos " << indicesIndex << " = (" << 0.5 + uvGapList.at(gapIndex) << ", " << 0 << ")" << endl;
            
            //now we decrement index
            gapIndex--;
            
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
//            cout << "Adding indices" << endl;
//            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
//            cout << "Adding indices" << endl;
//            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
        }
        else if(i == 62){
            //bot left corner
//            cout << "------ Bottom Left Corner -------" << endl;
            sectionIndex++;
            //next section need to reverse with gap list
            gapIndex = (int)heightGapList.size() - 1;
            
            vertexData.push_back(glm::vec3(-width/2, -height/2, 0));
            vertexData.push_back(glm::vec3(-width/2, (-1) * heightGapList.at(gapIndex), 0));
            
//            cout << "pos " << indicesIndex << " = (" << -width/2 << ", " << -height/2 << ", " << 0 << ")" << endl;
//            cout << "pos " << indicesIndex+1 << " = (" << -width/2 << ", " << (-1) * heightGapList.at(gapIndex) << ", " << 0 << ")" << endl;
            
            uvVertexData.push_back(glm::vec2(0, 0));
            uvVertexData.push_back(glm::vec2(0, 0.5 - uvGapList.at(gapIndex)));
            
//            cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << 0 << ")" << endl;
//            cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << 0.5 - uvGapList.at(gapIndex) << ")" << endl;
            
            gapIndex--;
            
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
//            cout << "Adding indices" << endl;
//            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
//            cout << "Adding indices" << endl;
//            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
        }
        else if(i == 87){
            //top left corner
//            cout << "Top Left Corner" << endl;
            sectionIndex++;
            //next section need to reverse with width gap list
            gapIndex = (int)widthGapList.size() - 1;

            vertexData.push_back(glm::vec3(-width/2, height/2, 0));
            vertexData.push_back(glm::vec3( (-1) * widthGapList.at(gapIndex), height/2, 0));
            
//            cout << "pos " << indicesIndex << " = (" << -width/2 << ", " << height/2 << ", " << 0 << ")" << endl;
//            cout << "pos " << indicesIndex+1 << " = (" << (-1) * widthGapList.at(gapIndex) << ", " << height/2 << ", " << 0 << ")" << endl;
            
            uvVertexData.push_back(glm::vec2(0, 1));
            uvVertexData.push_back(glm::vec2(0.5 - uvGapList.at(gapIndex), 1));
//            cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << 1 << ")" << endl;
//            cout << "uv pos " << indicesIndex << " = (" << 0.5 - uvGapList.at(gapIndex) << ", " << 1 << ")" << endl;
            
            gapIndex--;
            
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
//            cout << "Adding indices" << endl;
//            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
//            cout << "Adding indices" << endl;
//            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
        }
        else{
            //not corner.
//            assert(gapIndex < 12);
            
            switch (sectionIndex) {
                case 0:
                {
                    //(1)top right side
                    if(i == 0){
                        //(1-1)starting point
                        vertexData.push_back(glm::vec3(0, height/2, 0));
                        vertexData.push_back(glm::vec3(widthGapList.at(0), height/2, 0));
//                        indicesData.push_back(1);
//                        indicesData.push_back(2);
//                        cout << "Adding starting pos" << endl;
//                        cout << "pos " << 1 << " = (" << 0 << ", " << height/2 << ", " << 0 << ")" << endl;
//                        cout << "pos " << 2 << " = (" << widthGapList.at(0) << ", " << height/2 << ", " << 0 << ")" << endl;
                        uvVertexData.push_back(glm::vec2(0.5, 1.0));
                        uvVertexData.push_back(glm::vec2(0.5 + uvGapList.at(0), 1.0));
//                        cout << "uv pos " << 1 << " = (" << 0.5 << ", " << 1.0 << ")" << endl;
//                        cout << "uv pos " << 2 << " = (" << 0.5 + uvGapList.at(0) << ", " << 1.0 << ")" << endl;
                    }
                    else{
                        //(1-2)from the starting point to right before the top right corner
                        vertexData.push_back(glm::vec3(widthGapList.at(gapIndex), height/2, 0));
//                        cout << "pos " << indicesIndex << " = (" << widthGapList.at(gapIndex) << ", " << height/2 << ", " << 0 << ")" << endl;
                        uvVertexData.push_back(glm::vec2(0.5 + uvGapList.at(gapIndex), 1.0));
//                        cout << "uv pos " << indicesIndex << " = (" << 0.5 + uvGapList.at(gapIndex)<< ", " << 1.0 << ")" << endl;
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
//                        cout << "right mid point" << endl;
                        vertexData.push_back(glm::vec3(width/2, 0, 0));
                        uvVertexData.push_back(glm::vec2(1.0, 0.5));
                        
//                        cout << "pos " << indicesIndex << " = (" << width/2 << ", " << 0 << ", " << 0 << ")" << endl;
//                        cout << "uv pos " << indicesIndex << " = (" << 1.0 << ", " << 0.5 << ")" << endl;
                        //now increment index
                        gapIndex++;
                    }
                    else{
                        if(i <= 23){
                            //top of right side.
                            vertexData.push_back(glm::vec3(width/2, heightGapList.at(gapIndex), 0));
                            uvVertexData.push_back(glm::vec2(1.0, 0.5 + uvGapList.at(gapIndex)));
                            
//                            cout << "pos " << indicesIndex << " = (" << width/2 << ", " << heightGapList.at(gapIndex) << ", " << 0 << ")" << endl;
//                            cout << "uv pos " << indicesIndex << " = (" << 1 << ", " << 0.5 + uvGapList.at(gapIndex) << ")" << endl;
                            gapIndex--;
                        }
                        else{
                            //bottom of right side. gap Index should be 0 at starting here.
                            vertexData.push_back(glm::vec3(width/2, (-1) * heightGapList.at(gapIndex) , 0));
                            uvVertexData.push_back(glm::vec2(1.0, 0.5 - uvGapList.at(gapIndex)));
                            
//                            cout << "pos " << indicesIndex << " = (" << width/2 << ", " << (-1) * heightGapList.at(gapIndex) << ", " << 0 << ")" << endl;
//                            cout << "uv pos " << indicesIndex << " = (" << 1.0 << ", " << 0.5 - uvGapList.at(gapIndex) << ")" << endl;
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
//                        cout << "bottom mid point" << endl;
                        vertexData.push_back(glm::vec3(0, -height/2, 0));
                        uvVertexData.push_back(glm::vec2(0.5, 0));
                        
//                        cout << "pos " << indicesIndex << " = (" << 0 << ", " << -height/2 << ", " << 0 << ")" << endl;
//                        cout << "uv pos " << indicesIndex << " = (" << 0.5 << ", " << 0 << ")" << endl;
                        gapIndex++;
                    }
                    else{
                        if(i <= 48){
                            //right of bottom side
                            vertexData.push_back(glm::vec3(widthGapList.at(gapIndex), -width/2, 0));
                            uvVertexData.push_back(glm::vec2(0.5 + uvGapList.at(gapIndex), 0));
//                            cout << "pos " << indicesIndex << " = (" << widthGapList.at(gapIndex) << ", " << -width/2 << ", " << 0 << ")" << endl;
//                            cout << "uv pos " << indicesIndex << " = (" << 0.5 + uvGapList.at(gapIndex) << ", " << 0 << ", " << 0 << ")" << endl;
                            gapIndex--;
                        }
                        else{
                            //left of bototm side
                            vertexData.push_back(glm::vec3( (-1) * widthGapList.at(gapIndex), -width/2, 0));
                            uvVertexData.push_back(glm::vec2(0.5 - uvGapList.at(gapIndex), 0));
//                            cout << "pos " << indicesIndex << " = (" << (-1) * widthGapList.at(gapIndex) << ", " << -width/2 << ", " << 0 << ")" << endl;
//                            cout << "uv pos " << indicesIndex << " = (" << 0.5 - uvGapList.at(gapIndex) << ", " << 0 << ", " << 0 << ")" << endl;
                            gapIndex++;
                        }
                    }
                    break;
                }
                case 3:
                {
                    //left side. Same -width, height varies
                    
                    if(gapIndex == -1){
//                        cout << "left mid point" << endl;
                        vertexData.push_back(glm::vec3(-width/2, 0, 0));
                        uvVertexData.push_back(glm::vec2(0, 0.5));
//                        cout << "pos " << indicesIndex << " = (" << -width/2 << ", " << 0 << ", " << 0 << ")" << endl;
//                        cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << 0.5 << ")" << endl;
                        gapIndex++;
                    }
                    else{
                        if(i <= 73){
                            vertexData.push_back(glm::vec3(-width/2, (-1) * heightGapList.at(gapIndex), 0));
                            uvVertexData.push_back(glm::vec2(0, 0.5 - uvGapList.at(gapIndex)));
//                            cout << "pos " << indicesIndex << " = (" << -width/2 << ", " << (-1) * heightGapList.at(gapIndex) << ", " << 0 << ")" << endl;
//                            cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << 0.5 - uvGapList.at(gapIndex) << ")" << endl;
                            gapIndex--;
                        }
                        else{
                            vertexData.push_back(glm::vec3(-width/2, heightGapList.at(gapIndex), 0));
                            uvVertexData.push_back(glm::vec2(0, 0.5 + uvGapList.at(gapIndex)));
//                            cout << "pos " << indicesIndex << " = (" << -width/2 << ", " << heightGapList.at(gapIndex) << ", " << 0 << ")" << endl;
//                            cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << 0.5 + uvGapList.at(gapIndex) << ")" << endl;
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
                        uvVertexData.push_back(glm::vec2( 0.5-uvGapList.at(gapIndex), 1.0));
//                        cout << "pos " << indicesIndex << " = (" << -widthGapList.at(gapIndex) << ", " << height/2 << ", " << 0 << ")" << endl;
//                        cout << "uv pos " << indicesIndex << " = (" << 0.5-uvGapList.at(gapIndex) << ", " << 1.0 << ")" << endl;
                        gapIndex--;
                    }
//                    else{
//                        //last point is same as starting pos.
//                        cout << "skipping last spot. shares the starting one" << endl;
//                    }
                    
                    break;
                }
                default:
                {
                    assert(false);
                    break;
                }
            }//switch end
            
//            cout << "Adding indices" << endl;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            if(i == 99){
                indicesData.push_back(1);
//                cout << 0 << ", " << indicesIndex+1 << ", " << 1 << endl;
            }
            else{
                indicesData.push_back(indicesIndex+2);
//                cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
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
    glm::mat4 cameraMat = Director::getInstance().getCameraPtr()->getMatrix();
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