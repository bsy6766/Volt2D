//
//  Text.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Text.h"

#define VOID_OFFSET(i) (GLvoid*)(i)

using namespace Volt2D;

Text::Text():
RenderableObject(),
align(ALIGN_RIGHT),
start(-1),
end(-1),
width(0),
height(0)
{
    this->progPtr = Volt2D::Director::getInstance().getProgramPtr("Text");
    Color textColor = Color::WHITE;
    fontColor = textColor.getRGB();
}

Text::~Text(){
    translationData.clear();
}

Text* Text::createText(std::string objectName, std::string label, std::string fontName){
    cout << "Creating new Text object" << endl;
    
    Text* newText = new Text();
    newText->setName(objectName);
    newText->initText(label, fontName);
    
    return newText;
}

void Text::initText(std::string label, std::string fontName){
    this->fontName = fontName;
    text = label;
    start = 0;
    end = (int)strlen(label.c_str()) - 1;
    computeVertexData();
    loadVertexData();
    
    this->boundingBox = new BoundingBox(-width/2, -height/2, width/2, height/2);
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

void Text::setColor(Color color){
    glm::vec3 textColor = color.getRGB();
    
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
    indicesData.clear();
    
    //get font.
    Font* font = FontManager::getInstance().getFont(fontName);
    if(!font){
        cout << "Failed to find font." << endl;
        return;
    }
    
    std::vector<glm::vec2> originList;
    //Sprite text with new line character.
    splitByNewLine();
    //iterate through each line and compute originList to compute vertex
    computeOrigins(font, originList);
    
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
            GlyphData* gData = font->getGlyphDataFromChar(c);
            if(gData == nullptr){
                cout << "Failed to find GlyphData for char \"" << c << "\"." << endl;
                continue;
            }
            //if validation is still false, this char doesn't exist in font. Ignore it
            //TODO: let user to choose wheter to break the loop and leave as unloaded text or ignore missing chars
            if(!gData->valid)
                continue;
            
            //get data from glyph
            int bearingY = (int)(gData->metrics.horiBearingY >> 6);
            int glyphHeight = (int)(gData->metrics.height >> 6);
            int glyphWidth = (int)(gData->metrics.width >> 6);
            
            //compute vertex quad at origin.
            glm::vec2 p1 = glm::vec2((-1) * glyphWidth / 2, (-1) * (glyphHeight - bearingY)); //left bottom
            glm::vec2 p2 = glm::vec2(glyphWidth / 2, bearingY);
            
            //scale down to world size
            p1 /= Volt2D::SCREEN_TO_WORLD_SCALE;
            p2 /= Volt2D::SCREEN_TO_WORLD_SCALE;

            //get point where each char has to move
            glm::vec3 fPos = glm::vec3(origin.x + glyphWidth/2, origin.y, 0);
            glm::vec3 distance = (fPos - this->position);
            distance.x /= Volt2D::SCREEN_TO_WORLD_SCALE;
            distance.y /= Volt2D::SCREEN_TO_WORLD_SCALE;
            glm::mat4 transMatToFPos = glm::translate(glm::mat4(), distance);
            //compute translate matrix to fPos from origin
            translationData.push_back(transMatToFPos);

            //compute vertex data
            vertexData.push_back(glm::vec3(p1.x, p1.y, 0)); //Left bottom
            vertexData.push_back(glm::vec3(p1.x, p2.y, 0)); //Left top
            vertexData.push_back(glm::vec3(p2.x, p1.y, 0)); //Right bottom
            vertexData.push_back(glm::vec3(p2.x, p2.y, 0)); //Right top
            
            //compute uv coordinates
            uvVertexData.push_back(glm::vec2(gData->uvTopLeft.x, gData->uvBotRight.y));
            uvVertexData.push_back(gData->uvTopLeft);
            uvVertexData.push_back(gData->uvBotRight);
            uvVertexData.push_back(glm::vec2(gData->uvBotRight.x, gData->uvTopLeft.y));
            
            //add indices based on char
            indicesData.push_back(indicesIndex * 4);
            indicesData.push_back(indicesIndex * 4 + 1);
            indicesData.push_back(indicesIndex * 4 + 2);
            indicesData.push_back(indicesIndex * 4 + 1);
            indicesData.push_back(indicesIndex * 4 + 2);
            indicesData.push_back(indicesIndex * 4 + 3);
            
            //advance origin
            origin.x += (gData->metrics.horiAdvance >> 6);
            
            indicesIndex++;
        }
    }
}

void Text::loadVertexData(){
    glGenVertexArrays(1, &this->bufferObject.vao);
    glBindVertexArray(this->bufferObject.vao);
    
    //generate vertex buffer object for quad
    glGenBuffers(1, &this->bufferObject.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate texture uv buffer object for quad
    glGenBuffers(1, &this->bufferObject.uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate indices buffer
    glGenBuffers(1, &this->bufferObject.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferObject.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
}

void Text::computeOrigins(Font* font, std::vector<glm::vec2>& originList){
    originList.clear();
    
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
            GlyphData* gData = font->getGlyphDataFromChar(c);
            if(gData == nullptr){
                cout << "Failed to find GlyphData for char \"" << c << "\"." << endl;
            }
            
            //sum up all char's width
            w += (gData->metrics.horiAdvance >> 6);
            
            int newHeight = (int)(gData->metrics.height >> 6);
            //store highest height among the chars.
            if(newHeight >= h)
                h = newHeight;
            
            int newBearingY = (int)(gData->metrics.horiBearingY >> 6);
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
    
    this->width = maxWidth;
    this->height = totalHeight;
    this->RenderableObject::width = maxWidth / Volt2D::SCREEN_TO_WORLD_SCALE;
    this->RenderableObject::height = totalHeight / Volt2D::SCREEN_TO_WORLD_SCALE;
}

bool Text::hasEmptyText(){
    return text.empty();
}

void Text::render(){
    if(!visible) return;

    glUseProgram(progPtr->getObject());
    
    Font* font = FontManager::getInstance().getFont(fontName);
    
    font->bindTextTextureAtlas();
    
    glm::mat4 cameraMat = Volt2D::Director::getInstance().getCameraPtr()->getMatrix();
    matrixUniformLocation("cameraMat", cameraMat);
    glm::mat4 parentMat = glm::mat4();
    if(this->parent)
        parentMat = this->parent->getTransformMat();
    
    matrixUniformLocation("parentMat", parentMat);
    matrixUniformLocation("modelMat", modelMat);
    matrixUniformLocation("rotateMat", rotateMat);
    matrixUniformLocation("translateMat", translateMat);
    matrixUniformLocation("scaleMat", scaleMat);
    floatUniformLocation("opacity", opacity);
    vec3UniformLocation("fontColor", fontColor);
    
    glBindVertexArray(this->bufferObject.vao);
    
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
    
//    glActiveTexture(GL_TEXTURE0);
    
//    //한글 확인
//    std::wstring wStr(L"한글 출력 입니다요 walla!");
//    const wchar_t* wCharStr = wStr.c_str();
//
//    for(int i = 0; i < wcslen(wCharStr); i++){
//        cout << "char = " << wCharStr[i] << endl;
//        if(wCharStr[i] < 0xAC00 || wCharStr[i] > 0xD7A3){
//            if(wCharStr[i] == 0x20){
//                cout << "space!"<< endl;
//            }
//            else{
//                cout << "not korean!" << endl;
//            }
//        }
//        else{
//            cout << "korean!" << endl;
//            
//        }
//    }
    
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
            
            matrixUniformLocation("charTransMat", translationData.at(index));
            
            //get char and check validation.
            const char* cStr = it.c_str();
            char c = cStr[i];
            int cInt = (int)c;
            if(cInt < 32 || cInt > 126){
                cout << "Unsupported text" << endl;
//                exit(1);
                continue;
            }
            
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

    glBindVertexArray(0);
    glUseProgram(0);
}

void Text::splitByNewLine(){
    splittedText.clear();
    std::stringstream ss(text); // Turn the string into a stream.
    std::string tok;
    
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