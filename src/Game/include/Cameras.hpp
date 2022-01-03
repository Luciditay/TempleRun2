#pragma once

#include <glimac/glm.hpp>
#include "FreeflyCamera.hpp"
#include "TrackballCamera.hpp"
#include <glimac/SDLWindowManager.hpp>

/// \class Camera
class Camera {
    private:
    FreeflyCamera m_freeflycamera; /*!< character eyes point of view */
    TrackballCamera m_trackballcamera; /*!< camera turning around the character */
    bool m_activeCameraIsTrackball; /*!< true : trackball, false : freefly */ 
    bool m_dragAndDropCam; /*!< true if the camera is being dragged (mouse button down) */ 
    bool m_cameraCanMove; /*!< true if the camera is not blocked */ 

    public:
    /// \brief constructor
    /// \param distance : distance camera - character
    /// \param angleX : initial vertical angle
    /// \param angleY : initial horizontal angle
    Camera(const float distance = 5., const float angleX = 0., const float angleY = 0.);
    /// \brief give camera view matrix
    glm::mat4 getViewMatrix() const;
    /// \brief react to mouse and keys inputs to move the camera
    void handleSDLEvent(const SDL_Event& e);
};