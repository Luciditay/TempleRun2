#pragma once
#include <glimac/glm.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include "Cameras.hpp"
#include "Character.hpp"

/// \class MoveMatrix
/// \brief class that move all the matrix (of character, enemy, world, light...) depending on character movements
class MoveMatrix {
    private:
    glm::mat4 m_MVMatrixCharacter; /*!< model view matrix of the character */
    glm::mat4 m_MVMatrixWorld; /*!< model view matrix of the world */
    glm::mat4 m_ViewMatrix; /*!< view matrix */
    glm::mat4 m_MVMatrixLight; /*!< model view matrix of the light */
    glm::mat4 m_MVMatrixEnemy; /*!< model view matrix of the enemy */
    glm::mat4 m_MVMatrixCollectible; /*!< model view matrix of the collectible */

    float m_distanceEnemy; /*!< distance between character and enemy */

    Camera* m_camera; /*!< camera */
    Character* m_char; /*!< character */

    public:
    /// \brief constructor
    /// \param camera : camera 
    /// \param character : character
    MoveMatrix(Camera* camera, Character* character);

    /// \brief compute view matrix (camera following character on y axis)
    void computeViewMatrix();
    /// \brief compute character matrix (translated on y (jump), and scaled (squat))
    void computeMVCharacter();
    /// \brief compute world matrix : moving on x and z axis, and rotating depending on character movements
    void computeMVWorld();
    /// \brief compute light matrix : rotated with world
    void computeMVLight();
    /// \brief compute enemy matrix : behind the character
    void computeMVEnemy();
    /// \brief compute collectible matrix 
    void computeMVCollectible(glm::vec3 position);
    /// \brief compute all the previous matrix
    void computeAllMatrix();

    glm::mat4 getViewMatrix(); /*!< give the view matrix */
    glm::mat4 getCharMVMatrix(); /*!< give the character model view matrix */
    glm::mat4 getWorldMVMatrix(); /*!< give the world model view matrix */
    glm::mat4 getLightMVMatrix(); /*!< give the light model view matrix */
    glm::mat4 getEnemyMVMatrix(); /*!< give the enemy model view matrix */
    glm::mat4 getCollectibleMVMatrix(); /*!< give the collectible model view matrix */
};