//
//  SoundManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/19/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SoundManager__
#define __OpenGL_2D_Framework__SoundManager__

#include <map>
#include "CommonInclude.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"

class SoundManager{
private:
    SoundManager();
    ~SoundManager();
    SoundManager(SoundManager const& other);
    void operator=(SoundManager const&);
    
    FMOD::System *fmodSystem;
    void FMODErrorCheck(FMOD_RESULT result);
    
    FMOD_SPEAKERMODE speakerMode;
    int numDrivers;
    FMOD::Sound* bgm;
    FMOD::Channel* musicChannel;
    
public:
    static SoundManager& getInstance(){
        static SoundManager instance;
        return instance;
    }
    
    void initSoundManager();
    void terminateSoundManager();
    void createBGM(const char* file);
    void playBGM();
};

#endif /* defined(__OpenGL_2D_Framework__SoundManager__) */
