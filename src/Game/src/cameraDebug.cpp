#include "cameraDebug.hpp"

#include <iostream>

#define PI 3.14159265358979323846

cameraDebug::cameraDebug() : m_Position(glm::vec3(0., 0, 0.)), m_fPhi(PI), m_fTheta(0)
{
    computeDirectionVectors();
}

void cameraDebug::computeDirectionVectors()
{
    m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
    m_LeftVector = glm::vec3(sin(m_fPhi + (PI / 2.)), 0., cos(m_fPhi + (PI / 2)));
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    // std::cout << "[ " << m_FrontVector.x << " " << m_FrontVector.y << " " << m_FrontVector.z<<std::endl;
}

void cameraDebug::moveLeft(float t)
{
    m_Position += t * m_LeftVector;
}

void cameraDebug::moveFront(float t)
{
    m_Position += t * m_FrontVector;
}

void cameraDebug::rotateLeft(float degrees)
{
    m_fPhi += (degrees / 360) * 2 * PI;
    computeDirectionVectors();
}

void cameraDebug::rotateUp(float degrees)
{
    if (m_fTheta >= -M_PI / 2. && m_fTheta <= M_PI / 2.)
    {
        m_fTheta += (degrees / 360) * 2 * PI;
    }
    if (m_fTheta < -M_PI / 2.)
    {
        m_fTheta = -M_PI / 2. + 0.000001;
    }
    if (m_fTheta > M_PI / 2.)
    {
        m_fTheta = M_PI / 2. - 0.000001;
    }
    computeDirectionVectors();
}

glm::mat4 cameraDebug::getViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}

void cameraDebug::reactSDLEvents(const SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_z)
        {
            moveFront(0.1);
        }
        else if (e.key.keysym.sym == SDLK_s)
        {
            moveFront(-0.1);
        }

        if (e.key.keysym.sym == SDLK_q)
        {
            moveLeft(0.1);
        }
        else if (e.key.keysym.sym == SDLK_d)
        {
            moveLeft(-0.1);
        }

        if (e.key.keysym.sym == SDLK_LEFT)
        {
            rotateLeft(1);
        }
        else if (e.key.keysym.sym == SDLK_RIGHT)
        {
            rotateLeft(-1);
        }

        if (e.key.keysym.sym == SDLK_UP)
        {
            rotateUp(1);
        }
        else if (e.key.keysym.sym == SDLK_DOWN)
        {
            rotateUp(-1);
        }
        else if (e.key.keysym.sym == SDLK_SPACE)
        {
            m_Position += m_UpVector;
        }
    }
}