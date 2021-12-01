#pragma once
#include <glimac/glm.hpp>

class TrackballCamera {
    private : 
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

    float m_fDistanceInitial;
    float m_fAngleXInitial;
    float m_fAngleYInitial;

    public:
    TrackballCamera(const float distance = 5., const float angleX = 0., const float angleY = 0.);

    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void resetCamera();

    glm::mat4 getViewMatrix() const;
    
};



