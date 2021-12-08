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
    m_posChar(0.,0.,0.), m_jumping(false), m_jumpIndex(-0.4),
    m_scaleChar(1.,1.,1.), m_compenseScale(0.,0.,0.), m_squating(false), m_squatIndex(-0.3),
    m_turn(false), m_turningLeft(false), m_turningRight(false), m_angle(0), m_variationAngle(0),
    m_upChar(0.,1.,0.), m_frontChar({0.,0.,0.1}),
    m_lateralStepRight(false), m_lateralStepLeft(false){
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
            //Go front
            m_frontChar = glm::normalize(glm::rotate(glm::vec3(0.,0.,1.), glm::radians(float(m_angle)), glm::vec3(0.,1.,0.)));
            m_posChar-= m_frontChar;
            
            //Go to left or right
            if (m_lateralStepRight == true) {
                glm::vec3 m_stepRight = glm::normalize(glm::cross(m_frontChar, m_upChar));
                m_posChar += m_stepRight;
                m_lateralStepRight = false;
            }
            if (m_lateralStepLeft == true) {
                 glm::vec3 m_stepRight = glm::normalize(glm::cross(m_frontChar, m_upChar));
                m_posChar -= m_stepRight;
                m_lateralStepLeft = false;
            }

            //Jump
            if (m_jumping == true && m_posChar.y >= 1) {
                m_posChar.y = 1+jumpHight(m_jumpIndex);
                m_jumpIndex+=0.008;
            } else {
                m_jumping = false;
                m_posChar.y = 1;
                m_jumpIndex = -0.4;
            }

            //Squat
            if (m_squating == true && m_scaleChar.y <= 1) {
                m_scaleChar.y = squatScale(m_squatIndex);
                m_compenseScale.y = -1+squatScale(m_squatIndex);
                m_squatIndex+=0.01;
            } else {
                m_squating = false;
                m_scaleChar.y = 1;
                m_compenseScale.y = 0;
                m_squatIndex = -0.3;
            }

            //Turn left or Right
            if (m_turningLeft == true && m_variationAngle < 90) {
                m_angle+=2;
                m_variationAngle+=2;
            } else if (m_turningRight == true && m_variationAngle > -90) {
                m_angle-=2;
                m_variationAngle-=2;
            } else {
                m_variationAngle = 0;
                m_turningLeft = false;
                m_turningRight = false;
            }
}

void MoveMatrix::computeViewMatrix() {
    m_ViewMatrix = glm::translate(m_camera->getViewMatrix(), glm::vec3(0.,-m_posChar.y,0.));
}

void MoveMatrix::computeMVCharacter() {
    glm::mat4 VChar = glm::translate(glm::mat4(), glm::vec3(0.,m_posChar.y,0.)+m_compenseScale);
    VChar = glm::scale(VChar, m_scaleChar);
    m_MVMatrixCharacter = m_ViewMatrix * VChar;
}

void MoveMatrix::computeMVWorld() {
    glm::mat4 VWorld =  glm::rotate(glm::mat4(), glm::radians(float(-m_angle)), glm::vec3(0.,1.,0.));
    VWorld = glm::translate(VWorld, glm::vec3(-m_posChar.x, 0, -m_posChar.z));
    VWorld = glm::scale(VWorld, glm::vec3(250.,250.,250.));
    m_MVMatrixWorld = m_ViewMatrix * VWorld;
}

void MoveMatrix::computeMVLight() {
    glm::mat4 VLight = glm::rotate(glm::mat4(), glm::radians(float(-m_angle)), glm::vec3(0.,1.,0.));
    m_MVMatrixLight = m_ViewMatrix * VLight;
}

void MoveMatrix::setDistanceEnemy(const float distance) {
    m_distanceEnemy = distance;
}

void MoveMatrix::computeMVEnemy() {
    m_MVMatrixEnemy = glm::translate(getCharMVMatrix(), glm::vec3(0.,1.,m_distanceEnemy));
}

void MoveMatrix::computeAllMatrix() {
    reactToInputs();
    computeViewMatrix();
    computeMVCharacter();
    computeMVWorld();
    computeMVLight();
    computeMVEnemy();
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

glm::mat4 MoveMatrix::getEnemyMVMatrix(){
    return m_MVMatrixEnemy;
}