#version 330 core

in vec3 vViewPosition;
in vec3 vViewNormal;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs; //vs=view space => on doit recevoir direction*viewmatrix
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
    vec3 wi = normalize(uLightPos_vs-vViewPosition); //dir incidente
    float d = distance(uLightPos_vs,vViewPosition);
    vec3 Li = uLightIntensity/(d*d);
    vec3 N = normalize(vViewNormal);
    vec3 Kd = uKd; //couleur ref diffuse
    vec3 Ks = uKs; //couleur ref glossy
    float shininess = uShininess;
    vec3 wo = normalize(-vViewPosition); //vect. qui pointe vers la caméra (or cam = origine du repère)
    vec3 halfVector = normalize((wo+wi)/2.);

    return Li*(Kd*dot(wi,N)+Ks*(pow(dot(halfVector,N), shininess)));

}

void main() {
  fFragColor = vec4(blinnPhong(),1);

};