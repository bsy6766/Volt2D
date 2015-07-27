#version 410

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 uvVert;
layout(location = 2) in vec3 posVert;
layout(location = 3) in vec4 particleColor;
/**
 *  x = [0][0]
 *  y = [0][1]
 *  z = [1][0]
 *  w = [1][1]
 */
layout(location = 4) in vec4 particleTransform;

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
    vec4 vec4vert = vec4(vert, 1.0f);
    vec4vert = particleScaleMat * vec4vert; //matrix must come first than vector
    vec4vert += vec4(posVert, 0.0f);    //w must be 1 after addition
    finalPosition = vec4vert;
    //object's mat.
    //Transformation order.
    //From parent -> own model matrix -> own transformation
    mat4 objectMat = parentMat * translateMat * rotateMat * scaleMat * modelMat;
    gl_Position = cameraMat * objectMat * finalPosition;
    fragTexCoord = uvVert;
    pColor = particleColor;
}