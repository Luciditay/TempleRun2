#version 330

layout(location=0) in vec3 aVertexPos;
layout(location=2) in vec2 aTexturePos;

uniform mat4 uMVMatrix;

out vec2 texturePos;

void main(){
    texturePos=aVertexPos;
    gl_position = vec4(aVertexPos, 1); 
}