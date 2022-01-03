#pragma once
#include <glimac/glm.hpp>


/// \class TrackballCamera
/// \brief camera turning around the character
class TrackballCamera {
    private : 
    float m_fDistance; /*!< camera distance */
    float m_fAngleX; /*!< camera vertical angle */
    float m_fAngleY; /*!<  camera horizontal angle */

    float m_fDistanceInitial; /*!< camera distance at the beginning (needed to reset the camera parameters) */
    float m_fAngleXInitial; /*!< camera vertical angle at the beginning (needed to reset the camera parameters)  */
    float m_fAngleYInitial; /*!< camera horizontal angle at the beginning (needed to reset the camera parameters) */

    public:
    /// \brief constructor
    /// \param distance : set the initial distance
    /// \param angleX : set the initial vertical angle
    /// \param angleY : set the initial horizontal angle
    TrackballCamera(const float distance = 5., const float angleX = 0., const float angleY = 0.);

    /// \brief make the camera move forward
    /// \param delta : distance the camera travels
    void moveFront(float delta); 
    /// \brief make the camera rotate left
    /// \param degrees : the angle the camera rotates
    void rotateLeft(float degrees);
    /// \brief make the camera rotate up
     /// \param degrees : the angle the camera rotates
    void rotateUp(float degrees);
    /// \brief reset the camera parameters 
    void resetCamera();

    /// \brief give the view matrix
    glm::mat4 getViewMatrix() const;
    
};



