#include <iostream>
#include "Character.hpp"

float jumpHight(float x) {
    return -50*x*x+10;
};

float squatScale(float x) {
    return 1-(-5*x*x+0.5);
}

Character::Character() : 
    m_posChar(0.,0.,0.), m_jumping(false), m_jumpIndex(-0.4), m_speed(1.), m_distanceEnemy(100),
    m_scaleChar(1.,1.,1.), m_compenseScale(0.,0.,0.), m_squating(false), m_squatIndex(-0.3),
    m_turn(false), m_turningLeft(false), m_turningRight(false), m_angle(0), m_variationAngle(0),
    m_upChar(0.,1.,0.), m_frontChar({0.,0.,0.1}), m_dead(false),
    m_lateralStepRight(false), m_lateralStepLeft(false), m_fall(false), m_fallDistance(0){
}

void Character::handleSDLEvent(const SDL_Event& e) {
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
        
        //Key F : FALL
        if(e.key.keysym.sym == SDLK_f) { 
            if (m_jumping == false) {
                m_fall = true;
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

void Character::reactToInputs() {
            //Go front
            m_frontChar = m_speed*glm::normalize(glm::rotate(glm::vec3(0.,0.,1.), glm::radians(float(m_angle)), glm::vec3(0.,1.,0.)));
            m_posChar-= m_frontChar;
            
            //Go to left or right
            if (m_lateralStepRight == true) {
                glm::vec3 m_stepRight = glm::normalize(glm::cross(m_frontChar, m_upChar));
                m_posChar -= m_stepRight;
                m_lateralStepRight = false;
            }
            if (m_lateralStepLeft == true) {
                 glm::vec3 m_stepRight = glm::normalize(glm::cross(m_frontChar, m_upChar));
                m_posChar += m_stepRight;
                m_lateralStepLeft = false;
            }

            //Jump
            if (m_jumping == true && m_posChar.y >= 1) {
                m_posChar.y = 1+jumpHight(m_jumpIndex);
                m_jumpIndex+=0.02;
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

            //Fall
            if(m_fall) {
                m_fallDistance++;
                m_posChar.y-=m_fallDistance;
            }
}

int Character::getAngle() {
    return m_angle;
}

glm::vec3 Character::getScale() {
    return m_scaleChar;
}

glm::vec3 Character::getCompenseScale() {
    return m_compenseScale;
}

glm::vec3 Character::getPos() {
    return m_posChar;
}


