#version 330

in vec2 texturePos;
in vec3 fragColor;

uniform sampler2D uTexture;

out vec4 vFragColor;

void main(){
    vFragColor = texture(uTexture, texturePos);
    //vFragColor = vec4(fragColor, 1);
}