//
//  Object.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Object__
#define __OpenGL_2D_Framework__Object__

//#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <map>
#include "CommonInclude.h"
#include "BoundingBox.h"
#include "Z_Float.h"

/**
 *  \class Object
 *  
 *  \brief The most basic state of class that can be exist.
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
    //global z depth
    Z_Float z_depth;
    
    //Position
    glm::vec3 position;
    
    //Naming
    std::string objectName;
    
    //BoundingBox
    BoundingBox* boundingBox;
    bool needToUpdateBB;
    
    //Childing
    Object* parent;
    
    //OpenGL Matrix
    glm::mat4 translateMat;
    glm::mat4 rotateMat;
    glm::mat4 scaleMat;
    glm::mat4 modelMat;
    
    //0 ~ 360 degree
    GLfloat angle;
    //x,y,z. -1.0 ~ 1.0
    glm::vec3 scale;
    
    //Childing
    bool addChild(Object* child, Object* parent, bool replace = false);
    //TODO: removeObject
    void updateChild();
    void renderChild(glm::mat4 parentModelMat);
    
    /**
     *  Translate to position
     *  @param position A position to translate object
     */
    void translateTo(glm::vec3 position);
    
    /*
     *
     */
    void translateBy(glm::vec3 distance);
    
    //To transformation
    
    void wrapAngle(GLfloat& angle);
    void rotateTo(GLfloat angle, glm::vec3 axis);
    void scaleTo(glm::vec3 scale);
    
    //By transformation
    void rotateBy(GLfloat angle, glm::vec3 axis);
    void scaleBy(glm::vec3 scale);
    
    //Child mapping
    std::multimap<std::string, Object*> childObjectLUT; //look up table
    std::multimap<float, Object*> childObjMap;
    
private:
    void cleanChildList();
    
    void setParent(Object* parent);
    Object* getParent();
    
    //From RenderableObjectManager
//    bool addObject(Scene* scenePtr, std::string objectName, RenderableObject* object, bool replace);
//    bool removeObject(RenderableObject* object, bool deleteObject);
//    bool removeObject(std::string objectName);
    void changeZ(Object* object, float z);
    void changeZDepth(float z);
public:
    Object();
    virtual ~Object();
    
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
    
    //name
    std::string getName();
    void setName(std::string objectName);
    
    //bounding box
    BoundingBox* const getBoundingBox();
    
    //z depth
    void setZDepth(float z);
    bool getZDepth(float& z);
    bool isZValid();
    
    //virtual. 
    virtual void render() = 0;
    virtual void update() = 0;
};

#endif /* defined(__OpenGL_2D_Framework__Object__) */
