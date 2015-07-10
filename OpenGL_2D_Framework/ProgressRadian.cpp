//
//  ProgressRadian.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/26/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ProgressRadian.h"

ProgressRadian::ProgressRadian(){
    
}

ProgressRadian::~ProgressRadian(){
    
}

void ProgressRadian::initProgressRadian(GLenum textureTarget, const std::string barTextureName){
    texture = new Texture(textureTarget, barTextureName);
    texture->load();
    texture->getImageSize(w, h);
    
    computeVertexData();
    loadVertexData();
    
    boundingBox->x = vertexData.at(0).x;
    boundingBox->y = vertexData.at(0).y;
    boundingBox->w = w;
    boundingBox->h = h;
}

void ProgressRadian::computeVertexData(){
    //compute gap for each step and corner
    float widthGap = tan(3.6 * M_PI / 180) * (h/2);
    float heightGap = tan(3.6 * M_PI / 180) * (w/2);
    float widthCornerGap = (w/2) - (12 * widthGap);
    float heightCornerGap = (h/2) - (12 * heightGap);
    assert(widthGap * 12 + widthCornerGap == w/2);
    assert(heightGap * 12 + heightCornerGap == h/2);
    
    int sectionIndex = 0;
//    float curAngle = 0;
    int gapIndex = 0;
    float wFloat = (float)w;
    float hFloat = (float)h;
    
    
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
    //share this for all
    vertexData.push_back(origin);
    indicesData.push_back(0);
    int indicesIndex = 0;
    //iterate through 100 step and compute vertex
    for(int i = 0; i<100; i++){
        cout << "i = " << i << endl;
        //check corner
        if(i == 12){
            //first corner (top right);
            sectionIndex++;
            gapIndex = 1;
//            curAngle += 3.6f;
            
//            vertexData.push_back(origin);
//            vertexData.push_back(glm::vec3(wFloat/2 - widthCornerGap, hFloat/2, 0));
//            vertexData.push_back(glm::vec3(wFloat/2, hFloat/2, 0));
//            vertexData.push_back(origin);
//            vertexData.push_back(glm::vec3(wFloat/2, hFloat/2, 0));
//            vertexData.push_back(glm::vec3(wFloat/2, hFloat/2 - heightCornerGap, 0));
            
            vertexData.push_back(glm::vec3(wFloat/2, hFloat/2, 0));
            vertexData.push_back(glm::vec3(wFloat/2, hFloat/2 - heightCornerGap, 0));
            cout << "pos " << indicesIndex << " = (" << wFloat/2 << ", " << hFloat/2 << ", " << 0 << ")" << endl;
            cout << "pos " << indicesIndex+1 << " = (" << wFloat/2 << ", " << hFloat/2 - heightCornerGap << ", " << 0 << ")" << endl;
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            cout << "Adding indices" << endl;
            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            cout << "Adding indices" << endl;
            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
        }
        else if(i == 37){
            sectionIndex++;
            gapIndex = 1;
//            curAngle += 3.6f;
//            vertexData.push_back(origin);
//            vertexData.push_back(glm::vec3(wFloat/2, -hFloat/2 + heightCornerGap, 0));
//            vertexData.push_back(glm::vec3(wFloat/2, -hFloat/2, 0));
//            vertexData.push_back(origin);
            vertexData.push_back(glm::vec3(wFloat/2, -hFloat/2, 0));
            vertexData.push_back(glm::vec3(wFloat/2 - widthCornerGap, -hFloat/2, 0));
            cout << "pos " << indicesIndex << " = (" << wFloat/2 << ", " << -hFloat/2 << ", " << 0 << ")" << endl;
            cout << "pos " << indicesIndex+1 << " = (" << wFloat/2 - widthCornerGap << ", " << -hFloat/2 << ", " << 0 << ")" << endl;
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            cout << "Adding indices" << endl;
            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            cout << "Adding indices" << endl;
            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
        }
        else if(i == 62){
            sectionIndex++;
            gapIndex = 1;
//            curAngle += 3.6f;
//            vertexData.push_back(origin);
//            vertexData.push_back(glm::vec3(-wFloat/2 + widthCornerGap, -hFloat/2, 0));
//            vertexData.push_back(glm::vec3(-wFloat/2, -hFloat/2, 0));
//            vertexData.push_back(origin);
            vertexData.push_back(glm::vec3(-wFloat/2, -hFloat/2, 0));
            vertexData.push_back(glm::vec3(-wFloat/2, -hFloat/2 + heightCornerGap, 0));
            cout << "pos " << indicesIndex << " = (" << -wFloat/2 << ", " << -hFloat/2 << ", " << 0 << ")" << endl;
            cout << "pos " << indicesIndex+1 << " = (" << -wFloat/2 << ", " << -hFloat/2 + heightCornerGap << ", " << 0 << ")" << endl;
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            cout << "Adding indices" << endl;
            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            cout << "Adding indices" << endl;
            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
        }
        else if(i == 87){
            sectionIndex++;
            gapIndex = 1;
//            curAngle += 3.6f;
//            vertexData.push_back(origin);
//            vertexData.push_back(glm::vec3(-wFloat/2, hFloat/2 - heightCornerGap, 0));
//            vertexData.push_back(glm::vec3(-wFloat/2, hFloat/2, 0));
//            vertexData.push_back(origin);
            vertexData.push_back(glm::vec3(-wFloat/2, hFloat/2, 0));
            vertexData.push_back(glm::vec3(-wFloat/2 + widthCornerGap, hFloat/2, 0));
            cout << "pos " << indicesIndex << " = (" << -wFloat/2 << ", " << hFloat/2 << ", " << 0 << ")" << endl;
            cout << "pos " << indicesIndex+1 << " = (" << -wFloat/2 + widthCornerGap << ", " << hFloat/2 << ", " << 0 << ")" << endl;
            //for corners.
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            cout << "Adding indices" << endl;
            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            indicesData.push_back(indicesIndex+2);
            cout << "Adding indices" << endl;
            cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            indicesIndex++;
        }
        else{
            //not corner.
//            assert(gapIndex < 12);
            
            switch (sectionIndex) {
                case 0:
                {
                    //top right side
                    if(i == 0){
                        //starting point
                        vertexData.push_back(glm::vec3(0, hFloat/2, 0));
                        vertexData.push_back(glm::vec3(widthGap, hFloat/2, 0));
                        indicesData.push_back(1);
                        indicesData.push_back(2);
                        cout << "Adding starting pos" << endl;
                        cout << "pos " << 1 << " = (" << 0 << ", " << hFloat/2 << ", " << 0 << ")" << endl;
                        cout << "pos " << 2 << " = (" << widthGap << ", " << hFloat/2 << ", " << 0 << ")" << endl;
                    }
                    else{
//                        vertexData.push_back(origin);   //origin
//                        glm::vec3 point = glm::vec3(0 + (gapIndex * widthGap), hFloat/2, 0);
//                        vertexData.push_back(point); //top
//                        point.x += widthGap;
//                        vertexData.push_back(point);   //right
                        vertexData.push_back(glm::vec3(widthGap + (gapIndex * widthGap), hFloat/2, 0));
                        cout << "pos " << indicesIndex << " = (" << widthGap + (gapIndex * widthGap) << ", " << hFloat/2 << ", " << 0 << ")" << endl;
                    }
                    break;
                }
                case 1:
                {
                    //right side
//                    vertexData.push_back(origin);
//                    glm::vec3 point = glm::vec3(wFloat, hFloat/2 - heightCornerGap - (gapIndex * heightGap), 0);
//                    vertexData.push_back(point);
//                    point.y -= heightGap;
//                    vertexData.push_back(point);
                    vertexData.push_back(glm::vec3(wFloat/2, hFloat/2 - heightCornerGap - (gapIndex * heightGap), 0));
                    cout << "pos " << indicesIndex << " = (" << wFloat/2 << ", " << hFloat/2 - heightCornerGap - (gapIndex * heightGap) << ", " << 0 << ")" << endl;
                    break;
                }
                case 2:
                {
                    //bottom side
//                    vertexData.push_back(origin);
//                    glm::vec3 point = glm::vec3(wFloat/2 - widthCornerGap - (gapIndex * widthGap), -hFloat/2, 0);
//                    vertexData.push_back(point);
//                    point.x -= widthGap;
//                    vertexData.push_back(point);
                    vertexData.push_back(glm::vec3(wFloat/2 - widthCornerGap - (gapIndex * widthGap), -hFloat/2, 0));
                    cout << "pos " << indicesIndex << " = (" << wFloat/2 - widthCornerGap - (gapIndex * widthGap) << ", " << hFloat/2 << ", " << -hFloat/2 << ")" << endl;
                    break;
                }
                case 3:
                {
                    //right side
//                    vertexData.push_back(origin);
//                    glm::vec3 point = glm::vec3(-wFloat/2, -hFloat/2 + heightCornerGap + (gapIndex * heightGap), 0);
//                    vertexData.push_back(point);
//                    point.y += heightGap;
//                    vertexData.push_back(point);
                    vertexData.push_back(glm::vec3(-wFloat/2, -hFloat/2 + heightCornerGap + (gapIndex * heightGap), 0));
                    cout << "pos " << indicesIndex << " = (" << -wFloat/2 << ", " << -hFloat/2 + heightCornerGap + (gapIndex * heightGap) << ", " << 0 << ")" << endl;
                    break;
                }
                case 4:
                {
                    //top right side
//                    vertexData.push_back(origin);
//                    glm::vec3 point = glm::vec3(-wFloat/2 + widthCornerGap + (gapIndex * widthGap), hFloat/2, 0);
//                    vertexData.push_back(point);
//                    point.x += widthGap;
//                    vertexData.push_back(point);
                    if(i != 99)
                        vertexData.push_back(glm::vec3(-wFloat/2 + widthCornerGap + (gapIndex * widthGap), hFloat/2, 0));
                    else
                        cout << "skipping last spot. shares the starting one" << endl;
                    cout << "pos " << indicesIndex << " = (" << -wFloat/2 + widthCornerGap + (gapIndex * widthGap) << ", " << hFloat/2 << ", " << hFloat/2 << ")" << endl;
                    break;
                }
                default:
                {
                    assert(false);
                    break;
                }
            }//switch end
            
            cout << "Adding indices" << endl;
            indicesData.push_back(0);
            indicesData.push_back(indicesIndex+1);
            if(i == 99){
                indicesData.push_back(1);
                cout << 0 << ", " << indicesIndex+1 << ", " << 1 << endl;
            }
            else{
                indicesData.push_back(indicesIndex+2);
                cout << 0 << ", " << indicesIndex+1 << ", " << indicesIndex + 2 << endl;
            }
            
            gapIndex++;
            indicesIndex++;
//            curAngle+=3.6f;
        }//if end
    }//for end
}

void ProgressRadian::loadVertexData(){
    //generate vertex array object and bind it
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //generate vertex buffer object for quad
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate texture uv buffer object for quad
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate indices buffer
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

void ProgressRadian::render(){
    
}