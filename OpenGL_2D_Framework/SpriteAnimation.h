//
//  SpriteAnimation.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/23/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteAnimation__
#define __OpenGL_2D_Framework__SpriteAnimation__

#include "Texture.h"
#include "SpriteObject.h"
#include "Timer.h"

#include <map>

/**
 *  @class Animation
 *  @brief Has basic animation data.
 */
struct Animation{
    double interval;
    int size;
    string name;
    Texture* textureAtlas;
    /**
     *  First animation ever uses
     */
    BufferObject bufferObject;
    int currentFrameIndex;
    float textureWidth;
    float textureHeight;
    double intervalCounter;
};

/**
 *  @class SpriteAnimation
 *  @breif A class that is similar to Sprite but can have animations.
 *  
 *  SpriteAnimation can hold multiple animation by string name.
 *
 *  Vertex size
 *  SpriteAnimation can have various size of sprite (quad vertex). 
 *  You can set the specific size of quad when you create, or it will follow the size of first frame texture of the animation.
 *
 *  Texture file format
 *  To load multiple frame textures, all files must follow the animation name and numbering.
 *  The format is <animation name>_<number>.
 *  Number starts from 1. 
 *  i.e.) If you create an animation called "run", the frame texture files' name must be
 *  run_1, run_2, run_3, and so on.
 */
class SpriteAnimation : public SpriteObject{
private:
    /**
     *  Animation storage. Store Animation objects by string name as an ID
     */
    std::map<string/*Animation Name*/, Animation> animationMap;

    /**
     *  Empty means object play no animation.
     */
    string runningAnimationName;
    
    /**
     *  Compute vertex and indices
     *  @param width Quad width
     *  @param height Quad height
     */
    void computeVertexData(float texWidth, float texHeight, float imgW, float imgH);
    
    /**
     *  Load computed vertex.
     */
    void loadVertexData(Animation& ani);
    
    /**
     *  Overrides's Object::render();
     *  Render object
     */
    virtual void render() override;
    
    //private structor
    SpriteAnimation();
    
    /**
     *  Initialize with 
     */
    bool initWithAnimation(string name, string textureName, int size, double interval);
    
public:
    /**
     *  Create SpriteAnimation object without any animation on it. 
     *  @param objectName An object's name
     */
    static SpriteAnimation* create(string objectName);
    
    /**
     *  Create SpriteAnimation with animation
     *  @param objectName An object's name
     *  @param animationName String ID for animation
     *  @param textureName Animation texture name without numbering.
     *  @param frameSize Size of animation's frame. Must be greater than 0.
     *  @param frameInterval A frameInterval between each animation frame
     *  @return New SpriteAnimation instance if successfuly initialize. Else, nullptr.
     */
    static SpriteAnimation* createWithAnimation(string objectName, string animationName, string textureName, int frameSize, double frameInterval);
    
    //Destructor
    ~SpriteAnimation();
    
    /**
     *  Add Animation to this object.
     *  @param animationName String ID for animation
     *  @param textureName Animation texture name without numbering.
     *  @param frameSize Size of animation's frame. Must be greater than 0.
     *  @param frameInterval A frameInterval between each animation frame
     */
    void addAnimation(string name, string textureName, int frameSize, double frameInterval);
    
    /**
     *  Play animation
     *  @param Animation's name to play
     */
    void playAnimation(string name);
    
    /**
     *  Stop animation.
     */
    void stopAnimation();
};

#endif /* defined(__OpenGL_2D_Framework__SpriteAnimation__) */
