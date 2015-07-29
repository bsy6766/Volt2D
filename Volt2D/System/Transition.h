//
//  Transition.h
//  Volt2D
//
//  Created by Seung Youp Baek on 7/27/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__Transition__
#define __Volt2D__Transition__

#include "Scene.h"
#include "Sprite.h"
#include "RenderableObject.h"
#include "Color.h"

namespace Volt2D{
class Transition{
protected:
    Transition();
    Scene* currentScene;
    Scene* nextScene;
    
    void setNextScene(Scene* nextScene);
    
    double duration;
    double totalElapsedTime;
    
    bool running;
private:
public:
    virtual ~Transition();
    Scene* getNextScene();
};
    

class TransitionFade : public Volt2D::Transition{
private:
    /**
     *  Private constructor.
     */
    TransitionFade();
    
    /**
     *  Color to fade
     */
    Color color;
    
    /**
     *  Custom texture with color
     */
    Texture* texture;
    Sprite* effect;
    
    GLuint vao;
    
    bool initTransition(Color color, Scene* nextScene);
    
    void swapScene();
    
public:
    static TransitionFade* createWithColor(Color color, Scene* scene);
    ~TransitionFade();
    
    void run();
};
    
}

#endif /* defined(__Volt2D__Transition__) */
