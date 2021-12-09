#include <iostream>
#include "MoveMatrix.hpp"

MoveMatrix::MoveMatrix(Camera* camera, Character* character) : 
    m_camera(camera), m_char(character) {
}

void MoveMatrix::computeViewMatrix() {
    m_ViewMatrix = glm::translate(m_camera->getViewMatrix(), glm::vec3(0.,-m_char->getPos().y,0.));
}

void MoveMatrix::computeMVCharacter() {
    glm::mat4 VChar = glm::translate(glm::mat4(), glm::vec3(0.,m_char->getPos().y,0.)+m_char->getCompenseScale());
    VChar = glm::scale(VChar, m_char->getScale());
    m_MVMatrixCharacter = m_ViewMatrix * VChar;
}

void MoveMatrix::computeMVWorld() {
    glm::mat4 VWorld =  glm::rotate(glm::mat4(), glm::radians(float(-m_char->getAngle())), glm::vec3(0.,1.,0.));
    VWorld = glm::translate(VWorld, glm::vec3(-m_char->getPos().x, 0, -m_char->getPos().z));
    VWorld = glm::scale(VWorld, glm::vec3(250.,250.,250.));
    m_MVMatrixWorld = m_ViewMatrix * VWorld;
}

void MoveMatrix::computeMVLight() {
    glm::mat4 VLight = glm::rotate(glm::mat4(), glm::radians(float(-m_char->getAngle())), glm::vec3(0.,1.,0.));
    m_MVMatrixLight = m_ViewMatrix * VLight;
}

void MoveMatrix::setDistanceEnemy(const float distance) {
    m_distanceEnemy = distance;
}

void MoveMatrix::computeMVEnemy() {
    m_MVMatrixEnemy = glm::translate(m_ViewMatrix, glm::vec3(0.,1.,m_char->getDistanceEnemy()));
}

void MoveMatrix::computeAllMatrix() {
    computeViewMatrix();
    computeMVCharacter();
    computeMVWorld();
    computeMVLight();
    computeMVEnemy();
}

glm::mat4 MoveMatrix::getViewMatrix() {
    return m_ViewMatrix;
}

glm::mat4 MoveMatrix::getCharMVMatrix() {
    return m_MVMatrixCharacter;
}

glm::mat4 MoveMatrix::getWorldMVMatrix(){
    return m_MVMatrixWorld;
}

glm::mat4 MoveMatrix::getLightMVMatrix(){
    return m_MVMatrixLight;
}

glm::mat4 MoveMatrix::getEnemyMVMatrix(){
    return m_MVMatrixEnemy;
}