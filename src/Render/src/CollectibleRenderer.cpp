#include "CollectibleRenderer.hpp"

CollectibleRenderer::CollectibleRenderer(ObjProgram *program, MoveMatrix *moveMatrix, const glimac::FilePath &applicationPath, const std::string coinModelPath, const std::string &bonusModelPath) : 
    m_program(program), m_moveMatrix(moveMatrix),
    m_modelCoin(coinModelPath),
    m_modelBonus(bonusModelPath)

{
}

// void CollectibleRenderer::drawCollectible(const Collectible collectible)
// {
//     if (!collectible.isHidden())
//     {
//         m_moveMatrix->computeMVCollectible(collectible.position());
//         m_program->m_Program.use();
//         m_program->sendMatrix(m_moveMatrix->getCollectibleMVMatrix(), collectible.scale(), glm::vec3(0., 0., 0.));
//         if (collectible.type() == "Coin")
//         {
//             m_modelCoin.Draw(m_program->m_Program);
//         }
//         else
//         {
//             m_modelBonus.Draw(m_program->m_Program);
//         }
//     }
// }