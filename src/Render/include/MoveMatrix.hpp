#pragma once
#include <glimac/glm.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include "Cameras.hpp"
#include "Character.hpp"

class MoveMatrix {
    private:
    glm::mat4 m_MVMatrixCharacter;
    glm::mat4 m_MVMatrixWorld;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_MVMatrixLight;
    glm::mat4 m_MVMatrixEnemy;

    float m_distanceEnemy;

    Camera* m_camera;
    Character* m_char;

    public:
    MoveMatrix(Camera* camera, Character* character);

    void computeViewMatrix();
    void computeMVCharacter();
    void computeMVWorld();
    void computeMVLight();
    void computeMVEnemy();
    void computeAllMatrix();
    void setDistanceEnemy(const float distance);

    glm::mat4 getViewMatrix();
    glm::mat4 getCharMVMatrix();
    glm::mat4 getWorldMVMatrix();
    glm::mat4 getLightMVMatrix();
    glm::mat4 getEnemyMVMatrix();
};