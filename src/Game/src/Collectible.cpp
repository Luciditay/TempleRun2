#include "Collectible.hpp"

Collectible::Collectible(glm::vec2 position, std::string type, bool flying,Character* character, ScoreCounter* score) :
   m_scale(0.8,0.8,0.8), m_flying(flying), m_type(type), m_hidden(false), m_char(character), m_score(score) {
    if (m_flying) {
        m_position = glm::vec3(position.x, 15., position.y);
    } else {
         m_position = glm::vec3(position.x, 0., position.y);
    }

    if (m_type == "Coin") {
        m_scale = glm::vec3(0.05,0.05,0.05);
    }
}

void Collectible::action() {
    if (m_type == "Coin") {
        std::cout<< "bravo t'as une pièce"<<std::endl;
        m_score->increaseItems();
    }
    if (m_type == "Bonus") {
        std::cout<< "bravo t'as un bonus"<<std::endl;
        m_char->increaseSpeed();
    }
}

float Collectible::distanceToChar() {
    glm::vec2 posChar2D = glm::vec2(m_char->getPos().x, m_char->getPos().z);
    glm::vec2 posCollectible2D = glm::vec2(m_position.x, m_position.z);
    glm::vec2 CharToColl = posChar2D-posCollectible2D;
    return CharToColl.x*CharToColl.x + CharToColl.y*CharToColl.y;
}

void Collectible::collect() {
    if(distanceToChar() < 50 && (!m_hidden) && ((m_flying && m_char->isJumping()) || (!m_flying && !m_char->isJumping()))) {
        m_hidden = true;
        action();
    }
}

const bool Collectible::isHidden() const {
    return m_hidden;
}

const std::string Collectible::type() const {
    return m_type;
}

const glm::vec3 Collectible::position() const {
    return m_position;
}

const glm::vec3 Collectible::scale() const {
    return m_scale;
}