#version 410

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 uvVert;

uniform mat4 modelMat;
uniform mat4 translateMat;
uniform mat4 rotateMat;
uniform mat4 scaleMat;
uniform mat4 cameraMat;

out vec2 fragTexCoord;

void main(){
    vec4 finalPosition = vec4(vert, 1.0);
    mat4 objectMat = modelMat * translateMat * rotateMat * scaleMat;
    gl_Position = cameraMat * objectMat * finalPosition;
    fragTexCoord = uvVert;
}