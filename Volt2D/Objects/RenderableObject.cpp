//
//  RenderableObject.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "RenderableObject.h"
#include "Director.h"

using namespace Volt2D;

RenderableObject::RenderableObject():
Object(),
bufferObject({0, 0, 0, 0}),
opacity(255),
visible(true),
width(0),
height(0),
anchorPoint(glm::vec2()),
progPtr(Volt2D::Director::getInstance().getProgramPtr()),   //get default program
actionRunning(false),
useSpriteSheet(false)
{
//    cout << "[SYSTEM::INFO] Creating RednerableObject" << endl;
}

RenderableObject::~RenderableObject(){
    deleteVertexData();
//    cout << "[SYSTEM::INFO] Releasing RenderableObject" << endl;
    for (std::list<ActionSchedule*>::const_iterator ci = actionScheduleList.begin(); ci != actionScheduleList.end(); ++ci){
        delete (*ci);
}
    delete boundingBox;
}

void RenderableObject::setOpacity(GLfloat opacity){
    if(opacity < 0)
        opacity = 0;
    else if(opacity > 255)
        opacity = 255;
    
    this->opacity = opacity;
}

void RenderableObject::addOpacity(GLfloat opacity){
    this->opacity += opacity;
    
    if(this->opacity < 0)
        this->opacity = 0;
    else if(this->opacity > 255)
        this->opacity = 255;
}

GLfloat RenderableObject::getOpacity(){
    return this->opacity;
}

void RenderableObject::deleteVertexData(){
    vertexData.clear();
    uvVertexData.clear();
    indicesData.clear();
    
    glDeleteVertexArrays(1, &bufferObject.vao);
    glDeleteBuffers(1, &bufferObject.vbo);
    glDeleteBuffers(1, &bufferObject.uvbo);
    glDeleteBuffers(1, &bufferObject.ibo);
    
    bufferObject.vao = 0;
    bufferObject.vbo = 0;
    bufferObject.uvbo = 0;
    bufferObject.ibo = 0;
}

void RenderableObject::bindProgram(std::string programName){
    progPtr = Volt2D::Director::getInstance().getProgramPtr(programName);
}

void RenderableObject::addAction(ActionObject* action){
    addAction(action, 0);
}

void RenderableObject::addAction(ActionObject *action, int repeat){
    addActions({action}, repeat);
}

void RenderableObject::addActions(std::initializer_list<ActionObject *> actions, int repeat){
    for(auto it:actions){
        it->bindTarget(this);
    }
    ActionSchedule* singleActionSchedule = new ActionSchedule();
    singleActionSchedule->createSchedule(actions, repeat);
    actionScheduleList.push_back(singleActionSchedule);
}

void RenderableObject::runAction(){
    actionRunning = true;
}

void RenderableObject::stopAllActions(){
    actionRunning = false;
    
    for(std::list<ActionSchedule*>::const_iterator ci = actionScheduleList.begin(); ci != actionScheduleList.end(); ++ci){
        (*ci)->terminateAllAction();
        delete (*ci);
    }
    actionScheduleList.clear();
}

bool RenderableObject::isActionRunning(){
    return actionRunning;
}

void RenderableObject::update(double dt){
    //if there is no action, set running to false and return
    if(actionScheduleList.empty()){
        actionRunning = false;
        return;
    }
    
    //check if object can run action
    if(!actionRunning){
        return;
    }
    
    //    //iterate through schedule list
    for(auto schedule_it = actionScheduleList.begin(); schedule_it != actionScheduleList.end(); ){
        //        cout << "Updating schedule" << endl;
        (*schedule_it)->updateSchedule();
        
        if((*schedule_it)->isEmpty()){
            delete *schedule_it;
            schedule_it = actionScheduleList.erase(schedule_it);
            continue;
        }
        else{
            //not empty, but is done?
            if((*schedule_it)->isFinished()){
                if((*schedule_it)->needRepeat()){
                    //revive, increment counter
//                    cout << "Reviving schedule." << endl;
                    (*schedule_it)->reviveSchedule();
                    schedule_it++;
                }
                else{
                    //repeat done. delete list
//                    cout << "Repeat done. deleting list." << endl;
                    delete *schedule_it;
                    schedule_it = actionScheduleList.erase(schedule_it);
                    continue;
                }
                
            }
            else{
                schedule_it++;
            }
        }
    }
}

void RenderableObject::intUniformLocation(std::string name, int& i){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    glUniform1i(uniformLocation, i);
}

void RenderableObject::floatUniformLocation(std::string name, float& f){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    glUniform1fv(uniformLocation, 1, &f);
}

void RenderableObject::boolUniformLocation(std::string name, bool b){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    if(b)
        glUniform1i(uniformLocation, 1);
    else
        glUniform1i(uniformLocation, 0);
}

void RenderableObject::vec3UniformLocation(std::string name, glm::vec3 &vec){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    glUniform3fv(uniformLocation, 1, &vec[0]);
}

void RenderableObject::matrixUniformLocation(std::string name, glm::mat4 &matrix){
    GLint uniformLocation = glGetUniformLocation(progPtr->getObject(), name.c_str());
    if(uniformLocation == -1)
        throw std::runtime_error( std::string("Program uniform not found: " ) + name);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
}

void RenderableObject::setAnchrPoint(glm::vec2 anchorPoint){
    this->anchorPoint = anchorPoint;
    glm::vec3 anchorDistance = glm::vec3();
    float shiftX = -anchorPoint.x * this->width;
    float shiftY = -anchorPoint.y * this->height;
    anchorDistance = glm::vec3(shiftX, shiftY, 0);
    this->modelMat = glm::translate(glm::mat4(), anchorDistance);
}