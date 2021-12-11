#version 330

in vec2 texturePos;

uniform sampler2D uTextureCase;

out vec4 vFragColor;

void main(){
    vFragColor = vec4(texture(uCaseTexture, TexturePos).xyz, 1);
}