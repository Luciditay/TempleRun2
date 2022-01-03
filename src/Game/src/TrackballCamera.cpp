#include <iostream>
#include "TrackballCamera.hpp"

TrackballCamera::TrackballCamera(const float distance, const float angleX, const float angleY) :
m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY),
m_fDistanceInitial(distance), m_fAngleXInitial(angleX), m_fAngleYInitial(angleY)
{
}

void TrackballCamera::moveFront(float delta) {
    m_fDistance+=delta;
}

void TrackballCamera::rotateLeft(float degrees) {
    m_fAngleY+=degrees;
}

void TrackballCamera::rotateUp(float degrees) {
    if (m_fAngleX >= 0. && m_fAngleX <= M_PI/2){
        m_fAngleX+=degrees;
    } if (m_fAngleX < 0) {
        m_fAngleX = 0.+0.000001;
    } if (m_fAngleX > M_PI/2) {
        m_fAngleX = M_PI/2-0.000001;
    }
}

glm::mat4 TrackballCamera::getViewMatrix() const {
    glm::mat4 matrice = glm::mat4(glm::vec4(1,0,0,0), glm::vec4(0,1,0,0), 
                        glm::vec4(0,0,1,0), glm::vec4(0,0,0,1));
    matrice = glm::translate(matrice, glm::vec3(0,0,m_fDistance));
    matrice = glm::rotate(matrice, m_fAngleX, glm::vec3(1,0,0));
    matrice = glm::rotate(matrice, m_fAngleY, glm::vec3(0,1,0));

    return matrice;
}

void TrackballCamera::resetCamera() {
    m_fDistance = m_fDistanceInitial;
    m_fAngleY = m_fAngleYInitial;
    m_fAngleX = m_fAngleXInitial;
}