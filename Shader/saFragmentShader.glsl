#version 410

uniform sampler2DArray texArray;

uniform float opacity;
uniform int layer;

in vec2 fragTexCoord;

out vec4 fragColor;

void main(){
    vec4 finalColor = vec4(1, 1, 1, opacity/255);
    vec4 textureColor = texture(texArray, vec3(fragTexCoord.x, fragTexCoord.y, layer));
    fragColor = finalColor * textureColor;
}