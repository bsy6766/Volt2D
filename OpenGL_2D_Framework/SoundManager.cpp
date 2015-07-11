//
//  SoundManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/19/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "SoundManager.h"

SoundManager::SoundManager()
{
    
}

SoundManager::~SoundManager(){

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

void SoundManager::terminateSoundManager(){
    FMOD_RESULT result;
    
//    for(auto& it : groupMap){
//        bool playing = false;
//        FMODErrorCheck((it.second)->channelGroup->isPlaying(&playing));
////        FMODErrorCheck((it.second)->isPlaying(&playing));
//        if(playing){
//            FMODErrorCheck((it.second)->channelGroup->stop());
////            FMODErrorCheck((it.second)->stop());
//        }
////        FMODErrorCheck((it.second)->release());
//        FMODErrorCheck((it.second)->channelGroup->release());
//    }
    
    for(auto it : soundMap){
        bool playing = false;
        FMODErrorCheck((it.second)->channel->isPlaying(&playing));
        if(playing){
            FMODErrorCheck((it.second)->channel->stop());
        }
        result = (it.second)->sound->release();
        FMODErrorCheck(result);
    }
    
//    std::map<std::string, ChannelGroup*>::iterator cg_it;
//    for( cg_it = groupMap.begin(); cg_it != groupMap.end(); cg_it++) {
//        bool playing = false;
//        FMODErrorCheck((cg_it->second)->channelGroup->isPlaying(&playing));
//        //        FMODErrorCheck((it.second)->isPlaying(&playing));
//        if(playing){
//            FMODErrorCheck((cg_it->second)->channelGroup->stop());
//            //            FMODErrorCheck((it.second)->stop());
//        }
//        //        FMODErrorCheck((it.second)->release());
//        FMODErrorCheck((cg_it->second)->channelGroup->release());
//    }
    
    //this will stop all sound
    result = fmodSystem->release();
    FMODErrorCheck(result);
}

void SoundManager::createNewSound(std::string soundObjectName, std::string soundName, const char *bgmFilePath){
    auto find_it = soundMap.find(soundObjectName);
    if(find_it == soundMap.end()){
        Sound* newSound = Sound::createSound();
        FMOD::Sound* newFMODSound = newSound->sound;
        std::string bgmDir = Director::getInstance().getWorkingDir() + "/../Sound/" + std::string(bgmFilePath);
        FMOD_RESULT result = fmodSystem->createSound(bgmDir.c_str(), FMOD_LOOP_NORMAL, 0, &newFMODSound);
        FMODErrorCheck(result);
        FMOD::Channel* newFMODChannel = newSound->channel;
        //this will pause the sound at start.
        result = fmodSystem->playSound(newFMODSound, nullptr, true, &newFMODChannel);
        FMODErrorCheck(result);
        fmodSystem->update();
        newSound->sound = newFMODSound;
        newSound->channel = newFMODChannel;
        soundMap.insert(std::pair<std::string, Sound*>(soundObjectName, newSound));
    }
    else{
        cout << "Sound object with same name already exists." << endl;
        return;
    }
}

void SoundManager::createChannelGroup(std::string groupName){
    auto find_it = groupMap.find(groupName);
    if(find_it == groupMap.end()){
        ChannelGroup* cg = new ChannelGroup();
        cg->groupName = groupName;
        FMODErrorCheck(fmodSystem->createChannelGroup(groupName.c_str(), &cg->channelGroup));
//        groupMap.insert(std::pair<std::string, FMOD::ChannelGroup*>(groupName, newChannelGroup));
        fmodSystem->update();
        groupMap.insert(std::pair<std::string, ChannelGroup*>(groupName, cg));
    }
    else{
        cout << "ChannelGroup object with same name already exists." << endl;
        return;
    }
}

void SoundManager::addSoundToChannelGroup(std::string groupName, std::string soundName){
    auto find_group_it = groupMap.find(groupName);
    if(find_group_it == groupMap.end()){
        cout << "No ChannelGroup found" << endl;
    }
    else{
        auto find_sound_it = soundMap.find(soundName);
        if(find_sound_it == soundMap.end()){
            cout << "No Sound found" << endl;
        }
        else{
//            (find_sound_it->second)->channel->setChannelGroup((find_group_it->second));
            (find_sound_it->second)->channel->setChannelGroup((find_group_it->second)->channelGroup);
        }
    }
}

void SoundManager::setChannelGroupVolume(std::string groupName, float volume){
    auto find_group_it = groupMap.find(groupName);
    if(find_group_it == groupMap.end()){
        cout << "No ChannelGroup found" << endl;
    }
    else{
//        (find_group_it->second)->setVolume(volume);
        (find_group_it->second)->channelGroup->setVolume(volume);
    }
}

void SoundManager::playSound(std::string soundObjectName){
    Sound* sound = findSound(soundObjectName);
    if(sound){
        sound->channel->setPaused(false);
        fmodSystem->update();
    }
}

void SoundManager::pauseSound(std::string soundObjectName){
    Sound* sound = findSound(soundObjectName);
    if(sound){
        sound->channel->setPaused(true);
        fmodSystem->update();
    }
}

void SoundManager::stopSound(std::string soundObjectName){
    Sound* sound = findSound(soundObjectName);
    if(sound){
        sound->channel->stop();
        fmodSystem->update();
    }
}

void SoundManager::FMODErrorCheck(FMOD_RESULT result){
    if (result != FMOD_OK){
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
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