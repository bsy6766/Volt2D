//
//  Camera.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/10/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Camera__
#define __OpenGL_2D_Framework__Camera__

#include <GL/glew.h>
#include "Utility.hpp"

/**
 *  @class Camera
 *  @brieft Camera class for OpenGL. Just simple View * Projection
 *  \todo Make Camera compute aspect response to application's window size
 *  \todo Make Camera let set near and far clip by user
 */
class Camera{
private:
    /**
     *  Position of camera
     */
    glm::vec3 position;
    
    /// @{
    /// @name Camera attributes
    /**
     * Fovy (Field of view)
     */
    GLfloat fovy;
    
    /**
     *  Screen aspect. Fixed with 1.6f
     */
    GLfloat aspect;
    
    /**
     *  Near clip. Fixed to 0.01f
     */
    GLfloat nears;
    
    /**
     *  Far clip. Fixed to 200.0f
     */
    GLfloat fars;
    
    /**
     *  Camera veiw's vertical angle. 0 ~ 360 in degree
     */
    GLfloat verticalAngle;
    
    /**
     *  Camera view's horizontal angle. 0 ~ 360 in degree
     */
    GLfloat horizontalAngle;
    
    /**
     *  Speed of camera movement
     */
    GLfloat speed;
    
public:
    /**
     *  Constructor
     */
    Camera(float screenWidth, float screenHeight, float SCREEN_TO_WORLD_SCALE);
    
    //Destructor
    ~Camera();
    
    /// @{
    /// @name Camera getters
    /**
     *  Get camera projection. 
     *  Calls glm::perspective
     */
    glm::mat4 getProjection() const;
    
    /**
     *  Get camera matrix (projection * view)
     */
    glm::mat4 getMatrix() const;
    
    /**
     *  Get view Matrix
     */
    glm::mat4 getView() const;
    
    /**
     *  Get camera orientation
     */
    glm::mat4 getOrientation() const;
    
    /**
     *  Get camera's position
     */
    glm::vec3 getPosition() const;
    
    /**
     *  Get camera view's vertical angle
     */
    GLfloat getVerticalAngle() const;
    
    /**
     *  Get camera view's horizontal angle
     */
    GLfloat getHorizontalAngle() const;
    /// @}
    
    /// @{
    /// @name Camera setters
    /**
     *  Set camera's position
     */
    void setPosition(glm::vec3 position);
    
    /**
     *  Set camera view's angle
     */
    void changeAngle(double verticalValue, double horizontalValue);
    /// @}
    
    /// @{
    /// @name Camera movement functions
    
    /**
     *  Move camera foward
     */
    void moveFoward();
    
    /**
     *  Move camera backward
     */
    void moveBackward();
    
    /**
     *  Move camera right
     */
    void moveRight();
    
    /**
     *  Move camera left
     */
    void moveLeft();
    
    /**
     *  Move camera up
     */
    void moveUp();
    
    /**
     *  Move camera down
     */
    void moveDown();
    /// @}
    
    /// @{
    /// @name Speed modifiers
    
    /**
     *  Increase camera movement speed
     */
    void increaseSpeed();
    
    /**
     *  Decrease camera movement speed
     */
    void decreaseSpeed();
    /// @}
};

#endif /* defined(__OpenGL_2D_Framework__Camera__) */
