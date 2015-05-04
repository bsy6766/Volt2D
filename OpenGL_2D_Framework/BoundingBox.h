//
//  BoundingBox.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__BoundingBox__
#define __OpenGL_2D_Framework__BoundingBox__

#include <glm/glm.hpp>

class BoundingBox{
private:
    glm::vec2 origin;
    glm::vec2 end;
    glm::vec2 size;
public:
    BoundingBox();
    BoundingBox(int x, int y, int w, int h);
    ~BoundingBox();
    
    bool containsPoint(glm::vec2 point);
    bool intersectsBox(BoundingBox *box);
    
    void updateMatrix();
    
    //coordinate datas
    int x;
    int y;
    int w;
    int h;
};

#endif /* defined(__OpenGL_2D_Framework__BoundingBox__) */
