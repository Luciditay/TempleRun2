#pragma once

#include <glimac/glm.hpp>
#include "FreeflyCamera.hpp"
#include "TrackballCamera.hpp"
#include <glimac/SDLWindowManager.hpp>

class Camera {
    private:
    FreeflyCamera m_freeflycamera;
    TrackballCamera m_trackballcamera;
    bool m_activeCameraIsTrackball; //true : trackball, false : freefly
    bool m_dragAndDropCam;
    bool m_cameraCanMove;

    public:
    Camera(const float distance = 5., const float angleX = 0., const float angleY = 0.);
    glm::mat4 getViewMatrix() const;
    void handleSDLEvent(const SDL_Event& e);
};