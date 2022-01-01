#include <iostream>
#include "MoveMatrix.hpp"

MoveMatrix::MoveMatrix(Camera *camera, Character *character) : m_camera(camera), m_char(character)
{
}

void MoveMatrix::computeViewMatrix()
{
    m_ViewMatrix = glm::translate(m_camera->getViewMatrix(), glm::vec3(0., -m_char->getPos().y, 0.));
}

void MoveMatrix::computeMVCharacter()
{
    glm::mat4 VChar = glm::translate(glm::mat4(), glm::vec3(0., m_char->getPos().y, 0.) + m_char->getCompenseScale());
    VChar = glm::scale(VChar, glm::vec3(0.1, 0.1, 0.1));
    VChar = glm::scale(VChar, m_char->getScale());
    m_MVMatrixCharacter = m_ViewMatrix * VChar;
}

void MoveMatrix::computeMVWorld()
{
    glm::mat4 VWorld = glm::rotate(glm::mat4(), glm::radians(float(-m_char->getAngle())), glm::vec3(0., 1., 0.));
    VWorld = glm::translate(VWorld, glm::vec3(-m_char->getPos().x, 0, -m_char->getPos().z));
    VWorld = glm::translate(VWorld, glm::vec3(-1, 0.75, 0));
    m_MVMatrixWorld = m_ViewMatrix * VWorld;
}

void MoveMatrix::computeMVLight()
{
    glm::mat4 VLight = glm::rotate(glm::mat4(), glm::radians(float(-m_char->getAngle())), glm::vec3(0., 1., 0.));
    m_MVMatrixLight = m_ViewMatrix * VLight;
}

void MoveMatrix::computeMVEnemy()
{
    glm::mat4 VEnemy = glm::translate(glm::mat4(), glm::vec3(0., 1., m_char->getDistanceEnemy()));
    VEnemy= glm::scale(VEnemy, glm::vec3(0.1, 0.1, 0.1));
    m_MVMatrixEnemy = m_ViewMatrix * VEnemy;
}

void MoveMatrix::computeMVCollectible(glm::vec3 position)
{
    glm::mat4 VCollectible = glm::rotate(glm::mat4(), glm::radians(float(-m_char->getAngle())), glm::vec3(0., 1., 0.));
    VCollectible = glm::translate(VCollectible, (glm::vec3(-m_char->getPos().x, 0, -m_char->getPos().z)) + position);
    m_MVMatrixCollectible = m_ViewMatrix * VCollectible;
}

void MoveMatrix::computeAllMatrix()
{
    computeViewMatrix();
    computeMVCharacter();
    computeMVWorld();
    computeMVLight();
    computeMVEnemy();
}

glm::mat4 MoveMatrix::getViewMatrix()
{
    return m_ViewMatrix;
}

glm::mat4 MoveMatrix::getCharMVMatrix()
{
    return m_MVMatrixCharacter;
}

glm::mat4 MoveMatrix::getWorldMVMatrix()
{
    return m_MVMatrixWorld;
}

glm::mat4 MoveMatrix::getLightMVMatrix()
{
    return m_MVMatrixLight;
}

glm::mat4 MoveMatrix::getEnemyMVMatrix()
{
    return m_MVMatrixEnemy;
}

glm::mat4 MoveMatrix::getCollectibleMVMatrix()
{
    return m_MVMatrixCollectible;
}