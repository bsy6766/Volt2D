//
//  ParticleSystem.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/25/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#ifndef __CS364FinalProject__ParticleSystem__
#define __CS364FinalProject__ParticleSystem__

#include "Particle.h"
#include "Sprite.h"
#include <list>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Timer.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include "Program.h"

const int MAX_PARTICLE_COUNT = 1000;

class ParticleSystem{
private:
    //testing private constructor!
    ParticleSystem(int size);
    
    std::list<Particle*> particleList;
    
    //opengl
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint uvbo;
    GLuint vpbo;    //vertex position buffer

    std::vector<GLfloat> vertexData;
    std::vector<glm::vec2> uvVertexData;
    std::vector<GLfloat> vertexDistanceData;
    std::vector<GLushort> indicesData;
    
    Texture *texture;
    Program *progPtr;
    
    int liveCount;
    
    //time
    double totalElapsedTime;
    double duration;
    
    //visibility
    bool visible;
    
    //life time + rand
    double lifeTime;
    double lifeTimeVar;
    
    //gravity + rand
    float gravityX;
    float gravityXVar;
    float gravityY;
    float gravityYVar;
    
    //Texture
    
    //number. This is fixed.
    int totalParticleCount;
    int totalCreatedParticles;
    
    //emit
    double emitAngle;
    double emitAngleVar;
    
    //size
    float startSize;
    float startSizeRand;
    float endSize;
    float endSizeRand;
    
    //opacity
//    float startOpacity;
//    float endOpacity;

    //position
    glm::vec2 position;
    
    //speed
    float speed;
    float speedVar;

    void sortParticleList();
    void removeDeadParticles();

    template<typename Type>
    Type computeRandom(Type min, Type max){
            Type randVal = (Type)rand() / RAND_MAX;
            return min + randVal * (max - min);
    }
    
public:
    static ParticleSystem* initWithSize(int size);
    ~ParticleSystem();
    
    void initParticleTexture(GLenum _textureTarget, const std::string& _fileName, Program* progPtr);
    void initParticleSystem(double duration, double lifeTime, double lifeTimeVar, float speed, float speedVar, double emitAngle, double emitAngleVar, float gravityX, float gravityY);
    void setPosition(glm::vec2 position);
    void render();
    void update();
};

#endif /* defined(__CS364FinalProject__ParticleSystem__) */
