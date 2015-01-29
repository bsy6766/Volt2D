//
//  SpriteObject.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 12/2/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteObject__
#define __OpenGL_2D_Framework__SpriteObject__

//#include
#include "Program.h"
#include "SpriteAction.h"
#include "ActionMoveTo.h"
#include "Timer.h"
#include "ActionJumpBy.h"
#include "ActionFadeTo.h"
#include "ActionDelay.h"
#include "ActionRotateBy.h"
#include "SpriteActionSchedule.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>

//2D and 3D size is scaled down to 10. 
//ex) 1280 x 640 pixels texture -> 128 * 64 vertex length quad
const int SCREEN_TO_WORLD_SCALE = 10;

const float static GLOBAL_Z_VALUE = 0;

struct Rect{
    //x,y = bottom left
    float x;
    float y;
    float w;
    float h;
};

static int ID_COUNTER = 0;

class SpriteObject{
private:
    void instantUpdate(SpriteAction *actionPtr, std::list<SpriteActionSchedule*>::const_iterator &ci, bool &instantHasNext, bool &sequence);
    void intervalUpdate(SpriteAction *actionPtr, std::list<SpriteActionSchedule*>::const_iterator &ci, bool &instantHasNext, bool &sequence);
	
	winSize size = Scene::getInstance().getWindowSize();
protected:
    int spriteID;
    
    int w;
    int h;
    
    glm::vec2 position;
    Program *progPtr;
    
    bool actionRunning;
    float z;    //each sprite can set 0~100.
    
    Rect boundingBox;
    bool visible;
    
    GLuint vao;    //vertex array object
    GLuint vbo;    //vertex buffer object
    GLuint uvbo;     //uv vert buffer object
    GLuint ibo;    //indices buffer object
    
    glm::mat4 translateMat;
    glm::mat4 rotateMat;
    glm::mat4 scaleMat;
    glm::mat4 modelMat;
    
    std::vector<glm::vec3> vertexData;
    std::vector<glm::vec2> uvVertexData;
    std::vector<GLushort> indicesData;
    
    std::list<SpriteActionSchedule *> spriteActionScheduleList;
    
public:
    SpriteObject();
    SpriteObject(Program *ptr);
    virtual ~SpriteObject();
    
    float opacity;
    float angle;
    
    //position
    void setPosition(glm::vec2 position);
    glm::vec2 getPosition();
    
    //z depth
    void setZ_Depth(float value);
    float getZ_Depth();
    
    //sprite action
    void addAction(SpriteAction *action);
    void addActions(SpriteActionSchedule &actions);
    void runAction();
    void stopAction();
    std::list<SpriteAction*> getSpriteActionList();
    bool isActionRunning();
    
    //init. Derived sprite class must implement their each own vertex data and load as they need
    virtual void createVertexData() = 0;
    virtual void loadVertexData() = 0;
    virtual void render() = 0;
    
//    virtual void update() = 0;
    void update();
    void updateFromSpriteAction();
};

#endif /* defined(__OpenGL_2D_Framework__SpriteObject__) */
