//
//  Object.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Object.h"
#include "Layer.h"

Object::Object():
position(glm::vec3(0, 0, 0)),
parent(0),
needToUpdateBB(false),
boundingBox(0),
translateMat(glm::mat4()),
rotateMat(glm::mat4()),
scaleMat(glm::mat4()),
angle(0),
scale(glm::vec3(1, 1, 1))
{
    cout << "Object::Object()" << endl;
}

Object::~Object(){
    cout << "Object::~Object()" << endl;
    cleanChildList();
}

void Object::cleanChildList(){
    for(auto it : childObjMap){
        if(Layer* layerObj = dynamic_cast<Layer*>(it.second)){
            //if deleting object is layer, call exit so user can release their own stuff
            layerObj->exit();
        }
        delete (it.second);
    }
    //LUT has same pointer with obj map.
}

void Object::setPosition(glm::vec3 position){
    this->position = position;
    translateTo(position);
}

void Object::addPosition(glm::vec3 position){
    this->position += position;
    translateBy(position);
}

void Object::setX(float x){
    this->position.x = x;
    translateTo(this->position);
}

void Object::setY(float y){
    this->position.y = y;
    translateTo(this->position);
}

const glm::vec3 Object::getPosition(){
    return this->position;
}


void Object::translateTo(glm::vec3 position){
    glm::vec3 scaledPos = glm::vec3(position.x / 10, position.y / 10, position.z / 10);
    translateMat = glm::translate(glm::mat4(), scaledPos);
    needToUpdateBB = true;
}

void Object::translateBy(glm::vec3 distance){
    glm::vec3 scaledDistance = glm::vec3(distance.x / 10, distance.y / 10, distance.z / 10);
    translateMat = glm::translate(translateMat, scaledDistance);
    needToUpdateBB = true;
}

void Object::setAngle(GLfloat angle, glm::vec3 axis){
    angle *= (-1);
    rotateTo(angle, axis);
}

void Object::addAngle(GLfloat angle, glm::vec3 axis){
    angle *= (-1);
    rotateBy(angle, axis);
}

void Object::wrapAngle(GLfloat& angle){
    if(angle < 0)
        angle += 360;
    else if(angle > 360)
        angle -= 360;
    else if(angle == 360)
        angle = 0;
}

const GLfloat Object::getAngle(){
    return this->angle;
}

void Object::rotateTo(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1)){
    //rotate in 2d space by default
    wrapAngle(angle);
    rotateMat = glm::rotate(glm::mat4(), angle, axis);
    this->angle = angle;
    needToUpdateBB = true;
}

void Object::rotateBy(GLfloat angle, glm::vec3 axis = glm::vec3(0, 0, 1)){
    //rotate in 2D space by default
    this->angle += angle;
    wrapAngle(this->angle);
    rotateMat = glm::rotate(rotateMat, angle, axis);
    needToUpdateBB = true;
}

const glm::vec3 Object::getScale(){
    return this->scale;
}

const GLfloat Object::getScaleX(){
    return scale.x;
}

const GLfloat Object::getScaleY(){
    return scale.y;
}

const GLfloat Object::getScaleZ(){
    return scale.z;
}

void Object::setScale(glm::vec3 scale){
    scaleTo(scale);
}

void Object::addScale(glm::vec3 scale){
    scaleBy(scale);
}

void Object::scaleTo(glm::vec3 scale){
    this->scale = scale;
    scaleMat = glm::scale(glm::mat4(), scale);
    needToUpdateBB = true;
}

void Object::scaleBy(glm::vec3 scale){
    this->scale += scale;
    scaleMat = glm::scale(glm::mat4(), this->scale);
    needToUpdateBB = true;
}

glm::mat4 Object::getTransformMat(){
    if(this->parent != NULL){
        return this->parent->getTransformMat() * translateMat * rotateMat * scaleMat;
    }
    else{
        return translateMat * rotateMat * scaleMat;
    }
}

std::string Object::getName(){
    return this->objectName;
}

void Object::setName(std::string objectName){
    assert(objectName != "");
    this->objectName = objectName;
}

bool Object::addChild(Object *child, Object *parent, bool replace){
    child->parent = parent;
    
    auto obj_it = childObjectLUT.find(child->objectName);
    
    //LUT
    if(obj_it == childObjectLUT.end()){
        //no object exists with same name. remove
        cout << "Adding object named \"" << child->objectName << "\" to system." << endl;
    }
    else{
        if(replace){
            cout << "Replacing existing object named \"" << child->objectName << "\"." << endl;
            //remove exsiting name on LUT
            childObjectLUT.erase(obj_it);
            //remove from manager
        }
        else{
        }
    }
    
    float objectZ;
    //get Z. If fails, set z as +1 from highest z to render to the most top of scene
    if(!child->getZDepth(objectZ)){
        if(childObjMap.empty()){
            objectZ = 0;
        }
        else{
            auto end_it = childObjMap.end();
            end_it--;
            float lastZ = end_it->first;
            objectZ = lastZ + 1;
            //assign z value because it didn't had one
            child->setZDepth(objectZ);
        }
    }
    
    //Unlikely scene, Layer class can enter in middle of game.
    //So make sure it call init class if it's Layer
    if(Layer* layerObj = dynamic_cast<Layer*>(child)){
        layerObj->init();
    }
    
    //add to map
    childObjMap.insert(std::pair<float, Object*>(objectZ, child));
    //add to LUT
    childObjectLUT.insert(std::pair<std::string, Object*>(child->objectName, child));
    
    return true;
}

bool Object::removechild(Object* child, bool deleteObject){
    std::string objName = child->getName();
    auto objNameIt = childObjectLUT.find(objName);
    if(objNameIt == childObjectLUT.end()){
        cout << "No ojbect with name \"" << objName << "\" found." << endl;
        return false;
    }
    else{
        cout << "Removing object named \"" << objName << "\"." << endl;
        childObjectLUT.erase(objNameIt);
        for(auto objMapIt = childObjMap.begin(); objMapIt != childObjMap.end(); ++objMapIt){
            float z;
            child->getZDepth(z);
            
            if(objMapIt->first == z && objMapIt->second->getName() == objName){
                if(deleteObject)
                    delete objMapIt->second;
                childObjMap.erase(objMapIt);
                break;
            }
        }
        return true;
    }
}

void Object::updateChild(){
    for (auto it = childObjMap.begin(); it != childObjMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            childObjMap.erase(it);
        }
        else{
            //first, update it self so child can have updated parent.
            (it->second)->update();
            //update child's child
            (it->second)->updateChild();
            ++it;
        }
    }
}

void Object::renderChild(){
    for (auto it = childObjMap.begin(); it != childObjMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            childObjMap.erase(it);
        }
        else{
            //first render itself
            (it->second)->render();
            ++it;
        }
    }
    
    //omg double iteration. so bad!
    for (auto it = childObjMap.begin(); it != childObjMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            childObjMap.erase(it);
        }
        else{
            (it->second)->renderChild();
            ++it;
        }
    }
}

BoundingBox* const Object::getBoundingBox(){
    if(this->boundingBox && needToUpdateBB)
        this->boundingBox->updateBoundingBox(
                                             glm::translate(glm::mat4(), this->position),
                                             this->scaleMat,
                                             this->rotateMat);
    needToUpdateBB = false;
    return this->boundingBox;
}

void Object::setZDepth(float z){
    //if this object already had z value, then change in the manager
    if(this->z_depth.dirty){
        //use scene that is bound to this object to call renderable manager
        this->changeZ(this, z);
    }
    //else, change it self.
    else{
        this->z_depth.dirty = true;
        this->z_depth.setZ(z);
    }
}

bool Object::getZDepth(float& z){
    if(this->z_depth.dirty){
        z = this->z_depth.getZ(z);
        return true;
    }
    else{
        return false;
    }
}

bool Object::isZValid(){
    return this->z_depth.dirty;
}

//This function is only called when z_depth has been set. No need to check if it's none
void Object::changeZ(Object *object, float z){
    //check if z is valid
    if(object->isZValid()){
        //if so, check if it can get z
        float curZ;
        if(object->getZDepth(curZ)){
            //check if object is on LUT
            std::string name = object->getName();
            auto nameIt = childObjectLUT.find(name);
            if(nameIt != childObjectLUT.end()){
                //check if
                auto changingIt = childObjMap.find(curZ);
                if(changingIt != childObjMap.end()){
                    childObjMap.erase(changingIt);
                    //can be vulnerable.
                    object->z_depth.setZ(z);
                    childObjMap.insert(std::pair<float, Object*>(z, object));
                }
                else{
                    cout << "object not found in system" << endl;
                }
            }
            else{
                cout << "Object name not found in LUT" << endl;
            }
        }
        else{
            cout << "Z_Depth ERROR: Failed to get z depth value" << endl;
        }
    }
    else{
        //this object doens't have
        cout << "Z_Deprth ERROR: z_depth value not found for this object" << endl;
    }
}
