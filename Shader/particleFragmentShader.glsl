#version 410

uniform sampler2D tex;

//uniform float opacity;

in vec2 fragTexCoord;
in vec4 pColor;

out vec4 fragColor;

void main(){
    vec4 textureColor = texture(tex, fragTexCoord);
    vec4 finalColor = pColor;
    finalColor.r /= 255.0f;
    finalColor.g /= 255.0f;
    finalColor.b /= 255.0f;
    finalColor.a /= 255.0f;
    fragColor = finalColor * textureColor;
}