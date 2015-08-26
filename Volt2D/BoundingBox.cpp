//
//  BoundingBox.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "BoundingBox.h"

using namespace Volt2D;

BoundingBox::BoundingBox(float o_x, float o_y, float e_x, float e_y):
origin(glm::vec2(o_x, o_y)),
end(glm::vec2(e_x, e_y)),
originalOrigin(glm::vec2(o_x, o_y)),
originalEnd(glm::vec2(e_x, e_y)),
size(e_x - o_x, e_y - o_y)
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

void BoundingBox::updateBoundingBox(glm::mat4 translateMat, glm::mat4 scaledMat, glm::mat4 rotateMat, glm::mat4 modelMat){
    glm::vec4 castedOrigin = glm::vec4(originalOrigin.x, originalOrigin.y, 1, 1);
    glm::vec4 castedEnd = glm::vec4(originalEnd.x, originalEnd.y, 1, 1);
    glm::mat4 bbMat = glm::mat4() * translateMat * rotateMat * scaledMat * modelMat;
    origin = glm::vec2(bbMat * castedOrigin);
    end = glm::vec2(bbMat * castedEnd);
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
    size = glm::vec2(maxX - minX, maxY - minY);
}

bool BoundingBox::intersectsBox(BoundingBox *box){
    return false;
}