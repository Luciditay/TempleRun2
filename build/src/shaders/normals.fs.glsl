#version 330 core

in vec3 vViewPosition;
in vec3 vViewNormal;
in vec2 vTexCoords;

out vec3 fFragColor;

void main() {
  fFragColor = normalize(vViewNormal);
};