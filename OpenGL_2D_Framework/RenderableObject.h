//
//  RenderableObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__RenderableObject__
#define __OpenGL_2D_Framework__RenderableObject__

//#define GLM_FORCE_RADIANS

#include "Object.h"
#include "Program.h"
#include "ActionSchedule.h"
#include "Scene.h"
#include <vector>
#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class RenderableObject : public Object{
protected:    
    //scene bounded to
    Scene* scene;
    
    //vertex array and buffers
    GLuint vao;		//vertex array object
    GLuint vbo;		//vertex buffer object
    GLuint uvbo;	//uv vert buffer object
    GLuint ibo;		//indices buffer object
    
    //vertex, texture coordinate and index data
    std::vector<glm::vec3> vertexData;
    std::vector<glm::vec2> uvVertexData;
    std::vector<GLushort> indicesData;
    
    //0~255
    GLfloat opacity;
    
    //for rendering with shader
    Program *progPtr;
    
    //Action
    bool actionRunning;
    std::list<ActionSchedule *> actionScheduleList;
    
    //Rendering
    void floatUniformLocation(std::string name, float& f);
    void boolUniformLocation(std::string name, bool b);
    void vec3UniformLocation(std::string name, glm::vec3& vec);
    void matrixUniformLocation(std::string name, glm::mat4& matrix);
private:

public:
    RenderableObject();
    virtual ~RenderableObject();
    
    //opacity getter setter
    void setOpacity(GLfloat opacity);
    void addOpacity(GLfloat opacity);
    GLfloat getOpacity();
    
    //scene
    void bindScene(Scene* scenePtr);
    void unbindScene();
    
    virtual void computeVertexData() = 0;
    virtual void loadVertexData() = 0;
    virtual void render() = 0;
    
    //clear vertex std::vectors and delete buffer.
    void deleteVertexData();
    
    //program
    void bindProgram(std::string programName);
    
    //visibility. Making this public because it harms nothing.
    bool visible;
    
    // action
    void addAction(ActionObject* action);
    void addAction(ActionObject* action, int repeat);
    
    //some child class can override for their own protection of adding actions
    virtual void addActions(std::initializer_list<ActionObject*> actions, int repeat);
    void runAction();
    void stopAction();
    bool isActionRunning();
    void update();
};

#endif /* defined(__OpenGL_2D_Framework__RenderableObject__) */
