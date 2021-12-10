#pragma once
#include <glimac/glm.hpp>

/// \class FreeflyCamera
/// \brief camera looking at the world from the character eyes
class FreeflyCamera {
    private : 
    glm::vec3 m_Position; /*!< camera position */
    float m_fPhi; /*!< horizontal angle */
    float m_fTheta; /*!< vertical angle */

    glm::vec3 m_FrontVector; /*!< vector pointing to the front */
    glm::vec3 m_LeftVector; /*!< vector pointing to the left */
    glm::vec3 m_UpVector; /*!< vector pointing to the sky */

    /// \brief compute vectors
    void computeDirectionVectors();

    public:
    /// \brief constructor
    FreeflyCamera();
    /// \brief move camera to left
    /// \param t : distance
    void moveLeft(float t);
    /// \brief move camera to front
    /// \param t : distance
    void moveFront(float t);
    /// \brief rotate camera to left
    /// \param degrees : angle
    void rotateLeft(float degrees);
    /// \brief rotate camera to top
    /// \param degrees : angle
    void rotateUp(float degrees);
    /// \brief give the view matrix
    glm::mat4 getViewMatrix() const;

    
};



