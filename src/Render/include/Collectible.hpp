#pragma once
#include <glimac/glm.hpp>
#include <string>
#include <functional>
#include "ObjProgram.hpp"
#include "Character.hpp"
#include "UI.hpp"

#include "Model.hpp"

class Collectible
{
private:
    glm::vec3 m_position;
    glm::vec3 m_scale;
    bool m_flying;      // position on vertical axis : true sky, false floor
    std::string m_type; // "Coin" or "Bonus"
    bool m_hidden;

    Character *m_char;
    ScoreCounter *m_score;

public:
    Collectible(glm::vec2 position, std::string type, bool flying, Character *character, ScoreCounter *score);
    void collect();
    float distanceToChar();
    bool isHidden() const;
    void reset();
    const std::string type() const;
    const glm::vec3 position() const;
    const glm::vec3 scale() const;
    void action();
};