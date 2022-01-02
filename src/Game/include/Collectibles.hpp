#pragma once
#include <glimac/glm.hpp>
#include <string>
#include <functional>
#include <vector>
#include "ObjProgram.hpp"
#include "Character.hpp"
#include "Collectible.hpp"
#include "CollectibleRenderer.hpp"

#include "Model.hpp"

class Collectibles {
    private:
    std::vector<Collectible> m_collectibles;
    CollectibleRenderer m_renderer;
    Character* m_char;
    ScoreCounter* m_score;

    public:
    Collectibles(ObjProgram* program, MoveMatrix* moveMatrix, Character* character, ScoreCounter* score);
    void addCollectible(glm::vec2 position, std::string type, bool flying);
    void draw(glm::mat4 ProjMatrix);
    void reset();
};