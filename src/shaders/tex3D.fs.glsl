#version 330 core

in vec3 vViewPosition;
in vec3 vViewNormal;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D uTextureMoon;

void main() {
  fFragColor = texture(uTextureMoon, vTexCoords);
};