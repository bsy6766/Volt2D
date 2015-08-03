//
//  Object.h
//  Volt2D
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Object__
#define __Volt2D__Object__

#include <GL/glew.h>
#include <map>
#include "Utility.hpp"
#include "ActionSchedule.h"
#include "BoundingBox.h"
#include "Z_Float.h"

namespace Volt2D{
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
     *  Protected constructor
     */
    Object();
    
    /**
     *  ture if alive. False if dead. 
     *  Object gets deleted on next update iteration when it's dead.
     */
    bool alive;
    
    /**
     *  true if object auto relase at destruction.
     */
    bool autoRelease;
    
    /**
     *  Z depth. See Z_Float class for detail.
     */
    Volt2D::Z_Float z_depth;
    
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
    Volt2D::BoundingBox* boundingBox;
    
    /**
     *  A update flag for bounding box. 
     *  If true, it updates bounding box and it becomes true when ever object moves, rotates, or scales.
     */
    bool needToUpdateBB;
    
    /** Flag of action running */
    bool actionRunning;
    
    /** List of ActionSchedule */
    std::list<ActionSchedule *> actionScheduleList;
    
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
    GLfloat angleX;
    GLfloat angleY;
    GLfloat angleZ; //Z is base
    
    /**
     *  Scale axis of object. Each attrib represent each axis
     */
    glm::vec3 scale;
    
    /**
     *  Anchor point.
     *  @note Default is (0, 0). Max 0.5(top, right), Min -0.5(bot, left)
     */
    glm::vec2 anchorPoint;
    
    /**
     *  A opacity of this object.
     *  max = 255, min = 0
     */
    GLfloat opacity;
    
    /** Object's scaled size */
    float scaledWidth;
    
    /** Object's scaled size */
    float scaledHeight;
    
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
     *  Rotate to specific angle with axis
     *  @param angle A angle in degree to set
     *  @param axis A vec3 axis to rotate.
     */
    void rotateTo(GLfloat angle, glm::vec3 axis = Z_AXIS);
    
    /**
     *  Rotate by specific angle with axis
     *  @param angle A angle in degree to add on current object's angle
     *  @param axis A vec3 axis to rotate.
     */
    void rotateBy(GLfloat angle, glm::vec3 axis = Z_AXIS);
    
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
     * Change z order of object. Reorder the rendering order with new z.
     */
    void changeZ(Object* object, float z);
public:
    /** Virtual destructor */
    virtual ~Object();
    
    /**
     *  Get transformative matrix from the highest parent to the object it self.
     *  @return Transformative matrix
     */
    glm::mat4 getTransformMat();
    
    /**
     *  Get transformative matrix from only Scene and Layer.
     *  @return Transformative matrix from Scene and Layer only
     */
    glm::mat4 getSceneAndLayerTransformMat();
    
    /**
     *  Get transformative matrix from highest parent to object itself, excluding Scene and Layer.
     *  @return Transformative matrix excluding Scene and Layer
     */
    glm::mat4 getTransformMatWithOutSceneAndLayer();
    
    /**
     *  Get this object's hierarchal position. 
     *  All position from parent objects will be sumed on return
     *  @return Object's real position on screen
     */
    glm::vec3 getHierarchalPosition();
    
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
    void setAngle(GLfloat angle, glm::vec3 axis = Z_AXIS);
    
    /**
     *  Add angle
     *  @param angle An angle in degree to add on current angle of object
     *  @param axis An rotation axis. Set toZ-Axis by default.
     */
    void addAngle(GLfloat angle, glm::vec3 axis = Z_AXIS);
    
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
    
    /**
     *  Set opacity ot current object
     *  @param A opcity value to set.
     */
    void setOpacity(GLfloat opacity);
    
    /**
     *  Add opacity to current object's opacity.
     *  Opacity can not be greater than 255 or less than 255
     *  @param opacity A opacity value to add.
     */
    void addOpacity(GLfloat opacity);
    
    /**
     *  Get object's opacity
     *  @return Object's opacity
     */
    GLfloat getOpacity();
    
    /**
     *  Set object's anchor point
     */
    void setAnchorPoint(glm::vec2 anchorPoint);
    
    /** Get anchor point */
    glm::vec2 getAnchorPoint();
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
    Volt2D::BoundingBox* const getBoundingBox();
    
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
     *  Add single action.
     *  This will call RenderableObject::addAction(ActionObject*, int) with 0 repeat.
     *  @param action An ActionObject to add
     */
    void addAction(ActionObject* action);
    
    /**
     *  Add single action with desired repeat.
     *  @param action An ActionObject to add
     *  @param repeat A number to repeat action
     */
    void addAction(ActionObject* action, int repeat);
    
    /**
     *  Add multiple action.
     *  @param actions A std::initializer_list with ActionObject*
     *  @param repeat A number to repeat action
     */
    virtual void addActions(std::initializer_list<ActionObject*> actions, int repeat);
    
    /**
     *  Run the action
     *  This set RenderableObject::actionRunning to true
     */
    void runAction();
    
    /**
     *  Stop all actions that this object has and deletes
     */
    void stopAllActions();
    
    /**
     *  Tells if object currently running action objects.
     *  @Return A bool that represent wether this object is running action or not
     */
    bool isActionRunning();
    
    /**
     *  Virtual function for rendering
     */
    virtual void render() = 0;
    
    /**
     *  Virtual function for updating.
     */
    virtual void update(double dt);
    
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
     *  true if object is dead and ready to get released.
     */
    bool isDead();
    
    /**
     *  Release this object. 
     */
    void release();
};
}   //namespace end
    
#endif /* defined(__Volt2D__Object__) */
