#pragma once
#include <glimac/glm.hpp>
#include <string>
#include <functional>
#include "ObjProgram.hpp"
#include "Collectible.hpp"
#include <MoveMatrix.hpp>

#include "Model.hpp"

class CollectibleRenderer
{
private:
    Model m_modelCoin;
    Model m_modelBonus;
    ObjProgram *m_program;
    MoveMatrix *m_moveMatrix;

public:
    CollectibleRenderer(ObjProgram *program, MoveMatrix *moveMatrix);
    void drawCollectible(const Collectible collectible, glm::mat4 ProjMatrix);
};