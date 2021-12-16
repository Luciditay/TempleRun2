#version 330

layout(location=0) in vec3 aVertexPos;
layout(location=1) in vec3 aColorVertex;
layout(location=2) in vec2 aTexturePos;

uniform mat4 uMVMatrix;
uniform mat4 uMVPMatrix;

out vec2 texturePos;
out vec3 fragColor;


void main(){
    vec4 vertexPosition = vec4(aVertexPos, 1);

    fragColor = aColorVertex;
    texturePos = aTexturePos;
    gl_Position =  uMVPMatrix * vertexPosition;
}

