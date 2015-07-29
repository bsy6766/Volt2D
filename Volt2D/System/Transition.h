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
#include "Color.h"

namespace Volt2D{
class Transition{
protected:
    Transition();
    Scene* currentScene;
    Scene* nextScene;
    
    void setNextScene(Scene* nextScene);
private:
    double duration;
public:
    virtual ~Transition();
};
    

class TransitionFade : public Volt2D::Transition{
private:
    TransitionFade() = delete;
    /**
     *  Private constructor.
     */
    TransitionFade(Color color);
    
    /**
     *  Color to fade
     */
    Color color;
    
    /**
     *  Custom texture with color
     */
    
public:
    static TransitionFade* createWithColor(Color color, Scene* scene);
    ~TransitionFade();
};
    
}

#endif /* defined(__Volt2D__Transition__) */
