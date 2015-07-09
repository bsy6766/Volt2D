//
//  Text.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Text.h"

#define VOID_OFFSET(i) (GLvoid*)(i)

Text::Text()
//:TextObject(),
:RenderableObject(),
dirty(false),
loaded(false),
align(ALIGN_RIGHT),
start(-1),
end(-1),
fontColor(glm::vec3(255, 255, 255)) //RGB
{
    this->progPtr = Director::getInstance().getProgramPtr("Text");
//    prog = Director::getInstance().getProgramPtr();
}

Text::~Text(){
        //RenderableObject deletes buffer on destructor
//    glDeleteVertexArrays(1, &vao);
//    glDeleteBuffers(1, &vbo);
//    glDeleteBuffers(1, &uvbo);
//    glDeleteBuffers(1, &ibo);
    translationData.clear();
//    glDeleteBuffers(1, &vtbo);
}

void Text::initText(std::string label, std::string fontName = "arial.tff"){
    if(!dirty){
        dirty = true;
        this->fontName = fontName;
        text = label;
        start = 0;
        end = (int)strlen(label.c_str()) - 1;
        computeVertexData();
        loadVertexData();
    }
}

std::string Text::getText(){
    return this->text;
}

void Text::setText(std::string newText = ""){
    if (newText != text) {
        this->text = newText;
        computeVertexData();
    }
}

void Text::setColor(glm::vec3 textColor){
    if(textColor.r > 255)
        textColor.r = 255;
    
    if(textColor.g > 255)
        textColor.g = 255;
    
    if(textColor.b > 255)
        textColor.b = 255;
    
    this->fontColor = textColor;
}

void Text::computeVertexData(){
    //Compute new vertex data based on new text
    if(hasEmptyText())
        return;
    
    //clear vertex data
    vertexData.clear();
    uvVertexData.clear();
//    textureObjectData.clear();
    indicesData.clear();
    
    Font* font = FontManager::getInstance().getFont(fontName);
    if(!font){
        cout << "Failed to find font." << endl;
        loaded = false;
        return;
    }
    
    int maxHeight = 0;
    int totalWidth = 0;
//    glm::vec2 origin = glm::vec2();
    std::vector<glm::vec2> originList;
    splitByNewLine();
    getMaxValues(font, totalWidth, maxHeight, originList);
    
//    if(maxHeight == 0 || totalWidth == 0)
//        return;
//    
//    cout << "totalWidth = " << totalWidth << endl;
//    cout << "maxHeight = " << maxHeight << endl;
    
    unsigned short indicesIndex = 0;
    int index = 0;
    //iterate text splitted by new line char (\n)
    for(auto it : splittedText){
        //get the origin of the each line
        glm::vec2 origin = originList.at(index);
        index++;
        for(unsigned int i =0; i<it.length(); i++){
            //for each character
            char c = it[i];
            //get GlyphData
            GlyphData gData;
            //set validation to false
            gData.valid = false;
            font->getGlyphDataFromChar(c, gData);
            //if validation is still false, this char doesn't exist in font. Ignore it
            //TODO: let user to choose wheter to break the loop and leave as unloaded text or ignore missing chars
            if(!gData.valid)
                continue;
            
            //get data from glyph
            int bearingY = (int)(gData.metrics.horiBearingY >> 6);
            int height = (int)(gData.metrics.height >> 6);
            int width = (int)(gData.metrics.width >> 6);
            
//            glm::vec2 p1 = glm::vec2(origin.x, origin.y - (height - bearingY)); //left bottom
//            glm::vec2 p2 = glm::vec2(origin.x + width, origin.y + bearingY);
            //compute vertex quad at origin.
            glm::vec2 p1 = glm::vec2((-1) * width / 2, (-1) * (height - bearingY)); //left bottom
            glm::vec2 p2 = glm::vec2(width / 2, bearingY);
            
            p1 /= 10;
            p2 /= 10;
//            cout << "char = " << c << endl;
//            cout << "p1 = (" << p1.x << ", " << p1.y << ", 0)" << endl;
//            cout << "p2 = (" << p2.x << ", " << p2.y << ", 0)" << endl;
            
            //get point where each char has to move
            glm::vec3 fPos = glm::vec3(origin.x + width/2, origin.y, 0);
            glm::vec3 distance = (fPos - this->position);
            distance.x /= 10;
            distance.y /= 10;
            glm::mat4 transMatToFPos = glm::translate(glm::mat4(), distance);
            //compute translate matrix to fPos from origin
            translationData.push_back(transMatToFPos);

            
            vertexData.push_back(glm::vec3(p1.x, p1.y, 0)); //Left bottom
            vertexData.push_back(glm::vec3(p1.x, p2.y, 0)); //Left top
            vertexData.push_back(glm::vec3(p2.x, p1.y, 0)); //Right bottom
            vertexData.push_back(glm::vec3(p2.x, p2.y, 0)); //Right top
            
//            cout << "bot left: ( " << p1.x << ", " << p1.y << ", 0)" << endl;
//            cout << "top left: ( " << p1.x << ", " << p2.y << ", 0)" << endl;
//            cout << "bot right: ( " << p2.x << ", " << p1.y << ", 0)" << endl;
//            cout << "top right: ( " << p2.x << ", " << p2.y << ", 0)" << endl;
            
            //add uv coord. This is different from Sprite class because we didn't use stb_image to load and flip font texture.
            uvVertexData.push_back(glm::vec2(0, 1));	//top left
            uvVertexData.push_back(glm::vec2(0, 0));	//bot left
            uvVertexData.push_back(glm::vec2(1, 1));	//top right
            uvVertexData.push_back(glm::vec2(1, 0));	//bot right
            
            //add indices based on char
            indicesData.push_back(indicesIndex * 4);
            indicesData.push_back(indicesIndex * 4 + 1);
            indicesData.push_back(indicesIndex * 4 + 2);
            indicesData.push_back(indicesIndex * 4 + 1);
            indicesData.push_back(indicesIndex * 4 + 2);
            indicesData.push_back(indicesIndex * 4 + 3);
            
            //advance origin
            origin.x += (gData.metrics.horiAdvance >> 6);
            
            indicesIndex++;
        }
    }
    
//    for(unsigned int i = 0; i<text.length(); i++){
//        //for each character
//        char c = text[i];
//        //get GlyphData
//        GlyphData gData;
//        //set validation to false
//        gData.valid = false;
//        font->getGlyphDataFromChar(c, gData);
//        //if validation is still false, this char doesn't exist in font. Ignore it
//        //TODO: let user to choose wheter to break the loop and leave as unloaded text or ignore missing chars
//        if(!gData.valid)
//            continue;
//        
////        //add texture object for that char
////        textureObjectData.push_back(gData.texObj);
//        
//        //add vertex data
//        int bearingY = (int)(gData.metrics.horiBearingY >> 6);
//        int height = (int)(gData.metrics.height >> 6);
//        int width = (int)(gData.metrics.width >> 6);
//        
//        if(c == ' ')
//            width = 15;
//        
//        glm::vec2 p1 = glm::vec2(origin.x, origin.y - (height - bearingY)); //left bottom
//        glm::vec2 p2 = glm::vec2(origin.x + width, origin.y + bearingY);
//        
//        cout << "p1 = (" << p1.x << ", " << p1.y << ", 0)" << endl;
//        cout << "p2 = (" << p2.x << ", " << p2.y << ", 0)" << endl;
//        p1 /= 10;
//        p2 /= 10;
//        
//        vertexData.push_back(glm::vec3(p1.x, p1.y, 0)); //Left bottom
//        vertexData.push_back(glm::vec3(p1.x, p2.y, 0)); //Left top
//        vertexData.push_back(glm::vec3(p2.x, p1.y, 0)); //Right bottom
//        vertexData.push_back(glm::vec3(p2.x, p2.y, 0)); //Right top
//        
//        
////        cout << "bot left: ( " << p1.x << ", " << p1.y << ", 0)" << endl;
////        cout << "top left: ( " << p1.x << ", " << p2.y << ", 0)" << endl;
////        cout << "bot right: ( " << p2.x << ", " << p1.y << ", 0)" << endl;
////        cout << "top right: ( " << p2.x << ", " << p2.y << ", 0)" << endl;
//        
//        //add uv coord. This is different from Sprite class because we didn't use stb_image to load and flip font texture.
//        uvVertexData.push_back(glm::vec2(0, 1));	//top left
//        uvVertexData.push_back(glm::vec2(0, 0));	//bot left
//        uvVertexData.push_back(glm::vec2(1, 1));	//top right
//        uvVertexData.push_back(glm::vec2(1, 0));	//bot right
//        
//        //add indices based on char
//        indicesData.push_back(indicesIndex * 4);
//        indicesData.push_back(indicesIndex * 4 + 1);
//        indicesData.push_back(indicesIndex * 4 + 2);
//        indicesData.push_back(indicesIndex * 4 + 1);
//        indicesData.push_back(indicesIndex * 4 + 2);
//        indicesData.push_back(indicesIndex * 4 + 3);
//        
//        //advance origin
//        origin.x += (gData.metrics.horiAdvance >> 6);
//        
//        indicesIndex++;
//    }
    

}

void Text::loadVertexData(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //generate vertex buffer object for quad
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate texture uv buffer object for quad
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate indices buffer
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
    
    //generate translation buffer
//    glGenBuffers(1, &vtbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vtbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * translationData.size(), &translationData[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(progPtr->attrib("charTransVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
//    //
//    glBindVertexArray(0);
    
    loaded = true;
}

void Text::getMaxValues(Font* font, int &width, int &height, std::vector<glm::vec2>& originList){
    originList.clear();
//    width = 0;
//    height = 0;
//    int bearingY = 0;
//    origin = glm::vec2(0, 0);
    
//    for(unsigned int i = 0; i<text.length(); i++){
//        //for each character
//        char c = text[i];
//        //get GlyphData
//        GlyphData gData;
//        //set validation to false
//        gData.valid = false;
//        font->getGlyphDataFromChar(c, gData);
//        //if validation is still false, this char doesn't exist in font. Ignore it
//        //TODO: let user to choose wheter to break the loop and leave as unloaded text or ignore missing chars
//        if(!gData.valid)
//            continue;
//        
//        width += (gData.metrics.width >> 6);
//        int newHeight = (int)(gData.metrics.height >> 6);
//        if(newHeight >= height)
//            height = newHeight;
//        
//        int newBearingY = (int)(gData.metrics.horiBearingY >> 6);
//        if(newBearingY >= bearingY){
//            bearingY = newBearingY;
//        }
//    }
    
//    int bottomY = height - bearingY;
//    origin.x = width/2 * (-1);
//    origin.y = 0 - (height/2 - bottomY);
    
    int w = 0;
    int h = 0;
    int totalHeight = 0;
    int maxWidth = 0;
    int bearingY = 0;
    int maxBotY = 0;
    
    std::vector<int> offsetY;
    std::vector<int> widthList;
    
    //iterate text that is separated by new line
    for(auto it : splittedText){
        //reset width and height
        w = 0;
        h = 0;
        //iterate each line by char
        for(unsigned int i = 0; i < it.length(); i++){
            const char* cStr = it.c_str();
            char c = cStr[i];
            //get GlyphData
            GlyphData gData;
            //set validation to false
            gData.valid = false;
            font->getGlyphDataFromChar(c, gData);
            
            //sum up all char's width
            w += (gData.metrics.horiAdvance >> 6);
            
            int newHeight = (int)(gData.metrics.height >> 6);
            //store highest height among the chars.
            if(newHeight >= h)
                h = newHeight;
            
            int newBearingY = (int)(gData.metrics.horiBearingY >> 6);
            //store highest bearingY among the chars.
            int botY = newHeight - newBearingY;
            if(botY > maxBotY)
                maxBotY = botY;
            
            if(newBearingY >= bearingY)
                bearingY = newBearingY;
            
        }
        //check if this line has max width
        if(w >= maxWidth)
            maxWidth = w;
        
        //sum total hiehgt
        totalHeight += h;
        
        //create origin (center aligned)
        glm::vec2 origin = glm::vec2(0, 0);
        origin.x = w/2 * (-1);
        origin.y = 0;
        originList.push_back(origin);
        
        //save offsets
        offsetY.push_back(bearingY);
//        offsetY.push_back(h - bearingY);
        offsetY.push_back(maxBotY);
        
        widthList.push_back(w);
    }
//    
//    int offset = 0;
//    int index = 0;
    int lineNumber = (int)originList.size();
    int lineSpace = font->getLineSpace();

    totalHeight = ((lineNumber - 1) * lineSpace) + offsetY.at(0) + offsetY.at(offsetY.size() - 1);
    int baseY = totalHeight / 2;
    
    int newY = 0 - offsetY.at(0) + baseY;

//    for(unsigned int i = 0; i<originList.size(); i++){
    int originIndex = 0;
    for (unsigned int i = 0; i < offsetY.size(); i+=2){
        if(align == ALIGN_RIGHT){
            originList.at(originIndex).x = ((-1) * (maxWidth / 2)) + (maxWidth - widthList.at(i));
        }
        else if(align == ALIGN_LEFT){
            originList.at(originIndex).x = maxWidth / 2 * (-1);
        }
        originList.at(originIndex).y = newY;
//        newY -= lineSpace;
        newY -= (offsetY.at(i) + offsetY.at(i + 1));
        originIndex++;
    }
    
//    for(auto it = offsetY.begin(); it != offsetY.end(); it++){
//        offset -= (*it);
//        originList.at(index).y = (offset + baseY);
//        index++;
//        it++;
//        offset -= (*it);
//    }
}

bool Text::hasEmptyText(){
    return text.empty();
}

void Text::render(){
    glUseProgram(progPtr->getObject());
    //render text. need to specify camera again because we are using different shader
//    GLuint cameraUniformLocation = glGetUniformLocation(progPtr->getObject(), "cameraMat");
    glm::mat4 cameraMat = Director::getInstance().getCameraPtr()->getMatrix();
//    glUniformMatrix4fv(cameraUniformLocation, 1, GL_FALSE, &cameraMat[0][0]);
    matrixUniformLocation("cameraMat", cameraMat);
//
//    GLint modelUniformLocation = glGetUniformLocation(progPtr->getObject(), "modelMat");
//    if(modelUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "modelMat");
//    glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, &modelMat[0][0]);
//    
//    GLint rotateUniformLocation = glGetUniformLocation(progPtr->getObject(), "rotateMat");
//    if(rotateUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "rotateMat");
//    glUniformMatrix4fv(rotateUniformLocation, 1, GL_FALSE, &rotateMat[0][0]);
//    
//    GLint translateUniformLocation = glGetUniformLocation(progPtr->getObject(), "translateMat");
//    if(translateUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "translateMat");
//    glUniformMatrix4fv(translateUniformLocation, 1, GL_FALSE, &translateMat[0][0]);
//    
//    GLint scaleUniformLocation = glGetUniformLocation(progPtr->getObject(), "scaleMat");
//    if(scaleUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "scaleMat");
//    glUniformMatrix4fv(scaleUniformLocation, 1, GL_FALSE, &scaleMat[0][0]);
    
//    GLint fontColorUniformLocation = glGetUniformLocation(progPtr->getObject(), "fontColor");
//    if(fontColorUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "fontColor");
//    glUniform3fv(fontColorUniformLocation, 1, &fontColor[0]);
    
//    GLint opacityUniformLocation = glGetUniformLocation(progPtr->getObject(), "opacity");
//    if(opacityUniformLocation == -1)
//        throw std::runtime_error( std::string("Program uniform not found: " ) + "opacity");
//    glUniform1fv(opacityUniformLocation, 1, &opacity);
    
    matrixUniformLocation("modelMat", modelMat);
    matrixUniformLocation("rotateMat", rotateMat);
    matrixUniformLocation("translateMat", translateMat);
    matrixUniformLocation("scaleMat", scaleMat);
    floatUniformLocation("opacity", opacity);
    vec3UniformLocation("fontColor", fontColor);
    
    glBindVertexArray(vao);
    
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
//    glEnableVertexAttribArray(progPtr->attrib("charTransVert"));
//    glEnableVertexAttribArray(2);
    
    glActiveTexture(GL_TEXTURE0);
    
    Font* font = FontManager::getInstance().getFont(fontName);
    unsigned int index = -1;
    int rangeCounter = -1;
    for(auto it : splittedText){
        for(unsigned int i = 0; i<it.length(); i++){
            rangeCounter++;
            index++;
            if(rangeCounter < start)
                continue;
            if(rangeCounter > end)
                break;
            //send translate matrix for each char
//            GLint charTransMatUniformLocation = glGetUniformLocation(progPtr->getObject(), "charTransMat");
//            if(charTransMatUniformLocation == -1)
//                throw std::runtime_error( std::string("Program uniform not found: " ) + "charTransMat");
//            glUniformMatrix4fv(charTransMatUniformLocation, 1, GL_FALSE, &translationData.at(index)[0][0]);
            
            matrixUniformLocation("charTransMat", translationData.at(index));
            
            //get char and check validation.
            const char* cStr = it.c_str();
            char c = cStr[i];
            int cInt = (int)c;
            if(cInt < 32 || cInt > 126){
                cout << "Unsupported text" << endl;
                exit(1);
            }
            
            GlyphData gData;
            gData.valid = false;
            font->getGlyphDataFromChar(c, gData);
            GLuint texObj = gData.texObj;
            glBindTexture(GL_TEXTURE_2D, texObj);
            glDrawRangeElements(
                                GL_TRIANGLES/*Rendering mode. draw 2 triangles for 1 quad*/,
                                //index * 0/*start*/,
                                //index * 0/*end*/,
                                //Not sure what start and end do. Gonna try static number
                                0/*start*/,
                                6/*end*/,
                                6/*Count. Number of elements to be rendered. Single quad contains 6 vertexes.*/,
                                GL_UNSIGNED_SHORT/*indices type*/,
                                VOID_OFFSET(index * 6 * sizeof(GLushort))/*offset of each char(6 vertexes)*/
                                );
        }
    }
    
//    unsigned int textLength = (unsigned int)text.length();
//    const char* textCStr = text.c_str();
//    for(unsigned int i = 0; i<textLength; i++){
//        //for each character
//        char c = textCStr[i];
//        int cInt = (int)c;
////        cout << "rendering = " << cInt << endl;
//        if(cInt < 32 || cInt > 126){
//            cout << "Unsupported text" << endl;
//            exit(1);
//        }
////        get GlyphData
//        GlyphData gData;
//        //set validation to false
//        gData.valid = false;
//        font->getGlyphDataFromChar(c, gData);
//        GLuint texObj = gData.texObj;
//        glBindTexture(GL_TEXTURE_2D, texObj);
//        glDrawRangeElements(GL_TRIANGLES, i*4, i*4+4, 6, GL_UNSIGNED_SHORT, VOID_OFFSET(i * 6 * sizeof(GLushort)));
//    }
    glBindVertexArray(0);
}

void Text::splitByNewLine(){
    splittedText.clear();
    stringstream ss(text); // Turn the string into a stream.
    string tok;
    
    while(getline(ss, tok, '\n')) {
        splittedText.push_back(tok);
    }
}

void Text::setTextAlign(Text::TextAlign mode){
    this->align = mode;
}

void Text::setTextRange(int start, int end){
    if(start < 0)
        start = 0;
    this->start = start;
    
    int strLen = (int)strlen(text.c_str());
    if(end > strLen)
        end = strLen;
    this->end = end;
}