//
//  main.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 12/15/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include <iostream>
#include <string>
#include "Director.h"
#include "MenuScene.h"

int main(int argc, const char * argv[]) {
    try{
        cout << "[main] Starting application." << endl;
        if(Volt2D::Director::getInstance().initApp(argc, argv)){
            Volt2D::Director::getInstance().replaceScene(new MenuScene());
            Volt2D::Director::getInstance().run();
        }
        else{
            std::runtime_error("Failed to initialize system.");
        }
    }
    catch(std::bad_alloc& ba){
        std::cout << "[SYSTEM::ERROR] Bad allocation" << endl;
        std::cout << ba.what() << std::endl;
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    
    cout << "[main] Application terminated." << endl;
    return 0;
}
