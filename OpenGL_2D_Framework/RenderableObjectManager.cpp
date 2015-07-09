//
//  RenderableObjectManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/8/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "RenderableObjectManager.h"
#include "RenderableObject.h"

RenderableObjectManager::RenderableObjectManager(){
    cout << "RenderableObjectManager()" << endl;
}

RenderableObjectManager::~RenderableObjectManager(){
    cout << "~RenderableObjectManager()" << endl;
}

bool RenderableObjectManager::addObject(Scene* scenePtr, std::string objectName, RenderableObject *object, bool replace){
    assert(!objectName.empty());
    
    object->setName(objectName);
    
    auto obj_it = objNameLUT.find(objectName);
    if(obj_it == objNameLUT.end()){
        //no object exists with same name. remove
        cout << "Adding object named \"" << objectName << "\" to system." << endl;
    }
    else{
        if(replace){
            cout << "Replacing existing object named \"" << objectName << "\"." << endl;
            //remove exsiting name on LUT
            objNameLUT.erase(obj_it);
            //remove from manager
        }
        else{
            cout << "Object name \"" << objectName << "\" already exists." << endl;
            return false;
        }
    }
    
    //add to manager and add to LUT
    objNameLUT.insert(std::pair<std::string, RenderableObject*>(objectName, object));
    float objectZ;
    //get Z. If fails, set z as +1 from highest z to render to the most top of scene
    if(!object->getZDepth(objectZ)){
        if(objMap.empty()){
            objectZ = 0;
        }
        else{
            auto end_it = objMap.end();
            end_it--;
            float lastZ = end_it->first;
            objectZ = lastZ + 1;
            //assign z value because it didn't had one
            object->setZDepth(objectZ);
        }
    }
    if(scenePtr)
        object->bindScene(scenePtr);
    objMap.insert(std::pair<float, RenderableObject*>(objectZ, object));
    
    return true;
}

bool RenderableObjectManager::removeObject(RenderableObject *object, bool deleteObject){
    std::string objName = object->getName();
    auto objNameIt = objNameLUT.find(objName);
    if(objNameIt == objNameLUT.end()){
        cout << "No ojbect with name \"" << objName << "\" found." << endl;
        return false;
    }
    else{
        cout << "Removing object named \"" << objName << "\"." << endl;
        objNameLUT.erase(objNameIt);
        for(auto objMapIt = objMap.begin(); objMapIt != objMap.end(); ++objMapIt){
            float z;
            object->getZDepth(z);
            
            if(objMapIt->first == z && objMapIt->second->getName() == objName){
                if(deleteObject)
                    delete objMapIt->second;
                objMap.erase(objMapIt);
                break;
            }
        }
        return true;
    }
}

bool RenderableObjectManager::removeObject(std::string objectName){
    //Todo:: implement this!
    return true;
}

void RenderableObjectManager::update(){
    for (auto it = objMap.begin(); it != objMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            objMap.erase(it);
        }
        else{
            (it->second)->update();
            ++it;
        }
    }
}

void RenderableObjectManager::render(){
    for (auto it = objMap.begin(); it != objMap.end();){
        //if pointer is null, delete pointer and remove from the list.
        if(it->second == nullptr){
            delete (it->second);
            objMap.erase(it);
        }
        else{
            (it->second)->render();
            ++it;
        }
    }
}

//This function is only called when z_depth has been set. No need to check if it's none
void RenderableObjectManager::changeZ(RenderableObject *object, float z){
    //check if z is valid
    if(object->isZValid()){
        //if so, check if it can get z
        float curZ;
        if(object->getZDepth(curZ)){
            //check if object is on LUT
            std::string name = object->getName();
            auto nameIt = objNameLUT.find(name);
            if(nameIt != objNameLUT.end()){
                //check if
                auto changingIt = objMap.find(curZ);
                if(changingIt != objMap.end()){
//                    changingIt->second->changeZDepth(z);
                    objMap.erase(changingIt);
                    object->changeZDepth(z);
                    objMap.insert(std::pair<float, RenderableObject*>(z, object));
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
