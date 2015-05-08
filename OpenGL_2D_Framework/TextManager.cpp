//
//  TextManager.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "TextManager.h"
#include "Director.h"

TextManager::TextManager():
face(0),
glyph(0),
originalSize(0),
currentSize(0),
prog(0),
vao(0),
vbo(0),
fontCoords(0),
textTex(0)
{
    prog = Director::getInstance().getProgramPtr("Text");
//    prog = Director::getInstance().getProgramPtr();
}

TextManager::~TextManager(){
    //This class has nothing to release.
    //You can release shader program here. But I made my program(not this class) to release when program terminate.
    
    glDeleteTextures(1, &textTex);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uvbo);
    glDeleteBuffers(1, &ibo);
}

void TextManager::loadFont(std::string path, int height){
    if( FT_Init_FreeType( &library ) ){
        library = 0;
        cout << "Failed to init FreeType." << endl;
        return;
    }
    
    if(FT_New_Face(library, path.c_str(), 0, &face)){
        cout << "TextManager::Failed to load face. " << endl;
        return;
    }
    
    currentSize = height;
    
    FT_Set_Pixel_Sizes(face, 0, height);
    
    
//    for(size_t i = ' '; i <= '~'; ++i){
        if(FT_Load_Char(face, 'a', FT_LOAD_RENDER)){
//            cout << "Failed to load char: " << (char)i << endl;
//            continue;
        }
        
        FT_Glyph glyph;
        if(FT_Get_Glyph(face->glyph, &glyph)){
            cout << "Failed to get glyph" << endl;
//            continue;
        }
        
        FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
        FT_GlyphSlot slot = face->glyph;
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
        //        FT_Bitmap& bitmap = slot->bitmap;
        FT_Bitmap bitmap = bitmap_glyph->bitmap;
        
        
        GlyphData gData;
        //update reference
        gData.bitmap_buffer = new unsigned char[bitmap.rows * bitmap.width * sizeof(unsigned char)];
        
        memcpy(gData.bitmap_buffer, bitmap.buffer, bitmap.rows * bitmap.width * sizeof(unsigned char));
        
        gData.bitmap_width = bitmap.width; // copy texture width
        gData.bitmap_rows = bitmap.rows; // copy texture height
        gData.bitmap_left = slot->bitmap_left; // copy glyph width (pixels)
        gData.bitmap_top = slot->bitmap_top; // copy glyph height (pixels)
        gData.advance = glyph->advance; // copy the advance vector (note this isn't c++ vector, this is real vector)
//        gData.c = (char)i; // set the character
    gData.c = 'a';
        gData.size = currentSize; // set the size
        gData.valid = true;
        
        GLuint textureObject;
        glGenTextures(1, &textureObject);
        glBindTexture(GL_TEXTURE_2D, textureObject);
        
        gData.texObj = textureObject;
        
        // set texture parameters. Linear and clamp to edge.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, gData.bitmap_buffer);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    
        float x = 0;
        float y = 0;
        float sx = 10.0f / 1280.0f;
        float sy = 10.0f / 720.0f;
        
        float x2 = x + gData.bitmap_left * sx;
        float y2 = -y - gData.bitmap_top * sy;
        float w = gData.bitmap_width * sx;
        float h = gData.bitmap_rows * sy;
        
//        glm::vec4 box[4] = {
//            {x2, -y2, 0, 0},
//            {x2 + w, -y2, 1, 0},
//            {x2, -y2 - h, 0, 1},
//            {x2 + w, -y2 - h, 1, 1},
//        };
        
//        glm::vec4 box[4] = {
//            {-10, -10, 0, 0},
//            {-10, 10, 1, 0},
//            {10, -10, 0, 1},
//            {10, 10, 1, 1},
//        };
    
//        vertexData.clear();
//        uvVertexData.clear();
//        indicesData.clear();
    
    float cWidth = 5;
    float cHeight = 10;
    
        vertexData.push_back(glm::vec3(-cWidth/2, -cHeight/2, 10));
        vertexData.push_back(glm::vec3(-cWidth/2, cHeight/2, 10));
        vertexData.push_back(glm::vec3(cWidth/2, -cHeight/2, 10));
        vertexData.push_back(glm::vec3(cWidth/2, cHeight/2, 10));
        
        uvVertexData.push_back(glm::vec2(0, 0));	//bot left
        uvVertexData.push_back(glm::vec2(0, 1));	//top left
        uvVertexData.push_back(glm::vec2(1, 0));	//bot right
        uvVertexData.push_back(glm::vec2(1, 1));	//top right
    
        indicesData.push_back(0);
        indicesData.push_back(1);
        indicesData.push_back(2);
        indicesData.push_back(1);
        indicesData.push_back(2);
        indicesData.push_back(3);
    
//        glGenVertexArrays(1, &gData.vao);
//        glGenBuffers(1, &gData.vbo);
//        glGenBuffers(1, &gData.uvbo);
//        glGenBuffers(1, &gData.ibo);
//        
//        glBindVertexArray(gData.vao);
//        glBindBuffer(GL_ARRAY_BUFFER, gData.vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, gData.uvbo);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gData.ibo);
    
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        //generate vertex buffer object for quad
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
        glVertexAttribPointer(prog->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
        
        //generate texture uv buffer object for quad
        glGenBuffers(1, &uvbo);
        glBindBuffer(GL_ARRAY_BUFFER, uvbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
        glVertexAttribPointer(prog->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
        
        //generate indices buffer
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
        
        glBindVertexArray(0);
        
        
        
//    glyphMap.insert(std::pair<char, GlyphData>((char)i, gData)); // put newGlyphData into 'glyphs' vector for later reuse
    glyphMap.insert(std::pair<char, GlyphData>('a', gData));
//    }
}

void TextManager::setText(std::string text){
//    for(int i = 0; i<text.length(); i++){
//        char c = text[i];
//        GlyphData gData = glyphMap.at(c);
//        
//    }
    currentText = text;
}

void TextManager::renderText(){
//    glUseProgram(prog->getObject());
    glm::mat4 modelMat = glm::mat4();
    glm::mat4 rotateMat = glm::mat4();
    glm::mat4 translateMat = glm::mat4();
    glm::mat4 scaleMat = glm::mat4();
//    glm::mat4 translateMat = glm::translate(glm::mat4(), glm::vec3(20, 20, 0));
//    scaleMat = glm::scale(glm::mat4(), glm::vec3(10, 10, 1));
    
    int offset = 0;
//    for(size_t i = ' '; i <= '~'; ++i){
//        char c = (char)i;
    char c = 'a';
        GlyphData gData = glyphMap.at(c);
    
        //Camera Matrix. Projection * view.
        GLuint cameraUniformLocation = glGetUniformLocation(prog->getObject(), "cameraMat");
        glm::mat4 cameraMat = Director::getInstance().getCameraPtr()->getMatrix();
        glUniformMatrix4fv(cameraUniformLocation, 1, GL_FALSE, &cameraMat[0][0]);
    
        GLint modelUniformLocation = glGetUniformLocation(prog->getObject(), "modelMat");
        if(modelUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "modelMat");
        glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, &modelMat[0][0]);
        
        GLint rotateUniformLocation = glGetUniformLocation(prog->getObject(), "rotateMat");
        if(rotateUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "rotateMat");
        glUniformMatrix4fv(rotateUniformLocation, 1, GL_FALSE, &rotateMat[0][0]);
        
        GLint translateUniformLocation = glGetUniformLocation(prog->getObject(), "translateMat");
        if(translateUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "translateMat");
        glUniformMatrix4fv(translateUniformLocation, 1, GL_FALSE, &translateMat[0][0]);
        
        GLint scaleUniformLocation = glGetUniformLocation(prog->getObject(), "scaleMat");
        if(scaleUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "scaleMat");
        glUniformMatrix4fv(scaleUniformLocation, 1, GL_FALSE, &scaleMat[0][0]);

        
        GLuint tarVao = gData.vao;
        glBindVertexArray(vao);
        
        
        // Enable the vertex attributes for position, texcoord, and color.
        // See the shader for details.
        glEnableVertexAttribArray(prog->attrib("vert"));
        glEnableVertexAttribArray(prog->attrib("uvVert"));
        
        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, gData.texObj);
        glBindTexture(GL_TEXTURE_2D, gData.texObj);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        offset++;
        glBindVertexArray(0);
//        break;
//    }
}

