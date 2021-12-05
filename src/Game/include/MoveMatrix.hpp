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

    int m_currentTime;
    int m_previousTime;

    Camera* m_camera;

    //Jump
    glm::vec3 m_moveChar;
    bool m_jumping;
    float m_jumpIndex;

    //Squat
    glm::vec3 m_scaleChar;
    glm::vec3 m_moveCharwithoutCam;
    bool m_squating;
    float m_squatIndex;
    
    //Turn
    bool m_turn;
    bool m_turningLeft;
    bool m_turningRight;
    int m_angle;
    int m_variationAngle;

    //Run
    glm::vec3 m_moveWorld;
    bool m_lateralStepRight;
    bool m_lateralStepLeft;
    glm::vec3 m_stepRight;
    glm::vec3 m_up;
    glm::vec3 m_front;

    public:
    MoveMatrix(Camera* camera);
    void handleSDLEvent(const SDL_Event& e); 
    void reactToInputs();

    void computeViewMatrix();
    void computeMVCharacter();
    void computeMVWorld();
    void computeMVLight();
    void computeAllMatrix();
    

    glm::mat4 getViewMatrix();
    glm::mat4 getCharMVMatrix();
    glm::mat4 getWorldMVMatrix();
    glm::mat4 getLightMVMatrix();
};