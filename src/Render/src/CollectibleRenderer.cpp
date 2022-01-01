#include "CollectibleRenderer.hpp"

CollectibleRenderer::CollectibleRenderer(ObjProgram *program, MoveMatrix *moveMatrix) : 
    m_program(program), m_moveMatrix(moveMatrix),
    m_modelCoin("../assets/obj/coin/Only_Spider_with_Animations_Export.obj"),
    m_modelBonus("../assets/obj/Handgun_obj.obj")

{
}

void CollectibleRenderer::drawCollectible(const Collectible collectible, glm::mat4 ProjMatrix)
{
    if (!collectible.isHidden())
    {
        m_moveMatrix->computeMVCollectible(collectible.position());
        // m_program->m_Program.use();
        glm::mat4 MVMatrixCollectible = m_moveMatrix->getCollectibleMVMatrix();
        // m_program->sendMatrix(m_moveMatrix->getCollectibleMVMatrix(), );
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