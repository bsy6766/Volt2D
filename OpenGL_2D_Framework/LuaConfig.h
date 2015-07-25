//
//  LuaConfig.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/24/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__LuaConfig__
#define __OpenGL_2D_Framework__LuaConfig__

#include <map>
#include <string>
#include <iostream>
#include <list>
#include <vector>

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class DataObject{
public:
    enum DO_TYPE{
        DO_NONE=0,
        DO_FLOAT,
        DO_BOOL,
        DO_STRING,
        DO_PARENT
    };
    
    DO_TYPE type = DO_PARENT;
};

class FloatObject : public DataObject{
public:
    float value;
    FloatObject(float value){
        this->value = value;
        this->type = DataObject::DO_TYPE::DO_FLOAT;
    };
};

class BoolObject : public DataObject{
public:
    bool value;
    BoolObject(bool value){
        this->value = value;
        this->type = DataObject::DO_TYPE::DO_BOOL;
    };
};

class StringObject : public DataObject{
public:
    std::string value;
    StringObject(std::string value){
        this->value = value;
        this->type = DataObject::DO_TYPE::DO_STRING;
    };
};

class ParentObject : public DataObject{
public:
    std::string key;
    ParentObject(std::string key){
        this->key = key;
        this->type = DataObject::DO_TYPE::DO_PARENT;
    };
};

class Node{
public:
    DataObject* data;
    std::map<std::string, Node*> childNodes;
    Node();
    Node(DataObject* data){
        this->data = data;
    };
    ~Node(){
        if(data)
            delete this->data;
        
        for(auto it : this->childNodes){
            delete (it.second);
        }
    }
};

/**
 *
 */
class LuaConfig{
private:
    //can hold multiple option heirarchy
    std::map<std::string, Node*> configMap;
    std::string name;
    LuaConfig();
    bool readLuaTable(lua_State* L, std::string key, std::list<std::string>& keyChain);
    void addNode(std::list<std::string>& keyChain, Node* newNode);
public:
    static LuaConfig* create(std::string configName);
    void loadConfig(std::string key, std::string fileName);
    
    ~LuaConfig();
    
    bool getBoolean(std::string configName, std::string path);
    int getInt(std::string configName, std::string path);
    double getDouble(std::string configName, std::string path);
    float getFloat(std::string configName, std::string path);
    std::string getString(std::string configName, std::string path);
};

#endif /* defined(__OpenGL_2D_Framework__LuaConfig__) */
