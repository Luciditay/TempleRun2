#include <iostream>
#include "glimac/FreeflyCamera.hpp"
# define PI 3.14159265358979323846  

FreeflyCamera::FreeflyCamera() : m_Position(glm::vec3(0.,0.6,-1.)), m_fPhi(PI), m_fTheta(0)
{
    computeDirectionVectors();
}

void FreeflyCamera::computeDirectionVectors() {
    m_FrontVector = glm::vec3(cos(m_fTheta)*sin(m_fPhi), sin(m_fTheta), cos(m_fTheta)*cos(m_fPhi));
    m_LeftVector = glm::vec3(sin(m_fPhi+(PI/2.)), 0., cos(m_fPhi+(PI/2)));
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

void FreeflyCamera::moveLeft(float t) {
    m_Position += t*m_LeftVector;
}

void FreeflyCamera::moveFront(float t) {
    m_Position += t*m_FrontVector;
}


void FreeflyCamera::rotateLeft(float degrees) {
    if (m_fPhi >= M_PI/2. && m_fPhi<= 3*M_PI/2.){
        m_fPhi+=(degrees/360)*2*PI;
    } if (m_fPhi < M_PI/2.) {
        m_fPhi = M_PI/2.+0.000001;
    } if (m_fPhi > 3*M_PI/2.) {
        m_fPhi = 3*M_PI/2.-0.000001;
    }
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees) {
    if (m_fTheta >= -M_PI/2. && m_fTheta <= M_PI/2.){
        m_fTheta+=(degrees/360)*2*PI;
    } if (m_fTheta < -M_PI/2.) {
        m_fTheta = -M_PI/2.+0.000001;
    } if (m_fTheta > M_PI/2.) {
        m_fTheta = M_PI/2.-0.000001;
    }
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const {
    return glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);
}