#version 410

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 uvVert;
layout(location = 2) in vec3 posVert;

uniform mat4 modelMat;
uniform mat4 translateMat;
uniform mat4 rotateMat;
uniform mat4 scaleMat;
uniform mat4 cameraMat;
uniform bool particle;

out vec2 fragTexCoord;

void main(){
    vec4 finalPosition;
    if(particle){
        //vec3 movedPos = posVert.xyz;
        vec3 addPos = vert + posVert;
        finalPosition = vec4(addPos, 1.0f);
    }
    else{
        finalPosition = vec4(vert, 1.0f);
    }
    mat4 objectMat = modelMat * translateMat * rotateMat * scaleMat;
//    mat4 objectMat = modelMat * rotateMat * translateMat * scaleMat;
    gl_Position = cameraMat * objectMat * finalPosition;
    fragTexCoord = uvVert;
}