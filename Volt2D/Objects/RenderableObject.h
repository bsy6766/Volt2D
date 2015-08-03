//
//  RenderableObject.h
//  Volt2D
//
//  Created by Seung Youp Baek on 5/13/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __Volt2D__RenderableObject__
#define __Volt2D__RenderableObject__

#include "Object.h"
#include "Program.h"
#include "Scene.h"
#include <vector>
#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace Volt2D{
/**
 *  @class RenderableObject
 *  @brief A object that is renderable on screen. Contains several OpenGL varaibles.
 *  \todo Support anchor point for all object.
 */
class RenderableObject : public Volt2D::Object{
protected:
    /**
     *  Protected constructor
     */
    RenderableObject();
    
    /**
     *  @struct BufferObject
     *  @brief Contains vertex array object and buffer objects
     */
    struct BufferObject{
        GLuint vao;
        GLuint vbo;
        GLuint uvbo;
        GLuint ibo;
    };
    
    /** A pack of essential OpenGL objects */
    BufferObject bufferObject;
    
    /** A std::vector that stores all vertices */
    std::vector<glm::vec3> vertexData;
    
    /** A std::vector that stores all uv vertices */
    std::vector<glm::vec2> uvVertexData;
    
    /**
     *  A std::vector that stores all indices
     */
    std::vector<GLushort> indicesData;
    
    /** Pointer to rendering OpenGL Progream */
    Volt2D::Program *progPtr;
    
    
    /** true if using sprite sheet */
    bool useSpriteSheet;
    
    /**
     *  Pass int value to shader
     *  @param name Uniform name
     *  @param i (ref) A int value to pass to shader
     */
    void intUniformLocation(std::string name, int& i);
    /**
     *  Pass float value to shader
     *  @param name Uniform name
     *  @param f (ref) A float value to pass to shader
     */
    void floatUniformLocation(std::string name, float& f);
    
    /**
     *  Pass bool value to shader
     *  @param name Uniform name
     *  @param b A bool value to pass to shader
     */
    void boolUniformLocation(std::string name, bool b);
    
    /**
     *  Pass glm::vec3 value to shader
     *  @param name Uniform name
     *  @param vec (ref) A glm::vec3 value to pass to shader
     */
    void vec3UniformLocation(std::string name, glm::vec3& vec);
    
    /**
     *  Pass glm::mat4 value to shader
     *  @param name Uniform name
     *  @param matrix A glm::mat4 value to pass to shader
     */
    void matrixUniformLocation(const std::string name, const glm::mat4& matrix);
private:
    //no privates
public:
    //virtual destructor
    virtual ~RenderableObject();
    
    /**
     *  Clear vertices and indices vectors and delete buffer objects.
     */
    void deleteVertexData();
    
    /**
     *  Bind OpenGL Program to object.
     *  @param programName A OpenGL Program name to bind. This program will be used to render
     */
    void bindProgram(std::string programName);
    
    /**
     *  Visibility.
     */
    bool visible;
};
}   //namespace end

#endif /* defined(__Volt2D__RenderableObject__) */
