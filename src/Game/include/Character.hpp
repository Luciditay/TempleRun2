#pragma once
#include <glimac/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Model.hpp"
#include <glimac/SDLWindowManager.hpp>

/// \class Character
class Character
{
private:
    // Position and movements
    glm::vec3 m_posChar;       /*!< position of the character */
    glm::vec3 m_upChar;        /*!< vector pointing the sky */
    glm::vec3 m_frontChar;     /*!< vector pointing in the front direction */
    glm::vec3 m_scaleChar;     /*!< scale to be applied to the character */
    glm::vec3 m_compenseScale; /*!< translation needed to maintain the character on the floor even with the scale */

    //  Model m_model;

    float m_speed;         /*!< character speed */
    float m_distanceEnemy; /*!< distance character-enemy */
    float m_enemySpeed;    /*!< enemy speed */

    // Jump
    bool m_jumping;    /*!< true if the character is jumping */
    float m_jumpIndex; /*!< abscissa of the height of the character in the parabola representing the jump */
    // Squat
    bool m_squating;    /*!< true if the character is squating */
    float m_squatIndex; /*!< abscissa of the scale of the character in the parabola representing the squat */
    // Turn
    bool m_turn;          /*!< true if the character can turn with q and d*/
    bool m_turningLeft;   /*!< true if the character is turning left */
    bool m_turningRight;  /*!< true if the character is turning right */
    int m_angle;          /*!< angle of character rotation */
    int m_variationAngle; /*!< variation of the angle during the rotation */
    // Run
    bool m_lateralStepRight; /*!< true if the character is being translated to the right */
    bool m_lateralStepLeft;  /*!< true if the character is being translated to the left */
    // Fall
    bool m_fall;        /*!< true if the character is falling */
    int m_fallDistance; /*!< distance (y axis) travelled when falling */

    // State
    bool m_dead; /*!< true if the character is dead (RIP) */

public:
    /// \brief constructor
    Character(const glimac::FilePath &applicationPath);
    /// \brief change the action booleans according to the player inputs
    /// \param e : SDL_Event

    void draw();

    void computeMVCharacter();

    void computeViewMatrix();

    void handleSDLEvent(const SDL_Event &e);
    /// \brief react to action booleans changes, by modifying position value etc.
    void reactToInputs();
    /// \brief give the angle
    int getAngle();
    /// \brief give the scale
    glm::vec3 getScale();
    /// \brief give the translation keep character on the floor
    glm::vec3 getCompenseScale();
    /// \brief give character position
    glm::vec3 getPos();
    /// \brief give the distance enemy-character
    float getDistanceEnemy();
    /// \brief increase character speed and decrease the enemy speed
    void increaseSpeed();
    /// \brief true if the character is dead
    bool isDead();
    /// \brief true if the character is jumping
    bool isJumping();
    /// \brief reset character parameters (resurrection)
    void reset();
};