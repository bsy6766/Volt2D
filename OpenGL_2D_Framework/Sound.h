//
//  Sound.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/10/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Sound__
#define __OpenGL_2D_Framework__Sound__

#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include <string>

class Sound{
private:
    
    Sound();
    ~Sound();
public:
    FMOD::Sound* sound;
    FMOD::Channel* channel;
    
    static Sound* createSound(){
        Sound* newInstance = new Sound();
        return newInstance;
    };
    
//    FMOD::Sound* getSound(){
//        return this->sound;
//    }
//    
//    FMOD::Channel* getChannel(){
//        return this->channel;
//    }
};

#endif /* defined(__OpenGL_2D_Framework__Sound__) */
