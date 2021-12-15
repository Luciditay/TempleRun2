#version 330

layout(location=0) in vec3 aVertexPos;
layout(location=2) in vec3 aTexturePos;

uniform mat4 uMVMatrix;
uniform mat4 uMVPMatrix;

out vec3 texturePos;
out vec3 fragColor;

void main(){
    vec4 vertexPosition = vec4(aVertexPos, 1);

    texturePos=aTexturePos;
    fragColor = aTexturePos;
    gl_Position =  uMVPMatrix * vertexPosition;
}

