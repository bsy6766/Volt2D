//
//  SoundManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/11/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "SoundManager.h"
#include "Director.h"

using namespace Volt2D;

SoundManager::SoundManager(){
    
}

SoundManager::~SoundManager(){
    
}

bool SoundManager::FMODErrorCheck(FMOD_RESULT result){
    if(result == FMOD_OK){
        return true;
    }
    else{
        cout << "[SYSTEM::ERROR] FMOD_RESULT = " << FMOD_ErrorString(result) << endl;
        return false;
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
        std::cout << "[SYSTEM::ERROR] You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;
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

void SoundManager::createBGM(std::string bgmName, const char *bgmFileName, float volume){
    createSound(bgmName, FMOD_LOOP_NORMAL | FMOD_2D, bgmFileName, true);
}

void SoundManager::createSound(std::string soundName, FMOD_MODE modes, const char *soundFileName, bool pause, float volume){
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
                    //set volume
                    if(FMODErrorCheck(newSound->channel->setVolume(volume))){
                        //store sound on map
                        soundMap.insert(std::pair<std::string, Sound*>(soundName, newSound));
                    }
                    else{
                        cout << "[SYSTEM::ERROR] Failed to set volume on creation" << endl;
                    }
                }
                else{
                    cout << "[SYSTEM::ERROR] Failed to play and pause bgm on creation" << endl;
                }
            }
            else{
                //sfx
                //store sound on map
//                cout << "Creating sfx " << endl;
                soundMap.insert(std::pair<std::string, Sound*>(soundName, newSound));
            }
        }
        else{
            cout << "[SYSTEM::ERROR] Failed to create sound" << endl;
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
                if(!FMODErrorCheck(sound->channel->stop())){
                    cout << "[SYSTEM::ERROR] Failed to stop \"" << soundName << "\"'s channel." << endl;
                }
            }
            else{
                cout << "[SYSTEM::ERROR] \"" << soundName << "\" is not playing." << endl;
            }
        }
        else{
            //channel isn't valid = no sound playing in this channel.
            cout << "[SYSTEM::ERROR] channel invalid." << endl;
        }
    }
}

void SoundManager::playSFX(std::string sfxName, float volume){
    //get sound
    Sound* sound = findSound(sfxName);
    if(sound){
        //check if playing
        bool playing = false;
        if(FMODErrorCheck(sound->channel->isPlaying(&playing))){
//            cout << "sfx already playing" << endl;
            //then stop and play new
            if(FMODErrorCheck(sound->channel->stop())){
//                cout << "Stopping and playing new" << endl;
                if(FMODErrorCheck(fmodSystem->playSound(sound->sound, nullptr, false, &sound->channel))){
                    if(!FMODErrorCheck(sound->channel->setVolume(volume))){
                        cout << "Failed to set volume" << endl;
                    }
                }
                else{
                    cout << "Failed to play" << endl;
                }
                
            }
            else{
                cout << "Failed to stop to play new" << endl;
            }
        }
        else{
            //failed to get info. channel is invalid(free).
//            cout << "SFX not playing. so play!" << endl;
            if(FMODErrorCheck(fmodSystem->playSound(sound->sound, nullptr, false, &sound->channel))){
                if(!FMODErrorCheck(sound->channel->setVolume(volume))){
                    cout << "Failed to set volume" << endl;
                }
            }
            else{
                cout << "Failed to play" << endl;
            }
        }
    }
}

void SoundManager::playBGM(std::string bgmName){
    //get sound
    Sound* sound = findSound(bgmName);
    if(sound){
        //check if playing
        bool playing = false;
        if(FMODErrorCheck(sound->channel->isPlaying(&playing))){
            if(playing){
                //channel is already playing.
                bool paused = false;
                if(FMODErrorCheck(sound->channel->getPaused(&paused))){
                    if(paused){
                        //channel is playing and paused. unpause then.
                        if(!FMODErrorCheck(sound->channel->setPaused(false))){
                            cout << "bgm is playing and paused but failed to unpause" << endl;
                        }
                    }
                    else{
                        //channel is playing and not paused. so do nothing
                        cout << "bgm is playing but unpaused(already playing?)" << endl;
                    }
                }
                else{
                    //sould not reach here.
                    cout << "bgm is playing but failed to get pause info" << endl;
                }
            }
            else{
                //channel is not playing. never reach here?
                cout << "bgm is not playing." << endl;
            }
        }
        else{
            //channel is free.
            cout << "channel is free. play fresh?" << endl;
            if(FMODErrorCheck(fmodSystem->playSound(sound->sound, nullptr, false, &sound->channel))){
                cout << "playing fresh!" << endl;
            }
            else{
                cout << "failed to play fresh" << endl;
            }
        }
    }
    else{
        cout << "bgm doesn't exist" << endl;
    }
}

void SoundManager::pauseBGM(std::string bgmName){
    //get sound
    Sound* sound = findSound(bgmName);
    if(sound){
        //check if playing
        bool playing = false;
        if(FMODErrorCheck(sound->channel->isPlaying(&playing))){
            bool paused = false;
            if(FMODErrorCheck(sound->channel->getPaused(&paused))){
                if(paused){
                    cout << "already paused" << endl;
                }
                else{
                    if(!FMODErrorCheck(sound->channel->setPaused(true))){
                        cout << "failed to pause bgm" << endl;
                    }
                }
            }
            else{
                cout << "Channel is free" << endl;
            }
        }
        else{
            cout << "Channel is free" << endl;
        }
    }
    else{
        cout << "No sound found" << endl;
    }
}

void SoundManager::resumeBGM(std::string bgmName){
    //get sound
    Sound* sound = findSound(bgmName);
    if(sound){
        //check if playing
        bool playing = false;
        if(FMODErrorCheck(sound->channel->isPlaying(&playing))){
            bool paused = false;
            if(FMODErrorCheck(sound->channel->getPaused(&paused))){
                if(paused){
                    if(!FMODErrorCheck(sound->channel->setPaused(false))){
                        cout << "failed to resume bgm" << endl;
                    }
                }
                else{
                    cout << "already playing" << endl;
                }
            }
            else{
                cout << "Channel is free" << endl;
            }
        }
        else{
            cout << "Channel is free" << endl;
        }
    }
    else{
        cout << "No sound found" << endl;
    }
}

void SoundManager::createChannelGroup(std::string channelGroupName){
    auto find_it = this->channelGroupMap.find(channelGroupName);
    if(find_it == this->channelGroupMap.end()){
        FMOD::ChannelGroup* newChGroup;
        if(FMODErrorCheck(fmodSystem->createChannelGroup(channelGroupName.c_str(), &newChGroup))){
            //store in ch group map
            channelGroupMap[channelGroupName] = newChGroup;
            cout << "successfully create channel group" << endl;
        }
        else{
            cout << "Failed to create channel group" << endl;
        }
    }
    else{
        cout << "Channel Group with same name already exists" << endl;
    }
}

void SoundManager::bindSoundToChannelGroup(std::string soundName, std::string channelGroupName){
    //get sound
    Sound* sound = findSound(soundName);
    if(sound){
        //check ch group
        auto find_it = this->channelGroupMap.find(channelGroupName);
        if(find_it != this->channelGroupMap.end()){
            if(FMODErrorCheck(sound->channel->setChannelGroup(find_it->second))){
                cout << "Successfully added sound's channel to channel group" << endl;
            }
            else{
                cout << "Failed to add sound's channel to channel group" << endl;
            }
        }
        else{
            cout << "No channel group found" << endl;
        }
    }
    else{
        cout << "No sound found" << endl;
    }
}

SoundManager::Sound* SoundManager::findSound(std::string soundName){
    auto find_sound_it = soundMap.find(soundName);
    if(find_sound_it == soundMap.end()){
//        cout << "No sound found to player" << endl;
        return 0;
    }
    else{
        return (find_sound_it)->second;
    }
}

void SoundManager::release(){
    updateSystem();
    //release sound
    std::map<std::string, Sound*>::iterator s_it;
    for(s_it = soundMap.begin(); s_it != soundMap.end(); s_it++){
        bool playing = false;
        if(FMODErrorCheck((s_it->second)->channel->isPlaying(&playing))){
            if(playing){
                if(FMODErrorCheck((s_it->second)->channel->stop())){
                    if(FMODErrorCheck((s_it->second)->sound->release())){
//                        cout << "[SYSTEM::INFO] Successfully released " << s_it->first << endl;
                    }
                    else{
                        cout << "[SYSTEM::ERROR] Failed to release sound" << endl;
                    }
                }
            }
            else{
                if(FMODErrorCheck((s_it->second)->sound->release())){
//                    cout << "[SYSTEM::INFO] Successfully released " << s_it->first << endl;
                }
                else{
                    cout << "[SYSTEM::ERROR] Failed to release sound" << endl;
                }
            }
        }
        else{
            if(FMODErrorCheck((s_it->second)->sound->release())){
//                cout << "[SYSTEM::INFO] Successfully released " << s_it->first << endl;
            }
            else{
                cout << "[SYSTEM::ERROR] Failed to release sound" << endl;
            }
        }
        delete (s_it->second);
    }
    
    updateSystem();
    //release channel group
    std::map<std::string, FMOD::ChannelGroup*>::iterator ch_g_it;
    for(ch_g_it = channelGroupMap.begin(); ch_g_it != channelGroupMap.end(); ch_g_it++){
        
    }
    
    updateSystem();
    //release system
    if(FMODErrorCheck(fmodSystem->release())){
//        cout << "[SYSTEM::INFO] Successfully released fmod system" << endl;
    }
    else{
        cout << "[SYSTEM::ERROR] Failed to release fmod system" << endl;
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

bool SoundManager::setChannelGroupVolume(std::string channelGroupName, float volume){
    auto find_it = this->channelGroupMap.find(channelGroupName);
    if(find_it != this->channelGroupMap.end()){
        if(FMODErrorCheck((find_it->second)->setVolume(volume))){
            cout << "Successfully set new volume" << endl;
            return true;
        }
        else{
            cout << "Failed to set volume" << endl;
        }
    }
    else{
        cout << "Failed to find channel group" << endl;
    }
    return false;
}

bool SoundManager::getChannelGroupVolume(std::string channelGroupName, float& volume){
    auto find_it = this->channelGroupMap.find(channelGroupName);
    if(find_it != this->channelGroupMap.end()){
        if(FMODErrorCheck((find_it->second)->getVolume(&volume))){
            cout << "Successfully got new volume" << endl;
            return true;
        }
        else{
            cout << "Failed to set volume" << endl;
        }
    }
    else{
        cout << "Failed to find channel group" << endl;
    }
    return false;
}


void SoundManager::updateSystem(){
    fmodSystem->update();
}


