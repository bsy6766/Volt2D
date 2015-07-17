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

/**
 *  \class SoundManager
 *
 *  \brief Manages sounds (BGM, SFX).
 *
 *  \note This class uses FMOD.
 *  \note Volume is 1.0 for all sound by default. Volume can go below 0 to invert signal or go above to amplify.
 *
 *  This class provides options to create, play, stop, pause for either BGM or SFX.
 *
 */

class SoundManager{
private:
    /**
     * FMOD system. Update is called on every iteration.
     */
    FMOD::System *fmodSystem;
    
    /**
     *  FMOD error checking. 
     *
     *  @param result A result from FMOD functions.
     *  @return true if result is FMOD_OK. Else, false.
     */
    bool FMODErrorCheck(FMOD_RESULT result);

    /**
     *  Find sound by sound object name and returns the Sound object.
     *  @param soundName A given name (by you) for each sound object.
     *  @return A Sound class object. 0 if no sound found.
     */
    Sound* findSound(std::string soundName);
    
    /**
     * A std::map that stores Sound object with name as an ID.
     */
    std::map<std::string, Sound*> soundMap;
    
    /**
     *  A std::map that stores channel group with name as an ID
     */
    std::map<std::string, FMOD::ChannelGroup*> channelGroupMap;
    
    /**
     *  Initailize sound manager and FMOD system.
     */
    void initSoundManager();
    
    /**
     * Private constructor.
     * Call SoundManager::createSoundManager() to create instance.
     */
    SoundManager();
    
public:
    ~SoundManager();
    
    /**
     *  Create a SoundManager instance, initailize and return.
     *
     *  @return A new SoundManager instance
     */
    static SoundManager* createSoundManager(){
        SoundManager* newInstance = new SoundManager;
        newInstance->initSoundManager();
        return newInstance;
    }
    
    /**
     *  Create a non-looping sound.\n
     *  Calls SoundManager::createSound(std::string, FMOD_MODE, const char*).
     *
     *  @param sfxName A name for sfx sound object.
     *  @param sfxFileName A file name for sfx sound.
     */
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
     *  Create sounds and store.
     *  
     *  @param soundName A name for sound object.
     *  @param modes FMOD modes. 
     *  @param soundFileName A name for sound object file.
     *  @param pause true to play sound and pause on creation. false to just create sound only
     */
    void createSound(std::string soundName, FMOD_MODE modes, const char* soundFileName, bool pause);
    
    /**
     *  Creates a channel group with name.
     *  You can bind existing channel by calling SoundManager::bindSoundToChannelGroup(std::string soundName, std::channelGroupName)
     */
    void createChannelGroup(std::string channelGroupName);
    
    /**
     *  Bind existing sound's channel to channelGroup.
     *  If channelGroup doesn't exist, then it will create new one with name as an ID.
     *  You can create new FMOD channel group with SoundManager::createChannelGroup(std::string)
     */
    void bindSoundToChannelGroup(std::string soundName, std::string channelGroupName);
    
    /**
     *  Stops sound.
     */
    void stopSound(std::string soundName);
    
    /**
     *  Play SFX.
     *  Plays SFX only if SFX is not playing.
     */
    void playSFX(std::string sfxName);
    
    /**
     *  Play BGM.
     *  If sound is not playing, it will play newly. If sound is playing but paused, it will unpause.
     */
    void playBGM(std::string bgmName);
    
    /**
     *
     */
    void pauseBGM(std::string bgmName);
    
    /**
     *  Get volume of sound
     *  @return Volume of sound. Default is 1.0.
     */
    bool getSoundVolume(std::string soundName, float& volume);
    
    /**
     *  Set volume of sound
     *  
     *  @param Name for sound object to set volume
     *  @param volume A new volume value to set. Default is 1.0
     */
    bool setSoundVolume(std::string soundName, float volume);
    
    /**
     *
     */
    bool getChannelGroupVolume(std::string channelGroupName, float volume);
    
    /**
     *  Update FMOD System.
     *  This is called on every iteration.
     */
    void updateSystem();
    
    /**
     *  Release SoundManager
     *  It stops and release all sounds that were added and release FMOD::System at the end.
     */
    void release();
};

#endif /* defined(__OpenGL_2D_Framework__SoundManager__) */
