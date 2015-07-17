//
//  SoundManager.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SoundManager__
#define __OpenGL_2D_Framework__SoundManager__

#include <map>
#include "CommonInclude.h"
#ifdef _WIN32
#include <fmod.hpp>
#include <fmod_errors.h>
#elif __APPLE__
#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>
#endif
#include "Sound.h"

class SoundManager{
private:
    
    FMOD::System *fmodSystem;
    void FMODErrorCheck(FMOD_RESULT result);
    int numDrivers;
    Sound* findSound(std::string soundName);
    
    std::map<std::string, Sound*> soundMap;
    void initSoundManager();
    
public:
    SoundManager();
    ~SoundManager();
    
    static SoundManager* createSoundManager(){
        SoundManager* newInstance = new SoundManager;
        newInstance->initSoundManager();
        return newInstance;
    }
    
    void createSFX(std::string sfxName, const char* sfxFileName);
    /**
     *  Create a looping sound.\n
     *  Calls SoundManager::createSound(std::string, FMOD_MODE, const char*).
     *  
     *  @param bgmName A name for bgm sound object.
     *  @param bgmFileName A file name for bgm sound.
     */
    void createBGM(std::string bgmName, const char* bgmFileName);
    
    /**
     *  Create sound
     */
    void createSound(std::string soundName, FMOD_MODE modes, const char* soundFileName);
    void playSound(std::string soundName);
    void pauseSound(std::string soundName);
	void setVolume(std::string soundName, float volume);
	float getVolume(std::string soundName);
    void updateSystem();
    void test();
    
    void release();
};

#endif /* defined(__OpenGL_2D_Framework__SoundManager__) */
