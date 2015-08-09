//
//  LuaConfig.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 7/24/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "LuaConfig.h"

using namespace Volt2D;

void stackDump (lua_State *L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
                
            case LUA_TSTRING:  /* strings */
                printf("`%s'", lua_tostring(L, i));
                break;
                
            case LUA_TBOOLEAN:  /* booleans */
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;
                
            case LUA_TNUMBER:  /* numbers */
                printf("%g", lua_tonumber(L, i));
                break;
                
            default:  /* other values */
                printf("%s", lua_typename(L, t));
                break;
                
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

LuaConfig::LuaConfig(){
    
}

LuaConfig::~LuaConfig(){
    for(auto key : configMap){
        delete (key.second);
    }
}

LuaConfig* LuaConfig::create(std::string configName){
    LuaConfig* newConfig = new LuaConfig();
    newConfig->name = configName;
    return newConfig;
}

bool LuaConfig::loadConfig(std::string key, std::string fileName){
    //create new lua state
    lua_State* L = luaL_newstate();
    //open lua libraries
    luaL_openlibs(L);
    //do file
    int error = luaL_dofile(L, fileName.c_str());
    if(error){
        cout << "[SYSTEM::ERROR] Failed to load \"" << fileName << "\"." << endl;
        return false;
    }
    //iterate through script
    lua_getglobal(L, key.c_str());
    if(lua_istable(L, 1)){
        std::list<std::string> keyChain;
        this->readLuaTable(L, key, keyChain);
    }
    else{
        switch (lua_type(L, 1)) {
            case LUA_TSTRING:
                this->configMap[key] = new Node(new StringObject(lua_tostring(L, 1)));
                break;
            case LUA_TBOOLEAN:
                this->configMap[key] = new Node(new BoolObject(lua_toboolean(L, 1)));
                break;
            case LUA_TNUMBER:
                this->configMap[key] = new Node(new FloatObject(lua_tonumber(L, 1)));
                break;
            default:
                break;
        }
    }
    lua_close(L);
    return true;
}

bool LuaConfig::readLuaTable(lua_State* L, std::string key, std::list<std::string>& keyChain){
    //limit the scope
    {
        //At the start of function, add parent node.
        Node* newParentNode = new Node(new ParentObject(key));
        
        //if root = no keyChain, then add root.
        if(keyChain.empty()){
            this->configMap[key] = newParentNode;
        }
        else{
            this->addNode(keyChain, newParentNode);
        }
    }
    
    //build key chain
    keyChain.push_back(key);
    
    /*
        Lua Stack
        -1 : table
        (possible parent table)
     */

    //push nil key to Lua stack
    lua_pushnil(L);
    
    /*
     Lua Stack
     -1 : nil
     -2 : table
     (possible parent table)
     */
    
    //iterate table.
    while (lua_next(L, -2))
    {
        // stack now contains: -1 => value; -2 => key; -3 => table
        // copy the key so that lua_tostring does not modify the original
        lua_pushvalue(L, -2);

        // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
        const char *key = lua_tostring(L, lua_gettop(L));
        //build child key chain
        keyChain.push_back(key);
        //pop key
        lua_pop(L, 1);
        
        //by type
        switch (lua_type(L, lua_gettop(L))) {
            //String
            case LUA_TSTRING:
            {
                std::string value = lua_tostring(L, lua_gettop(L));
                //get value and pop from stack
                lua_pop(L, 1);
                
                //build new string node
                Node* strChildNode = new Node(new StringObject(value));
                this->addNode(keyChain, strChildNode);
                //child node added. pop this key from key chain
                keyChain.pop_back();

                break;
            }
            //Bool
            case LUA_TBOOLEAN:
            {
                bool value = lua_toboolean(L, lua_gettop(L));
                //get value and pop from stack
                lua_pop(L, 1);
                
                //build new bool node
                Node* boolChildNode = new Node(new BoolObject(value));
                this->addNode(keyChain, boolChildNode);
                //child node added. pop this key from key chain
                keyChain.pop_back();
                break;
            }
            //Number
            case LUA_TNUMBER:
            {
                float value = lua_tonumber(L, lua_gettop(L));
                lua_pop(L, 1);
                Node* floatChildNode = new Node(new FloatObject(value));
                this->addNode(keyChain, floatChildNode);
                keyChain.pop_back();
                break;
            }
            case LUA_TTABLE:
            {
                Node* parentNode = new Node(new ParentObject(key));
                this->addNode(keyChain, parentNode);
                keyChain.pop_back();

                this->readLuaTable(L, key, keyChain);
                keyChain.pop_back();
                break;
            }
            default:
                break;
        }
    }
    //pop table
    lua_pop(L, 1);
    
    return true;
}

void LuaConfig::addNode(std::list<std::string>& keyChain, Node* newNode){
    if(keyChain.size() == 1){
        //root node
        if(this->configMap.empty()){
            //add root node
            (*newNode).data->type = DataObject::DO_TYPE::DO_PARENT;
            configMap[keyChain.front()] = newNode;
        }
        else{
            return;
        }
    }
    else{
        //adding childs
        auto key = keyChain.begin();
        //get root node
        auto check_it = this->configMap.find(*key);
        if(check_it == this->configMap.end()){
            return;
        }
        Node* head = this->configMap[*key];
        key++;
        while (key != keyChain.end()) {
            //if head has key, proceed
            auto find_it = head->childNodes.find(*key);
            if(find_it == head->childNodes.end()){
                //not found add.
                head->childNodes[*key] = newNode;
            }
            else{
                //found. jump to next node
                head = (head->childNodes[*key]);
                key++;
            }
        }
    }
}

float LuaConfig::getFloat(std::string configName, std::string path){
    std::string curPath;
    std::string delimeter = ".";
    
    if(!path.empty()){
        curPath = configName + "." + path;
    }
    else{
        curPath = configName;
    }
    size_t delimIndex = curPath.find(".");
    
    if(delimIndex == std::string::npos){
        //first path
        auto find_it = this->configMap[curPath];
        if(find_it->data->type == DataObject::DO_TYPE::DO_FLOAT){
            FloatObject* fo = static_cast<FloatObject*>(find_it->data);
            return fo->value;
        }
        else{
            return 0;
        }
    }
    else{
        //check root
        std::string key = curPath.substr(0, delimIndex);
        curPath = curPath.substr(delimIndex+1);
        delimIndex = curPath.find(".");

        
        auto root_check = this->configMap.find(key);
        if(root_check == this->configMap.end()){
            return 0;
        }
        else{
            Node* head = root_check->second;
            
            while(delimIndex != std::string::npos){
                key = curPath.substr(0, delimIndex);
                curPath = curPath.substr(delimIndex+1);
                auto check_it = head->childNodes.find(key);
                if(check_it == head->childNodes.end()){
                    return 0;
                }
                else{
                    head = head->childNodes[key];
                }
                delimIndex = curPath.find(".");
            }
            
            auto find_it = head->childNodes.find(curPath);
            if(find_it != head->childNodes.end()){
                FloatObject* fo = static_cast<FloatObject*>(find_it->second->data);
                return fo->value;
            }
            else{
                return 0;
            }
        }
    }
}

std::string LuaConfig::getString(std::string configName, std::string path){
    std::string curPath;
    std::string delimeter = ".";
    
    if(!path.empty()){
        curPath = configName + "." + path;
    }
    else{
        curPath = configName;
    }
    size_t delimIndex = curPath.find(".");
    
    if(delimIndex == std::string::npos){
        //first path
        auto find_it = this->configMap[curPath];
        if(find_it->data->type == DataObject::DO_TYPE::DO_STRING){
            StringObject* so = static_cast<StringObject*>(find_it->data);
            return so->value;
        }
        else{
            return "";
        }
    }
    else{
        //check root
        std::string key = curPath.substr(0, delimIndex);
        curPath = curPath.substr(delimIndex+1);
        delimIndex = curPath.find(".");
        
        
        auto root_check = this->configMap.find(key);
        if(root_check == this->configMap.end()){
            return "";
        }
        else{
            Node* head = root_check->second;
            
            while(delimIndex != std::string::npos){
                key = curPath.substr(0, delimIndex);
                curPath = curPath.substr(delimIndex+1);
                auto check_it = head->childNodes.find(key);
                if(check_it == head->childNodes.end()){
                    return "";
                }
                else{
                    head = head->childNodes[key];
                }
                delimIndex = curPath.find(".");
            }
            
            auto find_it = head->childNodes.find(curPath);
            if(find_it != head->childNodes.end()){
                StringObject* so = static_cast<StringObject*>(find_it->second->data);
                return so->value;
            }
            else{
                return "";
            }
        }
    }
}

bool LuaConfig::getBoolean(std::string configName, std::string path){
    std::string curPath;
    std::string delimeter = ".";
    
    if(!path.empty()){
        curPath = configName + "." + path;
    }
    else{
        curPath = configName;
    }
    size_t delimIndex = curPath.find(".");
    
    if(delimIndex == std::string::npos){
        //first path
        auto find_it = this->configMap[curPath];
        if(find_it->data->type == DataObject::DO_TYPE::DO_FLOAT){
            BoolObject* bo = static_cast<BoolObject*>(find_it->data);
            return bo->value;
        }
        else{
            return false;
        }
    }
    else{
        //check root
        std::string key = curPath.substr(0, delimIndex);
        curPath = curPath.substr(delimIndex+1);
        delimIndex = curPath.find(".");
        
        
        auto root_check = this->configMap.find(key);
        if(root_check == this->configMap.end()){
            return false;
        }
        else{
            Node* head = root_check->second;
            
            while(delimIndex != std::string::npos){
                key = curPath.substr(0, delimIndex);
                curPath = curPath.substr(delimIndex+1);
                auto check_it = head->childNodes.find(key);
                if(check_it == head->childNodes.end()){
                    return false;
                }
                else{
                    head = head->childNodes[key];
                }
                delimIndex = curPath.find(".");
            }
            
            auto find_it = head->childNodes.find(curPath);
            if(find_it != head->childNodes.end()){
                BoolObject* bo = static_cast<BoolObject*>(find_it->second->data);
                return bo->value;
            }
            else{
                return false;
            }
        }
    }
}