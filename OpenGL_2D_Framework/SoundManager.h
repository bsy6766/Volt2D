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
#include "Director.h"
#include "CommonInclude.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include "Sound.h"

class ChannelGroup{
public:
    FMOD::ChannelGroup* channelGroup;
    std::string groupName;
};

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
    FMOD::Channel* musicChannel;
    
//    std::map<std::string, FMOD::ChannelGroup*> groupMap;
    std::map<std::string, ChannelGroup*> groupMap;
//    std::map<std::string, FMOD::Sound*> bgmMap;
    std::map<std::string, Sound* > soundMap;
    
    Sound* findSound(std::string soundName);
    
public:
    static SoundManager& getInstance(){
        static SoundManager instance;
        return instance;
    }
    
    void initSoundManager();
    void terminateSoundManager();
    
    void createChannelGroup(std::string groupName);
    void addSoundToChannelGroup(std::string groupName, std::string soundName);
    void createNewSound(std::string soundObjectName, std::string soundName, const char* bgmFilePath);
    void setChannelGroupVolume(std::string groupName, float volume);
    void playSound(std::string soundObjectName);
    void pauseSound(std::string soundObjectName);
    void stopSound(std::string soundObjectName);
};

#endif /* defined(__OpenGL_2D_Framework__SoundManager__) */
