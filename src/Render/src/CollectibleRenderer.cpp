#include "CollectibleRenderer.hpp"

CollectibleRenderer::CollectibleRenderer(ObjProgram *program, MoveMatrix *moveMatrix) : 
    m_program(program), m_moveMatrix(moveMatrix),
    m_modelCoin("../assets/obj/coin/coin.obj"),
    m_modelBonus("../assets/obj/fruit/fruit.obj")

{
    stbi_set_flip_vertically_on_load(false);
    m_modelBonus = Model("../assets/obj/fruit/fruit.obj");
}

void CollectibleRenderer::drawCollectible(const Collectible collectible, glm::mat4 ProjMatrix)
{
    if (!collectible.isHidden())
    {
        m_moveMatrix->computeMVCollectible(collectible.position());
        glm::mat4 MVMatrixCollectible = m_moveMatrix->getCollectibleMVMatrix();
        if (collectible.type() == "Coin")
        {
            m_modelCoin.Draw(ProjMatrix*MVMatrixCollectible, m_program, MVMatrixCollectible);
            
        }
        else
        {
            m_modelBonus.Draw(ProjMatrix*MVMatrixCollectible, m_program, MVMatrixCollectible); 
        }
    }
}