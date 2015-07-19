//
//  BoundingBox.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(int x, int y, int w, int h):
origin(glm::vec2(x, y)),
end(glm::vec2(w, h)),
originalOrigin(glm::vec2(x, y)),
originalEnd(glm::vec2(w, h))
{
    
}

BoundingBox::~BoundingBox(){
    
}

bool BoundingBox::containsPoint(glm::vec2 point){
    if(point.x >= origin.x && point.y >= origin.y && point.x <= end.x && point.y <= end.y)
        return true;
    else
        return false;
}

void BoundingBox::updateBoundingBox(glm::mat4 translateMat, glm::mat4 scaledMat, glm::mat4 rotateMat){
    glm::vec4 castedOrigin = glm::vec4(originalOrigin.x, originalOrigin.y, 1, 1);
    glm::vec4 castedEnd = glm::vec4(originalEnd.x, originalEnd.y, 1, 1);
    glm::mat4 modelMat = glm::mat4() * translateMat * rotateMat * scaledMat;
    origin = glm::vec2(modelMat * castedOrigin);
    end = glm::vec2(modelMat * castedEnd);
    updatePointWithMax();
}

void BoundingBox::updatePointWithMax(){
    float minX, maxX;
    float minY, maxY;
    
    if(origin.x >= end.x){
        minX = end.x;
        maxX = origin.x;
    }
    else{
        minX = origin.x;
        maxX = end.x;
    }
    
    if(origin.y >= end.y){
        minY = end.y;
        maxY = origin.y;
    }
    else{
        minY = origin.y;
        maxY = end.y;
    }
    
    origin = glm::vec2(minX, minY);
    end = glm::vec2(maxX, maxY);
}

bool BoundingBox::intersectsBox(BoundingBox *box){
    return false;
}