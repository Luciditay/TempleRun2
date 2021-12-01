#version 330 core

in vec3 vViewPosition;
in vec3 vViewNormal;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D uTextureEarth;
uniform sampler2D uTextureClouds;

void main() {
  
  vec4 texTemp1 = texture(uTextureEarth, vTexCoords);
  vec4 texTemp2 = texture(uTextureClouds, vTexCoords);

  fFragColor = texTemp1+texTemp2;
};