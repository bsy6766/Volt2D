//
//  Sound.h
//  Volt2D
//
//  Created by Seung Youp Baek on 7/10/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Sound__
#define __Volt2D__Sound__

#ifdef _WIN32
#include <fmod.hpp>
#include <fmod_errors.h>
#elif __APPLE__
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#endif
#include <string>

/**
 *  @class Sound
 *  @brief Simple wrapper for FMOD Sound and Channel
 */
class Sound{
private:
    Sound();
public:
    ~Sound(){};
    
    /**
     *  FMOD Sound object
     */
    FMOD::Sound* sound;
    
    /**
     *  FMOD Channel object
     */
    FMOD::Channel* channel;
    
    /**
     *  Create function for sound. Constructor will be private.
     *  @return New Sound class object
     */
    static Sound* createSound(){
        Sound* newInstance = new Sound();
        return newInstance;
    };
};

#endif /* defined(__Volt2D__Sound__) */
