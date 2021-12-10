#include "Collectibles.hpp"

Collectibles::Collectibles(ObjProgram* program, MoveMatrix* moveMatrix, Character* character, ScoreCounter* score) :
    m_renderer(program, moveMatrix), m_char(character), m_score(score) {}

void Collectibles::addCollectible(glm::vec2 position, std::string type, bool flying) {
    m_collectibles.push_back(Collectible(position, type, flying, m_char, m_score));
}

void Collectibles::draw(){
    for(auto it = std::begin(m_collectibles); it != std::end(m_collectibles); ++it) {
        it->collect();
        m_renderer.drawCollectible(*it);
    }
}