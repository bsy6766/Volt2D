//
//  BoundingBox.h
//  Volt2D
//
//  Created by Seung Youp Baek on 4/20/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__BoundingBox__
#define __Volt2D__BoundingBox__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Volt2D{
/**
 *  @class BoundingBox
 *  @brief A Bounding box for an Object
 */
class BoundingBox{
    friend class Object;
private:
    /**
     *  Original Origin point when the bounding box were made.
     *  This is used to update tranformed origin point.
     */
    glm::vec2 originalOrigin;
    
    /**
     *  Original End point when the bounding box were made.
     *  This is used to update tranformed end point.
     */
    glm::vec2 originalEnd;

    /**
     *  Update bounding box with Object's transformation matrix
     */
    void updateBoundingBox(glm::mat4 translateMat, glm::mat4 scaledMat, glm::mat4 rotateMat);
    
    /**
     *  Reorganize updated origin and end point
     */
    void updatePointWithMax();
public:
    //Constructor
    BoundingBox(int x, int y, int w, int h);
    //Destructor
    ~BoundingBox();
    
    /**
     *  Current bounding box's origin point(Most left low point)
     */
    glm::vec2 origin;
    
    /**
     *  Current bounding box's end point(Most right high point)
     */
    glm::vec2 end;
    
    /**
     *  Point - BoundingBox collision detection
     *  @return true if point is in bounding box. Else, false.
     */
    bool containsPoint(glm::vec2 point);
    
    /**
     *  BoundingBox - BoundingBox collision detection
     *  @return true if two bounding boxs collide. Else, false.
     */
    bool intersectsBox(BoundingBox *box);
};
}   //namespace end

#endif /* defined(__Volt2D__BoundingBox__) */
