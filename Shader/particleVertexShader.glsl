#version 410

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 uvVert;
layout(location = 2) in vec3 posVert;
layout(location = 3) in vec3 spawnPosVert;
layout(location = 4) in vec4 particleColor;
/**
 *  x = [0][0]
 *  y = [0][1]
 *  z = [1][0]
 *  w = [1][1]
 */
layout(location = 5) in vec4 particleTransform;

uniform mat4 parentMat;
uniform mat4 modelMat;
uniform mat4 translateMat;
uniform mat4 rotateMat;
uniform mat4 scaleMat;
uniform mat4 cameraMat;

out vec2 fragTexCoord;
out vec4 pColor;

void main(){
    mat4 particleScaleMat;
    //scale & rotation matrix
    particleScaleMat[0][0] = particleTransform[0];
    particleScaleMat[0][1] = particleTransform[1];
    particleScaleMat[1][0] = particleTransform[2];
    particleScaleMat[1][1] = particleTransform[3];
    particleScaleMat[2][2] = 1.0f;
    particleScaleMat[3][3] = 1.0f;
    
    vec4 finalPosition;
    //conver to vec4
    vec4 vert4 = vec4(vert, 1.0f);
    vec4 posVert4 = vec4(posVert, 1.0f);
    vec4 spawnPosVert4 = vec4(spawnPosVert, 1.0f);
    //first, rotate and scale particle itself on origin
    vert4 = particleScaleMat * vert4;
    //then, move to particle's position (from spwan, but adding up early on origin)
    vert4 += posVert4;
    vert4.w = 1.0f;
    //then, apply particle system's scale and rotation mat
    vert4 = rotateMat * scaleMat * vert4;
    //then, translate by spawn distance from origin
    vert4 += spawnPosVert4;
    vert4.w = 1.0f;
    //set to final position
    finalPosition = vert4;
    //apply parent and translate mat and set gl position
    gl_Position = cameraMat * parentMat * finalPosition * translateMat * modelMat;
    fragTexCoord = uvVert;
    pColor = particleColor;
}