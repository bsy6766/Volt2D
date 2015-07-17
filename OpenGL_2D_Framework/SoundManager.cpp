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

bool SoundManager::FMODErrorCheck(FMOD_RESULT result){
    if (result != FMOD_OK){
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        return false;
    }
    else{
        return true;
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

void SoundManager::createSFX(std::string sfxName, const char *sfxFileName){
    createSound(sfxName, FMOD_DEFAULT, sfxFileName, false);
}

void SoundManager::createBGM(std::string bgmName, const char *bgmFileName){
    createSound(bgmName, FMOD_LOOP_NORMAL | FMOD_2D, bgmFileName, true);
}

void SoundManager::createSound(std::string soundName, FMOD_MODE modes, const char *soundFileName, bool pause){
    if(!findSound(soundName)) {
        //create sound if there isn't a object with same name
        Sound* newSound = Sound::createSound(); //new Sound
        
        //full file path
        std::string filePath = Director::getInstance().getWorkingDir() + "/../Sound/" + std::string(soundFileName);
        
        //create new fmod sound
        FMOD_RESULT result = fmodSystem->createSound(filePath.c_str(), modes, 0, &newSound->sound);
        if(FMODErrorCheck(result)){
            if(pause){
                //bgm
                //this will pause the sound at start.
                result = fmodSystem->playSound(newSound->sound, nullptr, true, &newSound->channel);
                if(FMODErrorCheck(result)){
                    //store sound on map
                    soundMap.insert(std::pair<std::string, Sound*>(soundName, newSound));
                }
                else{
                    cout << "failed to play and pause bgm on creation" << endl;
                }
            }
            else{
                //sfx
                //store sound on map
                cout << "Creating sfx " << endl;
                soundMap.insert(std::pair<std::string, Sound*>(soundName, newSound));
            }
        }
        else{
            cout << "Failed to create sound" << endl;
        }
    }
}

void SoundManager::stopSound(std::string soundName){
    Sound* sound = findSound(soundName);
    if(sound){
        bool playing = false;
        if(FMODErrorCheck(sound->channel->isPlaying(&playing))){
            //succesfully got if channel is playing
            if(playing){
                if(FMODErrorCheck(sound->channel->stop())){
                    cout << "succesfully stopped channel" << endl;
                }
                else{
                    cout << "failed to stop channel" << endl;
                }
            }
            else{
                cout << "sound not playing. wtf?" << endl;
            }
        }
        else{
            //channel isn't valid = no sound playing in this channel.
            cout << "channel invalid. nothing to stop" << endl;
        }
    }
}

void SoundManager::playSFX(std::string sfxName){
    //get sound
    Sound* sound = findSound(sfxName);
    if(sound){
        //check if playing
        bool playing = false;
        if(FMODErrorCheck(sound->channel->isPlaying(&playing))){
            cout << "sfx already playing" << endl;
            //then stop and play new
            if(FMODErrorCheck(sound->channel->stop())){
                cout << "Stopping and playing new" << endl;
                FMODErrorCheck(fmodSystem->playSound(sound->sound, nullptr, false, &sound->channel));
            }
            else{
                cout << "Failed to stop to play new" << endl;
            }
        }
        else{
            //failed to get info. channel is invalid(free).
            cout << "SFX not playing. so play!" << endl;
            FMODErrorCheck(fmodSystem->playSound(sound->sound, nullptr, false, &sound->channel));
        }
    }
}

void SoundManager::playBGM(std::string bgmName){
    //get sound
    Sound* sound = findSound(bgmName);
    if(sound){
        //check if playing
        bool playing = false;
        FMODErrorCheck(sound->channel->isPlaying(&playing));
        if(playing){
            //check if it's paused
            cout << "PlayBGM(). bgm is playing" << endl;
            bool paused = false;
            FMODErrorCheck(sound->channel->getPaused(&paused));
            if(paused){
                //playing but paused. set paused to false.
                cout << "it's paused" << endl;
                FMODErrorCheck(sound->channel->setPaused(false));
            }
            else{
                cout << "it's already playing wtf?" << endl;
            }
        }
        else{
            //not playing. play it new.
            cout << "PlayBGM(). bgm isn't playing. so play!" << endl;
            FMODErrorCheck(fmodSystem->playSound(sound->sound, nullptr, true, &sound->channel));
        }
    }
}

void SoundManager::pauseBGM(std::string bgmName){
    //get sound
    Sound* sound = findSound(bgmName);
    if(sound){
        //check if playing
        bool playing = false;
        FMODErrorCheck(sound->channel->isPlaying(&playing));
        if(playing){
            FMODErrorCheck(sound->channel->setPaused(false));
        }
        else{
            cout << "can't pause sound that isn't playing" << endl;
        }
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

bool SoundManager::setSoundVolume(std::string soundName, float volume){
	Sound* sound = findSound(soundName);
    if(sound){
        FMODErrorCheck(sound->channel->setVolume(volume));
        return true;
    }
    else{
        return false;
    }
}

bool SoundManager::getSoundVolume(std::string soundName, float &volume){
	Sound* sound = findSound(soundName);
    if(sound){
        float curVolume;
        FMODErrorCheck(sound->channel->getVolume(&curVolume));
        volume = curVolume;
        return true;
    }
    else{
        return false;
    }
}

void SoundManager::updateSystem(){
    fmodSystem->update();
}