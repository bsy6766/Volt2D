//
//  SoundManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "SoundManager.h"
#include "Director.h"

SoundManager::SoundManager(){
    
}

SoundManager::~SoundManager(){
    
}

void SoundManager::FMODErrorCheck(FMOD_RESULT result){
    if (result != FMOD_OK){
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

void SoundManager::initSoundManager(){
    // Create FMOD interface object
    FMOD_RESULT result = FMOD::System_Create(&fmodSystem);
    FMODErrorCheck(result);
    
    // Check version
    unsigned int version;
    result = fmodSystem->getVersion(&version);
    FMODErrorCheck(result);
    
    if (version < FMOD_VERSION)
    {
        std::cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;
        exit(-1);
    }
    
    int driverCount = 0;
    result = fmodSystem->getNumDrivers(&driverCount);
    FMODErrorCheck(result);
    
    // No sound cards(disable sound)
    if (driverCount == 0)
    {
        result = fmodSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
        FMODErrorCheck(result);
    }
    
    // Initialize our Instance with 36 Channels
    fmodSystem->init(36, FMOD_INIT_NORMAL, NULL);
}

void SoundManager::createSound(std::string soundName, const char *soundFileName){
    auto find_it = soundMap.find(soundName);
    if(find_it == soundMap.end()){
        Sound* newSound = Sound::createSound();
        FMOD::Sound* newFMODSound = newSound->sound;
        std::string bgmDir = Director::getInstance().getWorkingDir() + "/../Sound/" + std::string(soundFileName);
        FMOD_RESULT result = fmodSystem->createSound(bgmDir.c_str(), FMOD_LOOP_NORMAL, 0, &newFMODSound);
        FMODErrorCheck(result);
        FMOD::Channel* newFMODChannel = newSound->channel;
        //this will pause the sound at start.
        result = fmodSystem->playSound(newFMODSound, nullptr, true, &newFMODChannel);
        FMODErrorCheck(result);
        fmodSystem->update();
        newSound->sound = newFMODSound;
        newSound->channel = newFMODChannel;
        soundMap.insert(std::pair<std::string, Sound*>(soundName, newSound));
    }
    else{
        cout << "Sound object with same name already exists." << endl;
        return;
    }
}

void SoundManager::playSound(std::string soundName){
    Sound* sound = findSound(soundName);
    if(sound){
        sound->channel->setPaused(false);
        fmodSystem->update();
    }
}

void SoundManager::pauseSound(std::string soundName){
    Sound* sound = findSound(soundName);
    if(sound){
        sound->channel->setPaused(true);
        fmodSystem->update();
    }
}

Sound* SoundManager::findSound(std::string soundName){
    auto find_sound_it = soundMap.find(soundName);
    if(find_sound_it == soundMap.end()){
        cout << "No sound found to player" << endl;
        return 0;
    }
    else{
        return (find_sound_it)->second;
    }
}

void SoundManager::release(){
    std::map<std::string, Sound*>::iterator s_it;
    for(s_it = soundMap.begin(); s_it != soundMap.end(); s_it++){
        bool playing = false;
        FMODErrorCheck((s_it->second)->channel->isPlaying(&playing));
        if(playing){
            FMODErrorCheck((s_it->second)->channel->stop());
        }
        FMODErrorCheck((s_it->second)->sound->release());
        delete (s_it->second);
    }
}

void SoundManager::setVolume(std::string soundName, float volume){
	Sound* targetSound = findSound(soundName);
	FMODErrorCheck(targetSound->channel->setVolume(volume));
}

float SoundManager::getVolume(std::string soundName){
	Sound* targetSound = findSound(soundName);
	float curVolume;
	FMODErrorCheck(targetSound->channel->getVolume(&curVolume));
	return curVolume;
}