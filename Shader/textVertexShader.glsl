#version 410

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 uvVert;
layout(location = 2) in vec3 posVert;

uniform mat4 parentMat;
uniform mat4 modelMat;
uniform mat4 translateMat;
uniform mat4 rotateMat;
uniform mat4 scaleMat;
uniform mat4 cameraMat;

out vec2 fragTexCoord;

void main(){
    vec4 finalPosition = vec4(vert, 1.0);
    
    //build each character's translative matrix
    mat4 charTransMat;
    charTransMat[0][0] = 1.0f;
    charTransMat[1][1] = 1.0f;
    charTransMat[2][2] = 1.0f;
    charTransMat[3][0] = posVert[0];
    charTransMat[3][1] = posVert[1];
    charTransMat[3][2] = posVert[2];
    charTransMat[3][3] = 1.0f;
    
    mat4 objectMat = parentMat * translateMat * rotateMat * scaleMat * charTransMat * modelMat;
    gl_Position = cameraMat * objectMat * finalPosition;
    fragTexCoord = uvVert;
}