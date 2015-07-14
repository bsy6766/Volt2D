//
//  RenderableObject.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "RenderableObject.h"

RenderableObject::RenderableObject():
Object(),
vao(0),
vbo(0),
uvbo(0),
ibo(0),
translateMat(glm::mat4()),
rotateMat(glm::mat4()),
scaleMat(glm::mat4()),
modelMat(glm::mat4()),
angle(0),
scale(glm::vec3(1, 1, 1)),
opacity(255),
visible(true),
progPtr(Director::getInstance().getProgramPtr()),   //get default program
actionRunning(false),
needToUpdateBB(false),
boundingBox(0)
{
    cout << "RenderableObject::RenderableObject()" << endl;
//    translateTo(position);
//    rotateTo(angle, glm::vec3(0, 0, 1));
//    scaleTo(scale);
//    setOpacity(opacity);
//    progPtr = Director::getInstance().getProgramPtr();
}

RenderableObject::~RenderableObject(){
    deleteVertexData();
    cout << "Deleting Renderable Object" << endl;
    for (std::list<ActionSchedule*>::const_iterator ci = actionScheduleList.begin(); ci != actionScheduleList.end(); ++ci){
        delete (*ci);
    }
    delete boundingBox;
}

void RenderableObject::setPosition(glm::vec3 position){
    this->position = position;
    translateTo(position);
}

void RenderableObject::addPosition(glm::vec3 position){
    this->position += position;
    translateBy(position);
}

void RenderableObject::setX(float x){
    this->position.x = x;
    translateTo(this->position);
}

void RenderableObject::setY(float y){
    this->position.y = y;
    translateTo(this->position);
}

void RenderableObject::translateTo(glm::vec3 position){
    glm::vec3 scaledPos = glm::vec3(position.x / 10, position.y / 10, position.z / 10);
    translateMat = glm::translate(glm::mat4(), scaledPos);
    needToUpdateBB = true;
}

void RenderableObject::translateBy(glm::vec3 distance){
    glm::vec3 scaledDistance = glm::vec3(distance.x / 10, distance.y / 10, distance.z / 10);
    translateMat = glm::translate(translateMat, scaledDistance);
    needToUpdateBB = true;
}

void RenderableObject::setAngle(GLfloat angle, glm::vec3 axis){
    angle *= (-1);
    rotateTo(angle, axis);
}

void RenderableObject::addAngle(GLfloat angle, glm::vec3 axis){
    angle *= (-1);
    rotateBy(angle, axis);
}

void RenderableObject::wrapAngle(GLfloat& angle){
    if(angle < 0)
        angle += 360;
    else if(angle > 360)
        angle -= 360;
    else if(angle == 360)
        angle = 0;
}

GLfloat RenderableObject::getAngle(){
    return this->angle;
}

void RenderableObject::rotateTo(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1)){
    //rotate in 2d space by default
    wrapAngle(angle);
    rotateMat = glm::rotate(glm::mat4(), angle, axis);
    this->angle = angle;
    needToUpdateBB = true;
}

void RenderableObject::rotateBy(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1)){
    //rotate in 2D space by default
    this->angle += angle;
    wrapAngle(this->angle);
    rotateMat = glm::rotate(rotateMat, angle, axis);
    needToUpdateBB = true;
}

glm::vec3 RenderableObject::getScale(){
    return this->scale;
}

GLfloat RenderableObject::getScaleX(){
    return scale.x;
}

GLfloat RenderableObject::getScaleY(){
    return scale.y;
}

GLfloat RenderableObject::getScaleZ(){
    return scale.z;
}

void RenderableObject::setScale(glm::vec3 scale){
    scaleTo(scale);
}

void RenderableObject::addScale(glm::vec3 scale){
    scaleBy(scale);
}

void RenderableObject::scaleTo(glm::vec3 scale){
    this->scale = scale;
    scaleMat = glm::scale(glm::mat4(), scale);
    needToUpdateBB = true;
}

void RenderableObject::scaleBy(glm::vec3 scale){
    this->scale += scale;
    scaleMat = glm::scale(glm::mat4(), this->scale);
    needToUpdateBB = true;
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
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uvbo);
    glDeleteBuffers(1, &ibo);
    
    vao = 0;
    vbo = 0;
    uvbo = 0;
    ibo = 0;
}

void RenderableObject::initBoundingBox(int w, int h){
    boundingBox->w = w;
    boundingBox->h = h;
    boundingBox->x = ((-1) * w) / 2;
    boundingBox->y = ((-1) * h) / 2;
}

void RenderableObject::bindProgram(std::string programName){
    progPtr = Director::getInstance().getProgramPtr(programName);
}

void RenderableObject::addAction(ActionObject* action){
    addAction(action, 0);
}

void RenderableObject::addAction(ActionObject *action, int repeat){
//    cout << "Adding Action " << action->getActionID() << " to Sprite #" << spriteID << std::endl;
    //bind owner
//    action->bindOwnerPtr(this);
//    ActionSchedule* singleActionSchedule = new ActionSchedule();
//    singleActionSchedule->createSchedule(action, repeat);
//    actionScheduleList.push_back(singleActionSchedule);
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

void RenderableObject::stopAction(){
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

void RenderableObject::update(){
    //if there is no action, set running to false and return
    if(actionScheduleList.empty()){
        actionRunning = false;
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
                    cout << "Reviving schedule." << endl;
                    (*schedule_it)->reviveSchedule();
                    schedule_it++;
                }
                else{
                    //repeat done. delete list
                    cout << "Repeat done. deleting list." << endl;
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

void RenderableObject::setZDepth(float z){
    //if this object already had z value, then change in the manager
    if(this->z_depth.dirty){
        //use scene that is bound to this object to call renderable manager
        this->scene->getRenderableObjectManager()->changeZ(this, z);
    }
    //else, change it self.
    else{
        this->z_depth.dirty = true;
        this->z_depth.z = z;
    }
}

//only
void RenderableObject::changeZDepth(float z){
    this->z_depth.z = z;
}

bool RenderableObject::getZDepth(float& z){
    if(this->z_depth.dirty){
        z = this->z_depth.z;
        return true;
    }
    else{
        return false;
    }
}

bool RenderableObject::isZValid(){
    return this->z_depth.dirty;
}

void RenderableObject::bindScene(Scene *scenePtr){
    this->scene = scenePtr;
}

void RenderableObject::unbindScene(){
    this->scene = 0;
}

BoundingBox* const RenderableObject::getBoundingBox(){
    if(this->boundingBox && needToUpdateBB)
        this->boundingBox->updateBoundingBox(
                                             glm::translate(glm::mat4(), this->position),
                                             this->scaleMat,
                                             this->rotateMat);
    needToUpdateBB = false;
    return this->boundingBox;
}