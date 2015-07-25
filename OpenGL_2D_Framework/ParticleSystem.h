//
//  ParticleSystem.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/25/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ParticleSystem__
#define __OpenGL_2D_Framework__ParticleSystem__

#include "Particle.h"
#include "RenderableObject.h"
#include <list>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Timer.h"
#include "Texture.h"
#include "Color.h"
#include "LuaConfig.h"

const int MAX_PARTICLE_COUNT = 1000;
const float GRAVITY = 9.81;

/**
 *  @class ParticleSystem
 *  @brief Basic particle system
 *  @note ParticleSystem must be initialized with size greater than 0
 *  @note Each particle doesn't have their own transform
 */
class ParticleSystem : public RenderableObject{
private:
    /// @{
    /// @name Particle system attributes
    
//    int totalParticleCount;
    int size;
    int totalCreatedParticles;
    int livingParticleNum;
    int liveCount;
    
    //-1 = inifnity
    double duration;
    double totalElapsedTime;
    
    Color startColor;
    Color startColorVar;
    
    Color endColor;
    Color endColorVar;
    //applying color to each particle
    bool applyColor;
    bool applyOpacity;
    
    float speed;
    float speedVar;

    float gravityX;
    float gravityXVar;
    
    float gravityY;
    float gravityYVar;
    
    float tanAccel;
    float tanAccelVar;
    
    float radialAccel;
    float radialAccelVar;
    
    //total particle number spawn per sec
    float emissionRate;
    //default: 0 degree (point north)
    float emitAngle;
    float emitAngleVar;
    
    //size
    float startSize;
    float startSizeVar;
    
    float endSize;
    float endSizeVar;
    
    //life time + rand
    double lifeTime;
    double lifeTimeVar;
    /// @}
    
    /// @{
    /// @name PartcielSystem datas
    
    std::list<Particle*> particleList;
    
    Texture *texture;
    bool usingDefaultTexture;
    
    GLuint vpbo;    //extra buffer for instancing
    
    /// @}

    //Private constructor
    ParticleSystem();
    
	//accumulative new life point.
	//if it gets bigger than 0, add new particle and keep the fractional point.
	//else, keep build up the point
	float newLifePoint;

    /**
     * Initialize particle's texture.
     * If this function isn't called(or if texture isn't set),
     * then the particle system use default texture(circle).
     */
    void initCustomTexture(string textureName = "system/default_particle.png", GLenum target = GL_TEXTURE_2D);
    
    void initDefaultTexture();
    
    void initWithSize(int size);
    
    bool initWithLua(string xmlFileName);
    
    void computeVertexData();
    
    void loadVertexData();
    
    bool initialize();
public:
    //Destructor
    ~ParticleSystem();
    
    /**
     *  Create particle system
     */
    static ParticleSystem* createWithSize(string objectName, int size = 0);
    
    /**
     *  Create particle system with lua config
     *  @param objectName An object name for particle system
     *  @param fileName Lua script file name
     */
    static ParticleSystem* createWithLuaConfig(string objectName, string fileName);
    
	/**
	* Particle system initializer
	* @param duration the duration of the particle system
	* @param lifeTime the base life time of single particle
	* @param lifeTimeVar the range between maximum and minimum variance of life time
	* @param speed the movement speed of single particle
	* @param speedVar the range between maximum and minimum variance of speed
	* @param emitAngle the particle's emitting direction(degree angle)
	*/
//	void initParticleSystem(
//                            double duration,
//                            double lifeTime,
//                            double lifeTimeVar,
//                            float speed,
//                            float speedVar,
//                            double emitAngle,
//                            double emitAngleVar,
//                            float gravityX,
//                            float gravityY
//                            );
    
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
     * True = dead, false = alive
     */
    bool isDead();
    
    
    void setDuration(double duration);
    void setStartColor(Color color);
    void setStartColorVar(Color color);
    void setEndColor(Color color);
    void setEndColorVar(Color color);
    void enableColor();
    void disableColor();
    void enableOpacity();
    void disableOpacity();
    void setSpeed(float speed);
    void setSpeedVar(float speed);
    void setGravityX(float gravity);
    void setGravityXVar(float gravity);
    void setGravityY(float gravity);
    void setGravityYVar(float gravity);
    void setTanAccel(float tanAccel);
    void setTanAccelVar(float tanAccel);
    void setRadialAccel(float radialAccel);
    void setRadialAccelVar(float radialAccel);
    void setEmitAngle(float angle);
    void setEmitAngleVar(float angle);
    void setLifeTime(float lifeTime);
    void setLifeTimeVar(float lifeTime);
    
};

#endif /* defined(__OpenGL_2D_Framework__ParticleSystem__) */
