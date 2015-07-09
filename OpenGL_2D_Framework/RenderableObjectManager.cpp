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

bool RenderableObjectManager::addObject(std::string objectName, RenderableObject *object, bool replace){
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
    objMap.insert(std::pair<float, RenderableObject*>(object->z, object));
    
    return true;
}

bool RenderableObjectManager::removeObject(RenderableObject *object){
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
            if(objMapIt->first == object->z && objMapIt->second->getName() == objName){
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
