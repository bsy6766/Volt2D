//
//  Text.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 5/7/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Text.h"

#define VOID_OFFSET(i) (GLvoid*)(i)

using namespace Volt2D;

Text::Text():
RenderableObject(),
color(Color::NONE),
maxWidth(0),
totalHeight(0),
type(TEXT_TYPE::STATIC)
{
    this->progPtr = Volt2D::Director::getInstance().getProgramPtr("Text");
}

Text::~Text(){
    glDeleteBuffers(1, &vpbo);
}

Text* Text::create(std::string objectName, std::string label, std::string font, TEXT_ALIGN align, Color color, TEXT_TYPE type){
    Text* newLabel = new Text();
    if(newLabel->initText(label, font, align, color, type)){
        newLabel->setName(objectName);
        return newLabel;
    }
    else{
        delete newLabel;
        return nullptr;
    }
}

bool Text::initText(std::string label, std::string font, TEXT_ALIGN align, Color color, TEXT_TYPE type){
    this->label = label;
    this->font = font;
    this->align = align;
    this->color = color;
    this->type = type;
    splitByNewLine();
    
    if(computeVertices()){
        loadVertexData();
    }
    else{
        return false;
    }
    
    return true;
}

bool Text::computeVertices(){
    //clear vertex data
    vertexData.clear();
    uvVertexData.clear();
    indicesData.clear();
    translationData.clear();
    
    //get font.
    Font* ttfFont = FontManager::getInstance().getFont(this->font);
    if(!ttfFont){
        cout << "Failed to find font." << endl;
        return false;
    }
    
    std::vector<glm::vec2> originList;
    //Sprite text with new line character.
    splitByNewLine();
    //iterate through each line and compute originList to compute vertex
    //Origin list is a point where label on each line starts.
    //This is same as how human writes letter on paper.
    computeOrigins(ttfFont, originList);
    
    unsigned short indicesIndex = 0;
    int index = 0;
    //iterate text splitted by new line char (\n)
    for(auto it : splittedLabel){
        //get the origin of the each line
        glm::vec2 origin = originList.at(index);
        index++;
        for(unsigned int i =0; i<it.length(); i++){
            //for each character
            char c = it[i];
            //get GlyphData
            GlyphData* gData = ttfFont->getGlyphDataFromChar(c);
            if(gData == nullptr){
                cout << "Failed to find GlyphData for char \"" << c << "\"." << endl;
                continue;
            }
            //if validation is still false, this char doesn't exist in font. Ignore it
            //TODO: let user to choose wheter to break the loop and leave as unloaded text or ignore missing chars
            if(!gData->valid)
                continue;
            
            //get data from glyph. Assume they don't have floating point for below values.
            int bearingY = (int)(gData->metrics.horiBearingY >> 6);
            int glyphHeight = (int)(gData->metrics.height >> 6);
            int glyphWidth = (int)(gData->metrics.width >> 6);
            
            //compute vertex quad at origin.
            //Left bottom.
            glm::vec2 p1 = glm::vec2((-1) * glyphWidth / 2,
                                     (-1) * (glyphHeight - bearingY)/*botY*/);
            //Top right
            glm::vec2 p2 = glm::vec2(glyphWidth / 2,
                                     bearingY); //top right
            
            //scale down to world size
            p1 /= Volt2D::SCREEN_TO_WORLD_SCALE;
            p2 /= Volt2D::SCREEN_TO_WORLD_SCALE;
            
            //get point where each char has to move (center of quad).
            //y just follows origin's y because that is the guidline for each line.
            glm::vec3 fPos = glm::vec3(origin.x + glyphWidth/2, origin.y, 0);
            //get distance from origin
            glm::vec3 distance = (fPos - glm::vec3(0));
            //scale down.
            distance.x /= Volt2D::SCREEN_TO_WORLD_SCALE;
            distance.y /= Volt2D::SCREEN_TO_WORLD_SCALE;
            //compute translation matrix to desired position
            glm::mat4 transMatToFPos = glm::translate(glm::mat4(), distance);
            //convert to vec3(x,y,z)
            glm::vec3 translateVec3 = glm::vec3(transMatToFPos[3][0],
                                                transMatToFPos[3][1],
                                                transMatToFPos[3][2]);
            //compute translate matrix to fPos from origin
            translationData.push_back(translateVec3);
            translationData.push_back(translateVec3);
            translationData.push_back(translateVec3);
            translationData.push_back(translateVec3);
            
            //compute vertex data
            vertexData.push_back(glm::vec3(p1.x, p1.y, Volt2D::GLOBAL_Z_VALUE)); //Left bottom
            vertexData.push_back(glm::vec3(p1.x, p2.y, Volt2D::GLOBAL_Z_VALUE)); //Left top
            vertexData.push_back(glm::vec3(p2.x, p1.y, Volt2D::GLOBAL_Z_VALUE)); //Right bottom
            vertexData.push_back(glm::vec3(p2.x, p2.y, Volt2D::GLOBAL_Z_VALUE)); //Right top
            
            //compute uv coordinates
            uvVertexData.push_back(glm::vec2(gData->uvTopLeft.x, gData->uvBotRight.y)); //Left bottom
            uvVertexData.push_back(gData->uvTopLeft);                                   //Left top
            uvVertexData.push_back(gData->uvBotRight);                                  //Right bottom
            uvVertexData.push_back(glm::vec2(gData->uvBotRight.x, gData->uvTopLeft.y)); //Right top
            
            //add indices based on char
            indicesData.push_back(indicesIndex * 4);
            indicesData.push_back(indicesIndex * 4 + 1);
            indicesData.push_back(indicesIndex * 4 + 2);
            indicesData.push_back(indicesIndex * 4 + 1);
            indicesData.push_back(indicesIndex * 4 + 2);
            indicesData.push_back(indicesIndex * 4 + 3);
            //increase indicies index
            indicesIndex++;
            
            //advance origin
            origin.x += (gData->metrics.horiAdvance >> 6);
        }
    }
    
    return true;
}
void Text::computeOrigins(Font* font, std::vector<glm::vec2>& originList){
    originList.clear();
    
    int w = 0;
    int h = 0;
    int totalHeight = 0;
    int maxWidth = 0;
    int maxBearingY = 0;
    int maxBotY = 0;
    
    std::vector<int> offsetY;
    std::vector<int> widthList;
    
    //iterate text that is separated by new line
    for(auto it : splittedLabel){
        //reset width and height
        w = 0;
        h = 0;
        //iterate each line by char
        for(unsigned int i = 0; i < it.length(); i++){
            //convert to char array and get char by index i
            const char* cStr = it.c_str();
            char c = cStr[i];
            
            //get GlyphData
            GlyphData* gData = font->getGlyphDataFromChar(c);
            if(gData == nullptr){
                cout << "Failed to find GlyphData for char \"" << c << "\"." << endl;
            }
            
            //sum up all char's width
            w += (gData->metrics.horiAdvance >> 6);
            
            //get height
            int newHeight = (int)(gData->metrics.height >> 6);
            //and store highest height among the chars.
            if(newHeight >= h)
                h = newHeight;
            
            //get bearing y for char
            int newBearingY = (int)(gData->metrics.horiBearingY >> 6);
            //store highest botY (= diff from total glyph's height and bearing y)
            int botY = newHeight - newBearingY;
            
            //and store the max bot y
            if(botY > maxBotY)
                maxBotY = botY;
            
            //and also save max bearing y
            if(newBearingY >= maxBearingY)
                maxBearingY = newBearingY;
            
        }
        //check if this line has max width
        if(w >= maxWidth)
            maxWidth = w;
        
        //sum total hiehgt
        totalHeight += h;
        
        //create origin. origin is the starting point of text quad vertices. y will be updated after this loop
        glm::vec2 origin = glm::vec2(0, 0);
        originList.push_back(origin);
        
        //save offsets
        offsetY.push_back(maxBearingY);
        offsetY.push_back(maxBotY);
        
        widthList.push_back(w);
    }
    
    //get center of height
    int baseY = totalHeight / 2;
    
    int newY = 0 - offsetY.at(0) + baseY;
    
    int originIndex = 0;
    //update origin list.
    //origin list starts from left and advance to right(like human writes)
    for (unsigned int i = 0; i < offsetY.size(); i+=2){
        if(align == TEXT_ALIGN::ALIGN_RIGHT){
            //right align. Add amount of diff between max with and current line's width to most left width position.
            originList.at(originIndex).x = ((-1) * (maxWidth / 2)) + (maxWidth - widthList.at(originIndex));
        }
        else if(align == TEXT_ALIGN::ALIGN_LEFT){
            //left align. Each line starts from left side.
            originList.at(originIndex).x = maxWidth / 2 * (-1);
        }
        else{
            //center align. Each line starts according to their own width.
            originList.at(originIndex).x = widthList.at(originIndex) / -2.0f;
        }
        //set the y position of origin.
        originList.at(originIndex).y = newY;
        //move down the y position.
        //CHECK!! I think offsetY isn't correct.
        newY -= (offsetY.at(i) + offsetY.at(i + 1));
        
        //increment index
        originIndex++;
    }
    
    //store size
    this->maxWidth = maxWidth;
    this->totalHeight = totalHeight;
    
    //store sacled size
    this->Object::scaledWidth = maxWidth / Volt2D::SCREEN_TO_WORLD_SCALE;
    this->Object::scaledHeight = totalHeight / Volt2D::SCREEN_TO_WORLD_SCALE;
}

void Text::loadVertexData(){
    glGenVertexArrays(1, &this->bufferObject.vao);
    glBindVertexArray(this->bufferObject.vao);
    
    GLenum usage;
    if(this->type == TEXT_TYPE::STATIC){
        usage = GL_STATIC_DRAW;
    }
    else if(this->type == TEXT_TYPE::DYNAMIC){
        usage = GL_DYNAMIC_DRAW;
    }
    
    //generate vertex buffer object for quad
    glGenBuffers(1, &this->bufferObject.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], usage);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate texture uv buffer object for quad
    glGenBuffers(1, &this->bufferObject.uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], usage);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate indices buffer
    glGenBuffers(1, &this->bufferObject.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferObject.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], usage);
    
    //allocating blank position buffer
    glGenBuffers(1, &this->vpbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vpbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * translationData.size(), &translationData[0], usage);
    glVertexAttribPointer(progPtr->attrib("posVert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Text::subVertexData(){
    GLenum usage;
    if(this->type == TEXT_TYPE::STATIC){
        usage = GL_STATIC_DRAW;
    }
    else if(this->type == TEXT_TYPE::DYNAMIC){
        usage = GL_DYNAMIC_DRAW;
    }
    
    //bind vertex coordinates buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.vbo);
    //orphan it
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], usage);
    //fill with new vertex coordinates
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * vertexData.size(), &vertexData[0]);
    
    //bind uv coordinates buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.uvbo);
    //orphan it
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], usage);
    //fill with new uv coordinates
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0]);
    
    //bind indices buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferObject.ibo);
    //orphan it
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), NULL, usage);
    //fill with new indicies
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLushort) * indicesData.size(), &indicesData[0]);
    
    //bind translation data buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->vpbo);
    //orphan buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * translationData.size(), NULL, usage);
    //fill buffer with new data
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * translationData.size(), &this->translationData[0]);
}

std::string Text::getLabel(){
    return this->label;
}

bool Text::setLabel(std::string label){
    if(this->type == TEXT_TYPE::STATIC){
        return false;
    }
    else{
        //backup
        std::string prevLabel = this->label;
        std::vector<std::string> prevSplit = this->splittedLabel;
        //update label
        this->label = label;
        
        if(computeVertices()){
            //updated vertex buffer
            subVertexData();
            return true;
        }
        else{
            //rollback
            this->label = prevLabel;
            this->splittedLabel = prevSplit;
            return false;
        }
    }
}

bool Text::setAlign(Volt2D::TEXT_ALIGN align){
    if(this->type == TEXT_TYPE::STATIC){
        return false;
    }
    else{
        //backup
        TEXT_ALIGN prevAlign = this->align;

        this->align = align;
        if(computeVertices()){
            //updated vertex buffer
            subVertexData();
            return true;
        }
        else{
            //rollback
            this->align = prevAlign;
            return false;
        }
    }}

void Text::setColor(Color color){
    this->color = color;
}

void Text::splitByNewLine(){
    this->splittedLabel.clear();
    std::stringstream ss(label); // Turn the string into a stream.
    std::string tok;
    
    while(getline(ss, tok, '\n')) {
        this->splittedLabel.push_back(tok);
    }
}

void Text::render(){
    if(!visible) return;
    if(label.empty()) return;
    
    glUseProgram(progPtr->getObject());
    
    Font* ttfFont = FontManager::getInstance().getFont(font);
    
    ttfFont->bindTextTextureAtlas();
    
    const glm::mat4 cameraMat = Volt2D::Director::getInstance().getProjectiveViewMatrix();
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
    glm::vec3 colorRGB = color.getRGB();
    vec3UniformLocation("fontColor", colorRGB);
    
    glBindVertexArray(this->bufferObject.vao);
    
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
    glEnableVertexAttribArray(progPtr->attrib("posVert"));
    
    //maybe instancing is not right...just use normal draw call...
    glDrawElements(GL_TRIANGLES, (int)this->indicesData.size(), GL_UNSIGNED_SHORT, 0);
    
    glBindVertexArray(0);
    glUseProgram(0);
}