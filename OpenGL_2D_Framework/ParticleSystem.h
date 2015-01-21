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
const float GRAVITY = 9.81;

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
    //std::vector<GLfloat> vertexDistanceData;
    std::vector<GLushort> indicesData;
    
    Texture *texture;
    Program *progPtr;
    
    int liveCount;
    
    //time
	//double totalElapsedTime;
	float totalElapsedTime;
    double duration;
	double particlePerSec;
    
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
	int livingParticleNum;
    
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

	//accumulative new life point.
	//if it gets bigger than 0, add new particle and keep the fractional point.
	//else, keep build up the point
	float newLifePoint;

	/**
	* Computes random number between the range.
	* This function handles all type of number
	*/
    template<typename Type>
    Type computeRandom(Type min, Type max){
            Type randVal = (Type)rand() / RAND_MAX;
            return min + randVal * (max - min);
    }
    
public:
    static ParticleSystem* initWithParticleSize(int size);
    ~ParticleSystem();
    
    /**
     * Initialize particle's texture. 
     * If this function isn't called(or if texture isn't set),
     * then the particle system use default texture(circle).
     */
    void initParticleTexture(GLenum _textureTarget, const std::string& _fileName, Program* progPtr);
   
	/**
	* Particle system initializer
	* @param duration the duration of the particle system
	* @param lifeTime the base life time of single particle
	* @param lifeTimeVar the range between maximum and minimum variance of life time
	* @param speed the movement speed of single particle
	* @param speedVar the range between maximum and minimum variance of speed
	* @param emitAngle the particle's emitting direction(degree angle)
	*/
	void initParticleSystem(
                            double duration,
                            double lifeTime,
                            double lifeTimeVar,
                            float speed,
                            float speedVar,
                            double emitAngle,
                            double emitAngleVar,
                            float gravityX,
                            float gravityY
                            );
    /**
     * Render particles. 
     * Render only living ones.
     */
    void render();

	/**
	* A particle update function.
	* Based on elpased time, add new particles and remove dead ones
	* It updates each particle's position data.
	*/
    void update();
    
    /**
     * Set particle system's position
     */
    void setPosition(glm::vec2 position);
};

#endif /* defined(__CS364FinalProject__ParticleSystem__) */
