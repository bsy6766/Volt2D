//
//  SpriteBatch.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/19/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__SpriteBatch__
#define __OpenGL_2D_Framework__SpriteBatch__

class SpriteBatch{
private:
    SpriteBatch();
public:
    /**
     *  Create SpriteBatch (SpriteSheet)
     *  @param textureFileName A texture to batch. Recommended to use size of power of 2.
     *  @param textureFramefileName A xml file that contains each image's position in texture.
     */
    static SpriteBatch* createSpriteBatch(const char* textureFileName, const char* textureFrameFileName);
    
    //Destructor
    ~SpriteBatch();
    
    void addChild();
};

#endif /* defined(__OpenGL_2D_Framework__SpriteBatch__) */
