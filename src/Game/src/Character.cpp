#include <iostream>
#include "Character.hpp"
#include "Constants.hpp"
#include <functional>

// float jumpHight(float x)
// {
//     return -8 * x * x + 1.5;
// };

// float squatScale(float x)
// {
//     return 1 - (-5 * x * x + 0.5);
// }

Character::Character(const std::string &modelPath, const glimac::FilePath &applicationPath)
    : m_posChar(0., 0., 0.), m_jumping(false), m_jumpIndex(-0.4), m_speed(0.05), m_distanceEnemy(3), m_enemySpeed(0.001),
      m_scaleChar(1., 1., 1.), m_compenseScale(0., 0., 0.), m_squating(false), m_squatIndex(-0.3),
      m_turn(false), m_turningLeft(false), m_turningRight(false), m_angle(0), m_variationAngle(0),
      m_upChar(0., 1., 0.), m_frontChar({0., 0., 0.1}), m_dead(false),
      m_walkingLeft(false), m_walkingRight(false),
      m_lateralStepRight(0.), m_lateralStepLeft(0.), m_fall(false), m_fallDistance(0),
      m_model(modelPath),
      m_xAxisPosition(0)
{
}

void Character::draw(glm::mat4 MVPMatrix, ObjProgram *program, glm::mat4 MVMatrix)
{
    m_model.Draw(MVPMatrix, program, MVMatrix);
}

void Character::squatAnimation()
{
    // m_scaleChar.y = squatScale(m_squatIndex);
    // m_compenseScale.y = -1 + squatScale(m_squatIndex);
    // m_squatIndex += 0.01;

    std::function<float(float x)> squatScale = [](float x)
    { return 1 - (-5 * x * x + 0.5); };

    m_scaleChar.y = squatScale(m_squatIndex);
    m_compenseScale.y = -0.1 + 0.1 * squatScale(m_squatIndex);
    m_squatIndex += 0.01;
}

void Character::jumpAnimation()
{
    std::function<float(float x)> jumpHight = [](float x)
    { return -8 * x * x + 1.5; };

    m_posChar.y = 1 + jumpHight(m_jumpIndex);
    m_jumpIndex += 0.02;
}

void Character::lateralStepLeftAnimation()
{
    glm::vec3 m_stepRight = glm::normalize(glm::cross(m_frontChar, m_upChar));
    // m_posChar += m_stepRight;
    // m_lateralStepLeft = false;
    // m_xAxisPosition--;

    if (m_lateralStepLeft <= 0.25)
    {
        m_posChar += m_lateralStepLeft * m_stepRight;
        m_lateralStepLeft += 0.05;
    }
    else
    {
        m_lateralStepLeft = 0.;
        m_walkingLeft = false;
        m_xAxisPosition--;
    }
}

void Character::lateralStepRightAnimation()
{
    glm::vec3 m_stepRight = glm::normalize(glm::cross(m_frontChar, m_upChar));
    // m_posChar -= m_stepRight;
    // m_lateralStepRight = false;
    //   m_xAxisPosition++;

    if (m_lateralStepRight <= 0.35)
    {
        m_posChar -= m_lateralStepRight * m_stepRight;
        m_lateralStepRight += 0.05;
    }

    else
    {
        m_lateralStepRight = 0.;
        m_walkingRight = false;
        m_xAxisPosition++;
    }
}

void Character::handleSDLEvent(const SDL_Event &e, int currentTileID)
{
    if (e.type == SDL_KEYDOWN)
    {
        // Key Q : LEFT
        if (currentTileID != 10 && currentTileID != 20 && currentTileID != 30)
        { // Eviter qu'il puisse tourner deux fois dans la même séquence
            m_turn = true;
        }

        if (e.key.keysym.sym == SDLK_q)
        {
            if (currentTileID == 10 || currentTileID == 30 && m_turn) // Left or double turning point
            {                                                         // Lateral Mode
                m_turningLeft = true;
            }
            else
            {
                if (m_xAxisPosition != -1) // Si le perso n'est pas à l'extrême gauche
                {
                    m_walkingLeft = true;
                }
            }
        }
        // Key D : RIGHT
        else if (e.key.keysym.sym == SDLK_d)
        {
            if (currentTileID == 20 || currentTileID == 30 && m_turn)
            { // Lateral move
                m_turningRight = true;
            }
            else
            {
                if (m_xAxisPosition != 1) // Si le perso n'est pas à l'ED
                {
                    m_walkingRight = true;
                }
            }
        }
        // Key Z : JUMP
        if (e.key.keysym.sym == SDLK_z)
        {
            if (m_squating == false)
            {
                m_jumping = true;
            }
        }

        // Key F : FALL
        if (e.key.keysym.sym == SDLK_f)
        {
            if (m_jumping == false)
            {
                m_fall = true;
            }
        }

        // Key S : SQUAT
        else if (e.key.keysym.sym == SDLK_s)
        {
            m_squating = true;
        }
    }
}

void Character::die()
{
    m_dead = true;
}

void Character::checkState(int currentTileId)
{

    if (currentTileId == TextureTypeId::TROU && isJumping() == false)
    {
        std::cout << "T'es mort" << std::endl;
        die();
    }

    // if (currentTileId == TextureTypeId::FautSBaisser && isSquatting() == false)
    // {
    //     std::cout << "Mieux vaut être un nain vivant qu'un grand échalas succombant" << std::endl;
    // }
}

void Character::reactToInputs(const glm::mat4 &matTerrain)
{
    int vAngulaire = 6;
    // Go front
    m_frontChar = m_speed * glm::normalize(glm::rotate(glm::vec3(0., 0., 1.), glm::radians(float(m_angle)), glm::vec3(0., 1., 0.)));
    m_posChar -= m_frontChar;

    int zSizeMatrice = matTerrain.get int xSizeMatrice =

        if (m_posChar)
    {
        std::cout << "Wall collapse" << std::endl;
    }

    // Enemy is coming...
    if (m_distanceEnemy > 0)
    {
        m_distanceEnemy = m_distanceEnemy - m_enemySpeed;
    }
    else
    {
        m_dead = true;
    }

    // Go to left or right
    // glm::vec3 m_stepRight = glm::normalize(glm::cross(m_frontChar, m_upChar));

    if (m_walkingRight == true)
    {
        lateralStepRightAnimation();
    }
    if (m_walkingLeft == true)
    {
        lateralStepLeftAnimation();
    }

    // Jump
    if (m_jumping == true && m_posChar.y >= 1)
    {
        jumpAnimation();
    }
    else
    {
        m_jumping = false;
        m_posChar.y = 1;
        m_jumpIndex = -0.4;
    }

    // Squat
    if (m_squating == true && m_scaleChar.y <= 1)
    {
        squatAnimation();
    }
    else
    {
        m_squating = false;
        m_scaleChar.y = 1;
        m_compenseScale.y = 0;
        m_squatIndex = -0.3;
    }

    // Turn left or Right
    if (m_turningLeft == true && m_variationAngle < 90)
    {

        m_angle += vAngulaire;
        m_variationAngle += vAngulaire;
    }
    else if (m_turningRight == true && m_variationAngle > -90)
    {
        m_angle -= vAngulaire;
        m_variationAngle -= vAngulaire;
    }
    else
    {
        m_variationAngle = 0;
        m_turningLeft = false;
        m_turningRight = false;
        m_turn = false;
    }

    // Fall
    if (m_fall)
    {
        m_fallDistance++;
        m_posChar.y -= m_fallDistance;
        if (m_fallDistance > 20)
        {
            m_dead = true;
        }
    }
}

int Character::getAngle()
{
    return m_angle;
}

glm::vec3 Character::getLookDirection()
{
    return glm::normalize(glm::rotate(glm::vec3(0., 0., 1.), glm::radians(float(m_angle)), glm::vec3(0., 1., 0.)));
}

glm::vec3 Character::getScale()
{
    return m_scaleChar;
}

glm::vec3 Character::getCompenseScale()
{
    return m_compenseScale;
}

glm::vec3 Character::getPos()
{
    return m_posChar;
}

float Character::getDistanceEnemy()
{
    return m_distanceEnemy;
}

bool Character::isDead()
{
    return m_dead;
}

bool Character::isSquating()
{
    return m_squating;
}

bool Character::isJumping()
{
    return m_jumping;
}

void Character::increaseSpeed()
{
    m_speed += 0.05;
    m_enemySpeed -= 0.0005;
}

void Character::reset()
{
    m_enemySpeed = 0.001;
    m_distanceEnemy = 3;
    m_posChar = glm::vec3(0., 0., 0.);
    m_frontChar = glm::vec3(0., 0., 0.1);
    m_fallDistance = 0;
    m_fall = false;
    m_dead = false;
    m_angle = 0;
}
