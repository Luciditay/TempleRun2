#pragma once
#include <glimac/glm.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include "Cameras.hpp"

class MoveMatrix {
    private:
    glm::mat4 m_MVMatrixCharacter;
    glm::mat4 m_MVMatrixWorld;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_MVMatrixLight;
    glm::mat4 m_MVMatrixEnemy;

    float m_distanceEnemy;

    Camera* m_camera;

    glm::vec3 m_posChar;
    glm::vec3 m_upChar;
    glm::vec3 m_frontChar;
    glm::vec3 m_scaleChar;
    glm::vec3 m_compenseScale;

    //Jump
    bool m_jumping;
    float m_jumpIndex;

    //Squat
    bool m_squating;
    float m_squatIndex;
    
    //Turn
    bool m_turn;
    bool m_turningLeft;
    bool m_turningRight;
    int m_angle;
    int m_variationAngle;

    //Run
    bool m_lateralStepRight;
    bool m_lateralStepLeft;

    public:
    MoveMatrix(Camera* camera);
    void handleSDLEvent(const SDL_Event& e); 
    void reactToInputs();

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