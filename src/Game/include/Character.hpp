#pragma once
#include <glimac/glm.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include <glimac/SDLWindowManager.hpp>

class Character {
    private:
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
    Character();
    void handleSDLEvent(const SDL_Event& e); 
    void reactToInputs();
    int getAngle();
    glm::vec3 getScale();
    glm::vec3 getCompenseScale();
    glm::vec3 getPos();
};