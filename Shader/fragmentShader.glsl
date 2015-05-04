#version 410

uniform sampler2D tex;

uniform float opacity;

in vec2 fragTexCoord;

out vec4 fragColor;

void main(){
    vec4 textureColor = texture(tex, fragTexCoord);
    vec4 finalColor = vec4(1, 1, 1, opacity/255);
//    vec4 finalColor = vec4(1, 1, 1, 1);
    fragColor = finalColor * textureColor;
}