//
//  BoundingBox.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__BoundingBox__
#define __OpenGL_2D_Framework__BoundingBox__

//#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class BoundingBox{
    friend class Object;
private:
    glm::vec2 originalOrigin;
    glm::vec2 originalEnd;
    glm::vec2 size;
    //need better design on this!
    
    
    //coordinate datas
    int x;
    int y;
    int w;
    int h;
    
    void updateBoundingBox(glm::mat4 translateMat, glm::mat4 scaledMat, glm::mat4 rotateMat);
    void updatePointWithMax();
public:
    BoundingBox();
    BoundingBox(int x, int y, int w, int h);
    ~BoundingBox();
    
    glm::vec2 origin;
    glm::vec2 end;
    
    bool containsPoint(glm::vec2 point);
    bool intersectsBox(BoundingBox *box);
};

#endif /* defined(__OpenGL_2D_Framework__BoundingBox__) */
