#version 330

in vec2 texturePos;
in vec3 fragColor;

uniform sampler2D uTexture;

out vec4 vFragColor;

void main(){
    //vFragColor = vec4(texture(uCaseTexture, TexturePos).xyz, 1);
    vFragColor = vec4(fragColor, 1);
}