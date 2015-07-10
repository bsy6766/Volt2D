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
    //need to compute the gap for vertex width and height. dividing width and height by 3.6 degrees will not work!
    std::vector<float> widthGapList;
//    widthGapList.push_back(0);
    std::vector<float> heightGapList;
//    heightGapList.push_back(0);
    
    float angle = 0;
    for(int i = 0; i<12; i++){
        angle+=3.6;
        float curWidthGap = tan(angle * M_PI / 180) * (h/2);
        widthGapList.push_back(curWidthGap);
        float curHeightGap = tan(angle * M_PI / 180) * (w/2);
        heightGapList.push_back(curHeightGap);
    }
    
//    //compute gap for each step and corner
//    float widthGap = tan(3.6 * M_PI / 180) * (h/2);
//    float heightGap = tan(3.6 * M_PI / 180) * (w/2);
//    float widthCornerGap = (w/2) - (12 * widthGap);
//    float heightCornerGap = (h/2) - (12 * heightGap);
//    assert(widthGap * 12 + widthCornerGap == w/2);
//    assert(heightGap * 12 + heightCornerGap == h/2);
//    
//    //uv. width and height is always 1 but I'll just separate just in case. :(
//    float uvWidthGap = tan(3.6 * M_PI / 180) * 1.0;
//    float uvHeightGap = tan(3.6 * M_PI / 180) * 1.0;
//    float uvWidthCornerGap = 1.0 - (12 * uvWidthGap);
//    float uvHeightCornerGap = 1.0 - (12 * uvHeightGap);
//    assert(uvWidthGap * 12 + uvWidthCornerGap == 1.0);
//    assert(uvHeightGap * 12 + uvHeightCornerGap == 1.0);
    
    int sectionIndex = 0;
//    float curAngle = 0;
    int gapIndex = 0;
    float wFloat = (float)w;
    float hFloat = (float)h;
    float uvWidth = 1.0f;
    float uvHeight = 1.0f;
    
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
            
            vertexData.push_back(glm::vec3(wFloat/2, hFloat/2, 0));
            vertexData.push_back(glm::vec3(wFloat/2, hFloat/2 - heightCornerGap, 0));
            cout << "pos " << indicesIndex << " = (" << wFloat/2 << ", " << hFloat/2 << ", " << 0 << ")" << endl;
            cout << "pos " << indicesIndex+1 << " = (" << wFloat/2 << ", " << hFloat/2 - heightCornerGap << ", " << 0 << ")" << endl;
            uvVertexData.push_back(glm::vec2(uvWidth, uvHeight));
            uvVertexData.push_back(glm::vec2(uvWidth, uvHeight - uvHeightCornerGap));
            cout << "uv pos " << indicesIndex << " = (" << uvWidth << ", " << uvHeight << ")" << endl;
            cout << "uv pos " << indicesIndex << " = (" << uvWidth << ", " << uvHeight - uvHeightCornerGap << ")" << endl;
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
            //bot right corner
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
            uvVertexData.push_back(glm::vec2(uvWidth, 0));
            uvVertexData.push_back(glm::vec2(uvWidth - uvWidthCornerGap, 0));
            cout << "uv pos " << indicesIndex << " = (" << uvWidth << ", " << 0 << ")" << endl;
            cout << "uv pos " << indicesIndex << " = (" << uvWidth - uvWidthCornerGap << ", " << 0 << ")" << endl;
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
            //bot left corner
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
            uvVertexData.push_back(glm::vec2(0, 0));
            uvVertexData.push_back(glm::vec2(0, uvHeightCornerGap));
            cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << uvHeight << ")" << endl;
            cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << uvHeight + uvHeightCornerGap << ")" << endl;
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
            //top left corner
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
            uvVertexData.push_back(glm::vec2(uvWidth, uvHeight));
            uvVertexData.push_back(glm::vec2(uvWidth, uvHeight - uvHeightCornerGap));
            cout << "uv pos " << indicesIndex << " = (" << uvWidth << ", " << uvHeight << ")" << endl;
            cout << "uv pos " << indicesIndex << " = (" << uvWidth << ", " << uvHeight - uvHeightCornerGap << ")" << endl;
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
                        uvVertexData.push_back(glm::vec2(uvOrigin.x, uvHeight));
                        uvVertexData.push_back(glm::vec2(uvWidthGap, uvHeight));
                        cout << "uv pos " << 1 << " = (" << uvOrigin.x << ", " << uvHeight << ")" << endl;
                        cout << "uv pos " << 2 << " = (" << uvWidthGap << ", " << uvHeight << ")" << endl;
                    }
                    else{
                        vertexData.push_back(glm::vec3(widthGap + (gapIndex * widthGap), hFloat/2, 0));
                        cout << "pos " << indicesIndex << " = (" << widthGap + (gapIndex * widthGap) << ", " << hFloat/2 << ", " << 0 << ")" << endl;
                        uvVertexData.push_back(glm::vec2(uvWidthGap + (gapIndex * uvWidthGap), uvHeight));
                        cout << "uv pos " << indicesIndex << " = (" << uvWidthGap + (gapIndex * uvWidthGap) << ", " << uvHeight << ")" << endl;
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
                    uvVertexData.push_back(glm::vec2(uvWidth, uvHeight - uvHeightCornerGap - (gapIndex * uvHeightGap)));
                    cout << "uv pos " << indicesIndex << " = (" << uvWidthGap << ", " << uvHeight - uvHeightCornerGap - (gapIndex * uvHeightGap) << ")" << endl;
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
                    uvVertexData.push_back(glm::vec2(uvWidth - uvWidthCornerGap - (gapIndex * uvWidthGap), 0));
                    cout << "uv pos " << indicesIndex << " = (" << uvWidth - uvWidthCornerGap - (gapIndex * uvWidthGap) << ", " << 0 << ")" << endl;
                    break;
                }
                case 3:
                {
                    //left side
//                    vertexData.push_back(origin);
//                    glm::vec3 point = glm::vec3(-wFloat/2, -hFloat/2 + heightCornerGap + (gapIndex * heightGap), 0);
//                    vertexData.push_back(point);
//                    point.y += heightGap;
//                    vertexData.push_back(point);
                    vertexData.push_back(glm::vec3(-wFloat/2, -hFloat/2 + heightCornerGap + (gapIndex * heightGap), 0));
                    cout << "pos " << indicesIndex << " = (" << -wFloat/2 << ", " << -hFloat/2 + heightCornerGap + (gapIndex * heightGap) << ", " << 0 << ")" << endl;
                    uvVertexData.push_back(glm::vec2(0, uvHeightCornerGap + (gapIndex * uvHeightGap)));
                    cout << "uv pos " << indicesIndex << " = (" << 0 << ", " << uvHeightCornerGap + (gapIndex * uvHeightGap) << ")" << endl;
                    break;
                }
                case 4:
                {
                    //top left side
//                    vertexData.push_back(origin);
//                    glm::vec3 point = glm::vec3(-wFloat/2 + widthCornerGap + (gapIndex * widthGap), hFloat/2, 0);
//                    vertexData.push_back(point);
//                    point.x += widthGap;
//                    vertexData.push_back(point);
                    if(i != 99){
                        vertexData.push_back(glm::vec3(-wFloat/2 + widthCornerGap + (gapIndex * widthGap), hFloat/2, 0));
                        uvVertexData.push_back(glm::vec2(uvWidthCornerGap + (gapIndex * uvWidthGap), uvHeight));
                    }
                    else{
                        cout << "skipping last spot. shares the starting one" << endl;
                    }
                    cout << "pos " << indicesIndex << " = (" << -wFloat/2 + widthCornerGap + (gapIndex * widthGap) << ", " << hFloat/2 << ", " << hFloat/2 << ")" << endl;
                    cout << "uv pos " << indicesIndex << " = (" << uvWidthCornerGap + (gapIndex * uvWidthGap) << ", " << uvHeight << ")" << endl;
                    
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