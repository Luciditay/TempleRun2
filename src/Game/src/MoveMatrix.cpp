#include <iostream>
#include "MoveMatrix.hpp"

float jumpHight(float x) {
    return -50*x*x+10;
};

float squatScale(float x) {
    return 1-(-5*x*x+0.5);
}

MoveMatrix::MoveMatrix(Camera* camera) : 
    m_camera(camera),
    m_moveChar(0.,0.,0.), m_jumping(false), m_jumpIndex(-0.4),
    m_scaleChar(1.,1.,1.), m_moveCharwithoutCam(0.,0.,0.), m_squating(false), m_squatIndex(-0.3),
    m_turn(false), m_turningLeft(false), m_turningRight(false), m_angle(0), m_variationAngle(0),
    m_moveWorld(0.,0.,0.), m_stepRight(), m_up(0.,1.,0.), m_front({0.,0.,0.1}),
    m_lateralStepRight(false), m_lateralStepLeft(false),
    m_currentTime(0), m_previousTime(0) {
}

void MoveMatrix::handleSDLEvent(const SDL_Event& e) {
    if(e.type == SDL_KEYDOWN) {
        //Key T or Y : Enable Turn or Rotation 
        if(e.key.keysym.sym == SDLK_t) {
            m_turn = true;
        }
        if(e.key.keysym.sym == SDLK_y) {
            m_turn = false;
        }
        //Key Q : LEFT
        if(e.key.keysym.sym == SDLK_q) {
            if (!m_turn) { //Lateral Mode
                m_lateralStepLeft = true;
            } else { //Rotation 90°
                if (m_turningRight == false) {
                    m_turningLeft = true;
                }
            }
        }
        //Key D : RIGHT
        else if(e.key.keysym.sym == SDLK_d) {
            if (!m_turn) { //Lateral move
            m_lateralStepRight = true;
            } else { //Rotation 90°
                if (m_turningLeft == false) {
                    m_turningRight = true;
                }
            }
        } 
        //Key Z : JUMP
        if(e.key.keysym.sym == SDLK_z) {
            if (m_squating == false) {
                m_jumping = true;
            }
        }
        //Key S : SQUAT
        else if(e.key.keysym.sym == SDLK_s) {
            if (m_jumping == false) {
                m_squating = true;
            }
        }
    }
}

void MoveMatrix::reactToInputs() {
        //update current time
        m_currentTime = SDL_GetTicks();

        if(m_currentTime - m_previousTime > 15) {
            //Go front
            m_front = glm::normalize(glm::rotate(glm::vec3(0.,0.,1.), glm::radians(float(m_angle)), glm::vec3(0.,1.,0.)))*glm::vec3(0.3,0.3,0.3);
            m_moveWorld += m_front;
            
            //Go to left or right
            if (m_lateralStepRight == true) {
                m_stepRight = glm::normalize(glm::cross(m_front, m_up))*glm::vec3(0.5,0.5,0.5);
                m_moveWorld += m_stepRight;
                m_lateralStepRight = false;
            }
            if (m_lateralStepLeft == true) {
                m_stepRight = glm::normalize(glm::cross(m_front, m_up))*glm::vec3(0.5,0.5,0.5);
                m_moveWorld -= m_stepRight;
                m_lateralStepLeft = false;
            }

            //Jump
            if (m_jumping == true && m_moveChar.y >= 1) {
                m_moveChar.y = 1+jumpHight(m_jumpIndex);
                m_jumpIndex+=0.008;
            } else {
                m_jumping = false;
                m_moveChar.y = 1;
                m_jumpIndex = -0.4;
            }

            //Squat
            if (m_squating == true && m_scaleChar.y <= 1) {
                m_scaleChar.y = squatScale(m_squatIndex);
                m_moveCharwithoutCam.y = -1+squatScale(m_squatIndex);
                m_squatIndex+=0.01;
            } else {
                m_squating = false;
                m_scaleChar.y = 1;
                m_moveCharwithoutCam.y = 0;
                m_squatIndex = -0.3;
            }

            //Turn left or Right
            if (m_turningLeft == true && m_variationAngle <= 90) {
                m_angle++;
                m_variationAngle++;
            } else if (m_turningRight == true && m_variationAngle >= -90) {
                m_angle--;
                m_variationAngle--;
            } else {
                m_variationAngle = 0;
                m_turningLeft = false;
                m_turningRight = false;
            }
        //update previous time
        m_previousTime = m_currentTime;
        }
        
}

void MoveMatrix::computeViewMatrix() {
    m_ViewMatrix = glm::translate(m_camera->getViewMatrix(), -m_moveChar);
}

void MoveMatrix::computeMVCharacter() {
    glm::mat4 VChar = glm::translate(glm::mat4(), m_moveChar+m_moveCharwithoutCam);
    VChar = glm::scale(VChar, m_scaleChar);
    m_MVMatrixCharacter = m_ViewMatrix * VChar;
}

void MoveMatrix::computeMVWorld() {
    glm::mat4 VWorld =  glm::rotate(glm::mat4(), glm::radians(float(-m_angle)), glm::vec3(0.,1.,0.));
    VWorld = glm::translate(VWorld, m_moveWorld);
    VWorld = glm::scale(VWorld, glm::vec3(250.,250.,250.));
    m_MVMatrixWorld = m_ViewMatrix * VWorld;
}

void MoveMatrix::computeMVLight() {
    glm::mat4 VLight = glm::rotate(glm::mat4(), glm::radians(float(-m_angle)), glm::vec3(0.,1.,0.));
    m_MVMatrixLight = m_ViewMatrix * VLight;
}

void MoveMatrix::computeAllMatrix() {
    reactToInputs();
    computeViewMatrix();
    computeMVCharacter();
    computeMVWorld();
    computeMVLight();
}

glm::mat4 MoveMatrix::getViewMatrix() {
    return m_ViewMatrix;
}

glm::mat4 MoveMatrix::getCharMVMatrix() {
    return m_MVMatrixCharacter;
}

glm::mat4 MoveMatrix::getWorldMVMatrix(){
    return m_MVMatrixWorld;
}

glm::mat4 MoveMatrix::getLightMVMatrix(){
    return m_MVMatrixLight;
}