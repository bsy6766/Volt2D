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

const float POWER_SCALE = 10;
const int MAX_PARTICLE_COUNT = 1000;
//const float GRAVITY = 9.81;

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
    
    /**
     *  Position Variance. Applies to current position of object.
     */
    glm::vec3 posVar;
    
    /**
     *  Blending option
     *  true if blends between particles
     *  false if render based on z depth
     *  Default blending mode for particle system is GL_SRC_ALPHA and GL_ONE for src and dest.
     */
    bool blend;
    
    /**
     *  Particle size. Can't be less than 0
     */
    int size;
    
    /**
     *  Total number of particle created ever since particle system started.
     */
    int totalCreatedParticles;
    
    /**
     *  Number of particle currently alive in particle system.
     */
    int livingParticleNum;
    
    /**
     *  Duration of system. -1 means infinite.
     */
    double duration;
    
    /**
     *  Total elapsed time of this system. If exceeds duration, it stops creating particles unless duration is -1
     */
    double totalElapsedTime;
    
    /**
     *  Stating color of each particle.
     */
    Color startColor;
    
    /**
     *  Variance for starting color
     */
    Color startColorVar;
    
    /**
     *  Ending color of each particle
     */
    Color endColor;
    
    /**
     *  Variance for ending color
     */
    Color endColorVar;
    
    /**
     *  true if you want to apply color values to each particle. Else, false.
     *  Set false to display each particle's texture with out adding color on it if texture is sprite.
     */
    bool applyColor;
    
    /**
     *  Base speed of each particle. Used to compute direction vector for each particle
     */
    float speed;
    
    /**
     *  Variance for speed
     */
    float speedVar;
    
    /**
     *  Gravity for x coordinates. Positive value applies gravity from left to right and vice versa for negative value.
     */
    float gravityX;
    
    /**
     *  Gravity for y coordinates. Positive value applies gravity from top to bottom and vice versa for negative value
     */
    float gravityY;
    
    /**
     *  Tangential acceleration. Perpendicular to particle's direction.
     */
    float tanAccel;
    
    /**
     *  Varaince for tangential acceleration.
     */
    float tanAccelVar;
    
    /**
     *  Radial acceleration. Positive value pushes away from spawned position, negative calue pulls particle to spawned position.
     */
    float radialAccel;
    
    /**
     *  Variance for radial acceleration
     */
    float radialAccelVar;
    
    /**
     *  Number of particle created per second.
     */
    float emissionRate;
    
    /**
     *  Angle of direction in degree for particle's movement.
     */
    float emitAngle;
    
    /**
     *  Variance for emission angle.
     */
    float emitAngleVar;
    
    /**
     *  Starting size. 
     *  Min = 0, Max = 255.
     *  Each particle will be scaled based on value.
     *  Default particles' texture are 256 pixels wide and long.
     */
    float startSize;
    
    /**
     *  Variance for starting size
     */
    float startSizeVar;
    
    /**
     *  Ending size. Same as starting size.
     */
    float endSize;
    
    /**
     *  Variance for ending size.
     */
    float endSizeVar;
    
    /**
     *  Duration of each particle's life.
     */
    double lifeTime;
    
    /**
     *  Variance for life time.
     */
    double lifeTimeVar;
    /// @}
    
    /// @{
    /// @name PartcielSystem datas
    
    /**
     *  Stores all particle.
     */
    std::list<Particle*> particleList;
    
    /**
     *  Texture for each particle. 
     *  Default textures available.
     */
    Texture *texture;
    
    /**
     *  Particle's position data buffer object
     */
    GLuint vpbo;
    
    /**
     *  Particle's color data buffer object
     */
    GLuint cbo;
    
    /**
     *  Particle's size(scale) data buffer object
     */
    GLuint sbo;
    
    /// @}

    //Private constructor
    ParticleSystem();
    
    /**
     *  Life point storage on this system
     *  Since elapsed time always varies and not meseaured is second, particle might not always spawn on each iteration.
     *  If so, we store partial value of emission rate based on elapsed time.
     *  If this exceeds 1, then we spawn particle based on this point value, excluding floating point.
     */
	float newLifePoint;

    /**
     * Initialize particle's texture.
     * @param textureName Name for particle's texture file. Default is set to blurred circle texture.
     *  @param target A texture target
     */
    void initCustomTexture(string textureName = "system/default_particle.png", GLenum target = GL_TEXTURE_2D);
    
    /**
     *  Initialize texture with default texture
     *  Default: Blurred circle.
     */
    void initDefaultTexture();
    
    /**
     *  Initialize with size only. 
     *  Uses default texture
     */
    void initWithSize(int size);
    
    /**
     *  Initialize with Lua script.
     *  @param luaFileName A file name for lua script
     *  @note Default texture is used if texture name is empty.
     */
    bool initWithLua(string luaFileName);
    
    /**
     *  Compute particle's vertex data
     */
    void computeVertexData();
    
    /**
     *  Load vertex.
     *  Particle's position data, color data, and size data is initialized with blank buffer.
     */
    void loadVertexData();
    
    /**
     *  Initialize system's variables. 
     *  @return false if fails to initialize or condition doesn't meet.
     */
    bool initialize();
public:
    //Destructor
    ~ParticleSystem();
    
    /**
     *  Create particle system
     *  @param objectName Object's name
     *  @param size Particle size for this system.
     */
    static ParticleSystem* createWithSize(string objectName, int size = 0);
    
    /**
     *  Create particle system with lua config
     *  @param objectName An object name for particle system
     *  @param fileName Lua script file name
     */
    static ParticleSystem* createWithLuaConfig(string objectName, string fileName);
    
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
    
    /// @{
    /// @name Setters
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
    /// @}
};

#endif /* defined(__OpenGL_2D_Framework__ParticleSystem__) */
