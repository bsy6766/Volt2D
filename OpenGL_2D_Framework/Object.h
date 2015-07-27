//
//  Object.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Object__
#define __OpenGL_2D_Framework__Object__

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <map>
#include "CommonInclude.hpp"
#include "BoundingBox.h"
#include "Z_Float.h"

/**
 *  @class Object
 *  
 *  @brief The most basic state of class that can be exist.
 *
 *  This class is the highest base class. 
 *  All object that exists in system will inherite this class.
 *  Object class itself has no rendering feature.
 *  However, it will have position, boundingbox and transform matrixes
 *  to exists as an virtual object in the scene. (like invisible tracking node)
 *  To actually render the object, you will have to use RenderableObject.
 */

class Object{
protected:
    /**
     *  ture if alive. False if dead. 
     *  Object gets deleted on next update iteration when it's dead.
     */
    bool alive;
    
    /**
     *  Z depth. See Z_Float class for detail.
     */
    Z_Float z_depth;
    
    /**
     *  A vec3 position of object. Z is almost always 0.
     */
    glm::vec3 position;
    
    /**
     *  Object name
     */
    std::string objectName;
    
    /**
     *  A bonding box. See BoundingBox class for detail.
     */
    BoundingBox* boundingBox;
    
    /**
     *  A update flag for bounding box. 
     *  If true, it updates bounding box and it becomes true when ever object moves, rotates, or scales.
     */
    bool needToUpdateBB;
    
    /**
     *  Pointer to parent
     */
    Object* parent;
    
    /**
     *  Model matrix. Anchor point applies first here.
     */
    glm::mat4 modelMat;
    
    /**
     *  Translation matrix
     */
    glm::mat4 translateMat;
    
    /**
     *  Rotation matrix
     */
    glm::mat4 rotateMat;
    
    /**
     *  Scale matrix
     */
    glm::mat4 scaleMat;
    
    /**
     *  Angle of object. 
     *  @note max = 360, min = 0
     */
    GLfloat angle;
    
    /**
     *  Scale axis of object. Each attrib represent each axis
     */
    glm::vec3 scale;
    
    /**
     *  Add child
     *  @param child A child object to add
     *  @param parent A parent to bind
     *  @param replace A replace flag. true will replace existing object.
     */
    bool addChild(Object* child, Object* parent, bool replace = false);
    
    /**
     *  Remove child from object
     *  @param child A object to remove
     *  @param deleteObject true if you want to delete object and release from memory. Else, false.
     */
    bool removechild(Object* child, bool deleteObject);
    
    /**
     *  Update all children objects that object has
     */
    void updateChild(double dt);
    
    /**
     *  Render all children objects that object has
     */
    void renderChild();
    
    /**
     *  Translate to position
     *  @param position A vec3 position to translate object
     */
    void translateTo(glm::vec3 position);
    
    /**
     *  Translate by distance
     *  @param distance A vec3 distance to add on current object's position
     */
    void translateBy(glm::vec3 distance);
    
    /**
     *  Wrap angle with boundary of 0 ~ 360 in degree.
     *  @param (ref) angle A reference angle to wrap.
     */
//    void wrapAngle(GLfloat& angle);
    
    /**
     *  Rotate to specific angle with axis
     *  @param angle A angle in degree to set
     *  @param axis A vec3 axis to rotate.
     */
    void rotateTo(GLfloat angle, glm::vec3 axis);
    
    /**
     *  Rotate by specific angle with axis
     *  @param angle A angle in degree to add on current object's angle
     *  @param axis A vec3 axis to rotate.
     */
    void rotateBy(GLfloat angle, glm::vec3 axis);
    
    /**
     *  Scale object to specific scale
     *  @param scale A vec3 scale to set
     */
    void scaleTo(glm::vec3 scale);
    
    /**
     *  Scale object by some amount of scale
     *  @param scale A vec3 scale to add on current object's scale
     */
    void scaleBy(glm::vec3 scale);
    
    //Child mapping
    std::multimap<std::string, Object*> childObjectLUT; //look up table
    std::multimap<float, Object*> childObjMap;
    
private:
    /**
     *  Cleans all child(children) that is added to this object
     */
    void cleanChildList();
    
    /**
     *  Change z order of object. Reorder the rendering order with new z.
     */
    void changeZ(Object* object, float z);
public:
    /**
     *  Constructor
     */
    Object();
    
    /**
     *  Virtual destructor
     */
    virtual ~Object();
    
    /**
     *  Get this object's model matrix (= T * R * S).
     *  @return Object's model matrix
     */
    glm::mat4 getTransformMat();
    
    /// @{
    /// @name Setters and Getters for Position, Angle, and Scale
    /**
     *  Set position
     *  @param position A new vec3 position to overwrite current object's position
     */
    void setPosition(glm::vec3 position);
    
    /**
     *  Add position
     *  @param position A new vec3 position to add on current position of object
     */
    void addPosition(glm::vec3 position);
    
    /**
     *  Get position
     *  @return (const) Get object's current position
     */
    const glm::vec3 getPosition();
    
    /**
     *  Set x position of object
     *  @param x A value of x position to set
     */
    void setX(float x);
    
    /**
     *  Set y position of object
     *  @param y A value of y position to set
     */
    void setY(float y);
    
    /**
     *  Set Angle
     *  @param angle An angle in degree to overwrite object's current angle
     *  @param axis An rotation axis. Set to Z-Axis by default.
     */
    void setAngle(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1));
    
    /**
     *  Add angle
     *  @param angle An angle in degree to add on current angle of object
     *  @param axis An rotation axis. Set toZ-Axis by default.
     */
    void addAngle(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1));
    
    /**
     *  Get angle
     *  @Return (const) A float value of current angle of object in degree
     */
    const GLfloat getAngle();
    
    /**
     *  Set scale
     *  @note 1.0 is a default scale.
     *  @param A vec3 scale value to overwrite object's current scale
     */
    void setScale(glm::vec3 scale);
    
    /**
     *  Add scale
     *  @note 1.0 is a default scale.
     *  @param A vec3 scale value to add on object's current scale
     */
    void addScale(glm::vec3 scale);
    
    /**
     *  Get scale
     *  @return (const) A vec3 scale value of object
     */
    const glm::vec3 getScale();
    
    /**
     *  Get scale x value
     *  @return (const) A float x value of scale
     */
    const GLfloat getScaleX();
    
    /**
     *  Get scale y value
     *  @return (const) A float y value of scale
     */
    const GLfloat getScaleY();
    
    /**
     *  Get scale z value
     *  @return (const) A float z value of scale
     */
    const GLfloat getScaleZ();
    /// @}
    
    /**
     *  Get name of object
     *  @return Name of object.
     */
    std::string getName();
    
    /**
     *  Set name of object. Overwrites name.
     */
    void setName(std::string objectName);
    
    /**
     *  Get bounding box. 
     *  @return (const) A BoundingBox pointer
     */
    BoundingBox* const getBoundingBox();
    
    /**
     *  Set the z order for object.
     *  If z_depth was already set and added to an object, it will change to new z and reorder.
     *  Else, it will set the new z order to object.
     *  @param z New z order to set
     */
    void setZDepth(float z);
    
    /**
     *  Get Z order for this object.
     *  @param (ref) A reference of z to retrieve z order
     *  @return true if object has z. Else, false.
     */
    bool getZDepth(float& z);
    
    /**
     *  Check if z has been set for this object
     *  @return true if object has z order. Else, false.
     */
    bool isZValid();
    
    /**
     *  Virtual function for rendering
     */
    virtual void render() = 0;
    
    /**
     *  Virtual function for updating.
     */
    virtual void update(double dt) = 0;
    
    /**
     *  true if object is dead and ready to get released.
     */
    bool isDead();
    
    /**
     *  Release this object. 
     */
    void release();
};

#endif /* defined(__OpenGL_2D_Framework__Object__) */
