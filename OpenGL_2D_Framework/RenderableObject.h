//
//  RenderableObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__RenderableObject__
#define __OpenGL_2D_Framework__RenderableObject__

#include "Object.h"
#include "Program.h"
#include "ActionSchedule.h"
#include "Scene.h"
#include <vector>
#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

/**
 *  @struct BufferObject
 *  @brief Contains vertex array object and buffer objects
 */
struct BufferObject{
    GLuint vao;
    GLuint vbo;
    GLuint uvbo;
    GLuint ibo;
};

/**
 *  @class RenderableObject
 *  @brief A object that is renderable on screen. Contains several OpenGL varaibles.
 *  \todo Support anchor point for all object.
 */
class RenderableObject : public Object{
protected:
    /**
     *  A pack of essential OpenGL objects
     */
    BufferObject bufferObject;
    
    /**
     *  A std::vector that stores all vertices
     */
    std::vector<glm::vec3> vertexData;
    
    /**
     *  A std::vector that stores all uv vertices
     */
    std::vector<glm::vec2> uvVertexData;
    
    /**
     *  A std::vector that stores all indices
     */
    std::vector<GLushort> indicesData;
    
    /**
     *  Object's scaled size
     */
    float width;
    
    /**
     *  Object's scaled size
     */
    float height;
    
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
    
    /**
     *  Pointer to rendering OpenGL Progream.
     */
    Program *progPtr;
    
    /**
     *  Flag of action running
     */
    bool actionRunning;
    
    /**
     *  List of ActionSchedule.
     */
    std::list<ActionSchedule *> actionScheduleList;
    
    /**
     *  Pass int value to shader
     *  @param name Uniform name
     *  @param i (ref) A int value to pass to shader
     */
    void intUniformLocation(std::string name, int& i);
    /**
     *  Pass float value to shader
     *  @param name Uniform name
     *  @param f (ref) A float value to pass to shader
     */
    void floatUniformLocation(std::string name, float& f);
    
    /**
     *  Pass bool value to shader
     *  @param name Uniform name
     *  @param b A bool value to pass to shader
     */
    void boolUniformLocation(std::string name, bool b);
    
    /**
     *  Pass glm::vec3 value to shader
     *  @param name Uniform name
     *  @param vec (ref) A glm::vec3 value to pass to shader
     */
    void vec3UniformLocation(std::string name, glm::vec3& vec);
    
    /**
     *  Pass glm::mat4 value to shader
     *  @param name Uniform name
     *  @param matrix A glm::mat4 value to pass to shader
     */
    void matrixUniformLocation(std::string name, glm::mat4& matrix);
private:

public:
    RenderableObject();
    virtual ~RenderableObject();
    
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
    void setAnchrPoint(glm::vec2 anchorPoint);
    
    /**
     *  Clear vertices and indices vectors and delete buffer objects.
     */
    void deleteVertexData();
    
    /**
     *  Bind OpenGL Program to object.
     *  @param programName A OpenGL Program name to bind. This program will be used to render
     */
    void bindProgram(std::string programName);
    
    /**
     *  Visibility.
     */
    bool visible;
    
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
     *  Implements Object::update()
     */
    virtual void update(double dt);
};

#endif /* defined(__OpenGL_2D_Framework__RenderableObject__) */
