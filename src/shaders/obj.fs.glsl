#version 330 core

in vec3 vViewPosition;
in vec3 vViewNormal;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

//uniform vec3 uLightDir_vs; //vs=view space => on doit recevoir direction*viewmatrix
uniform vec3 uLightPos_vs; //vs=view space => on doit recevoir direction*viewmatrix
//uniform vec3 uLightIntensity;
uniform vec3 uLightIntensityPos;

uniform sampler2D texture_diffuse1;

uniform vec3 uLightVecDirectional0; 
uniform vec3 uLightIntensityDirectional0; 
uniform vec3 uLightVecDirectional1; 
uniform vec3 uLightIntensityDirectional1; 


vec3 blinnPhongDir(vec3 direction, vec3 intensity) {
  if (dot(direction, vViewNormal)<0) { //On essaie de ne pas éclairer la face cachée de l'objet. 
    return vec3(0.,0.,0.);
  } else {
    vec3 wi = normalize(direction); //dir incidente
    vec3 Li = intensity;
    vec3 N = normalize(vViewNormal);
    vec3 Kd = uKd; //couleur ref diffuse
    vec3 Ks = uKs; //couleur ref glossy
    float shininess = uShininess;
    vec3 wo = normalize(-vViewPosition); //vect. qui pointe vers la caméra (or cam = origine du repère)
    vec3 halfVector = normalize((wo+wi)/2.);

    return Li*(Kd*dot(wi,N)+Ks*(pow(dot(halfVector,N), shininess)));
  }

}

vec3 blinnPhongPos() {
  if (dot((uLightPos_vs-vViewPosition), vViewNormal)<0) { //On essaie de ne pas éclairer la face cachée de l'objet. 
    return vec3(0.,0.,0.);
  } else {
    vec3 wi = normalize(uLightPos_vs-vViewPosition); //dir incidente
    float d = distance(uLightPos_vs,vViewPosition);
    vec3 Li = uLightIntensityPos/(d*d);
    vec3 N = normalize(vViewNormal);
    vec3 Kd = uKd; //couleur ref diffuse
    vec3 Ks = uKs; //couleur ref glossy
    float shininess = uShininess;
    vec3 wo = normalize(-vViewPosition); //vect. qui pointe vers la caméra (or cam = origine du repère)
    vec3 halfVector = normalize((wo+wi)/2.);

    return Li*(Kd*dot(wi,N)+Ks*(pow(dot(halfVector,N), shininess)));
  }
}

void main() {
  fFragColor = vec4(blinnPhongDir(uLightVecDirectional1, uLightIntensityDirectional1),1.);
  fFragColor += vec4(blinnPhongDir(uLightVecDirectional0, uLightIntensityDirectional0),1.);
  fFragColor += vec4(blinnPhongPos(),1.);
  fFragColor *= texture(texture_diffuse1, vTexCoords);
};