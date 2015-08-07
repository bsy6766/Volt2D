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
#include "Actions.h"

namespace Volt2D{
    /**
     *  @class Transition
     *  @brief Virtual base class for Scene transitions.
     */
    class Transition{
    protected:
        /** Protected constructor */
        Transition();

        /** Next scene to replace */
        Scene* nextScene;
        
        /** total duration of scene transition */
        double duration;
        
        /** Finish flag. ture if transition is done. */
        bool done;
        
        /** delay padding between actions */
        ActionDelay* delayPad;
        
        ActionCallFunc* callEndFunc;
        ActionCallFunc* callSwapSceneFunc;
        ActionCallFunc* callOnEnter;
        
        void callEnterFunc();
    private:
        //no private sir
    public:
        /** virtual desctructor */
        virtual ~Transition();
        
        /** Check if transition is done or not */
        bool isDone();
        
        /** Finish scene transition */
        void end();
        
        /// @{
        /// @name Virtual functions
        /** Start scene transition */
        virtual void start() = 0;
        
        /** Update scene transition effects */
        virtual void update(double dt){};
        
        /** Render scene transition effects */
        virtual void render() = 0;
        
        /** Swap current scene with next scene. */
        virtual void swapScene();
        /// @}
    };
        
    /**
     *  @class TransitionFade
     *  @brief Transition between scene by color fade
     *  @note Duration means total time that will take to finish scene traistion, not for each fade effect.
     */
    class TransitionFade : public Volt2D::Transition{
    private:
        /**
         *  Private constructor.
         */
        TransitionFade();
        
        /** Custom texture with color */
        Texture* texture;
        
        /** Fade sprite */
        Sprite* effect;
        
        /**
         *  Initialize transiton fade
         *  @param duration Total duration of scene transition
         *  @param color Fading color.
         *  @param nextScene Next scene to replace
         */
        bool initTransition(double duration, Color color, Scene* nextScene);
        
    public:
        /**
         *  Create TransitionFade.
         *  @param duration Total duration of scene transition
         *  @param color Fading color
         *  @param nextScene Next scene to replace
         */
        static TransitionFade* createWithColor(double duration, Color color, Scene* scene);
        
        /** Destructor */
        ~TransitionFade();
        
        /// @{
        /// @name Override from Volt2D::Transition class
        /** Start scene transition */
        virtual void start() override;
        
        /** Update scene transition effects */
        virtual void update(double dt) override;
        
        /** Render scene transition effects */
        virtual void render() override;
        /// @}
    };
    
    enum class TransitionDirection{
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };
    
    /**
     *  @class TransitionMove
     *  @brief Transition scene by moving from direction
     */
    class TransitionMove : public Transition{
    private:
        /** Private constructor */
        TransitionMove();
        
        /**
         *  Initialize TransitionMove
         *  @param duration Total duration of scene transition
         *  @param direction Direction to move scene while transition
         *  @param nextScene Next scene to replace
         */
        void initTransition(double duration, Volt2D::TransitionDirection direction, Scene* nextScene);
        
        /** flag for scene rendering */
        bool sceneSwapped;
    public:
        /**
         *  Create TransitionMove
         *  @param duration Total duration of scene transition
         *  @param direction Direction to move scene while transition
         *  @param nextScene Next scene to replace
         */
        static TransitionMove* createWithDirection(double duration, Volt2D::TransitionDirection direction, Scene* nextScene);
        
        /** Destructor */
        ~TransitionMove();
        
        /// @{
        /// @name Override from Volt2D::Transition class
        /** Start scene transition */
        virtual void start() override;
        
        /** Update scene transition effects */
        virtual void update(double dt) override;
        
        /** Render scene transition effects */
        virtual void render() override;
        
        /** Swap current scene with next scene. */
        virtual void swapScene() override;
        /// @}
    };
    
    //\todo TransitionSlide
    
    /**
     *  @class TransitionFlip
     *  @brief Transition scene by flipping from direction
     */
    class TransitionFlip : public Transition{
    private:
        /** Private Constructor */
        TransitionFlip();
        
        /**
         *  Intialize Transition
         *  @param duration Total duration of scene transition
         *  @param direction Direction to move scene while transition
         *  @param nextScene Next scene to replace
         */
        void initTransition(double duration, Volt2D::TransitionDirection direction, Scene* nextScene);

    public:
        /**
         *  Create TransitionFlip
         *  @param duration Total duration of scene transition
         *  @param direction Direction to move scene while transition
         *  @param nextScene Next scene to replace
         */
        static TransitionFlip* createWithDirection(double duration, Volt2D::TransitionDirection direction, Scene* nextScene);
        
        /** Destructor */
        ~TransitionFlip();
        /// @{
        /// @name Override from Volt2D::Transition class
        /** Start scene transition */
        virtual void start() override;
        
        /** Update scene transition effects */
        virtual void update(double dt) override;
        
        /** Render scene transition effects */
        virtual void render() override;
        /// @}
    };
}   //namespace end

#endif /* defined(__Volt2D__Transition__) */
