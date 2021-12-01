#include <iostream>
#include "glimac/Cameras.hpp"

Camera::Camera(const float distance, const float angleX, const float angleY) :
    m_freeflycamera(),
    m_trackballcamera(distance, angleX, angleY), 
    m_activeCameraIsTrackball(true),
    m_dragAndDropCam(false),
    m_cameraCanMove(true) {}

glm::mat4 Camera::getViewMatrix() const {
    if (m_activeCameraIsTrackball) {
        return m_trackballcamera.getViewMatrix();
    } else {
        return m_freeflycamera.getViewMatrix();
    }
};

void Camera::handleSDLEvent(const SDL_Event& e) {
    if(e.type == SDL_MOUSEBUTTONDOWN && m_cameraCanMove && m_activeCameraIsTrackball) {
        if (e.button.button == 4) {
                m_trackballcamera.moveFront(0.5);
        } 
        if (e.button.button == 5) {
                m_trackballcamera.moveFront(-0.5);
        }
    }

    if(e.type == SDL_MOUSEBUTTONDOWN && m_cameraCanMove) {
        m_dragAndDropCam = true;
    }
    if(e.type == SDL_MOUSEBUTTONUP && m_cameraCanMove) {
        m_dragAndDropCam = false;
    }

    if(e.type == SDL_MOUSEMOTION && m_dragAndDropCam && m_cameraCanMove) {
        if (e.motion.xrel>0) {
            if (m_activeCameraIsTrackball) {
                m_trackballcamera.rotateLeft(0.03);
            } else {
                m_freeflycamera.rotateLeft(-1);
            }
        }
        if (e.motion.xrel<0) {
            if (m_activeCameraIsTrackball) {
                m_trackballcamera.rotateLeft(-0.03);
            } else {
                m_freeflycamera.rotateLeft(1);
            }
        }
        if (e.motion.yrel>0) {
            if (m_activeCameraIsTrackball) {
                m_trackballcamera.rotateUp(0.03);
            } else {
                m_freeflycamera.rotateUp(-1);
            }
        }
        if (e.motion.yrel<0) {
            if (m_activeCameraIsTrackball) {
                m_trackballcamera.rotateUp(-0.03);
            } else {
                m_freeflycamera.rotateUp(1);
            }
        }
    }

    if(e.key.keysym.sym == SDLK_c && e.key.state == SDL_PRESSED && m_cameraCanMove) {
            SDL_EnableKeyRepeat(0,0);
            m_activeCameraIsTrackball = !m_activeCameraIsTrackball;
            SDL_EnableKeyRepeat(10,10);
    }

    if(e.key.keysym.sym == SDLK_l && e.key.state == SDL_PRESSED) {
        SDL_EnableKeyRepeat(0,0);
        m_trackballcamera.resetCamera();
        m_cameraCanMove = !m_cameraCanMove;
        SDL_EnableKeyRepeat(10,10);
    }
}