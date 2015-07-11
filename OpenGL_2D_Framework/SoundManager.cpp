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
    result = bgm->release();
    FMODErrorCheck(result);
    result = fmodSystem->release();
    FMODErrorCheck(result);
}

void SoundManager::createBGM(const char *file){
    FMOD_RESULT result = fmodSystem->createSound(file, FMOD_LOOP_NORMAL, 0, &bgm);
    FMODErrorCheck(result);
}

void SoundManager::playBGM(){
    FMOD_RESULT result = fmodSystem->playSound(bgm, NULL, false, &musicChannel);
    FMODErrorCheck(result);
}

void SoundManager::FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}