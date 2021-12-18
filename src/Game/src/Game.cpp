#include "Game.hpp"
#include "glimac/glm.hpp"
#include "Constants.hpp"

void Game::drawTerrain(float ratio, cameraDebug &camDebug)
{

    glm::mat4 MVMatrix;
    const glm::mat4 ViewMatrix = camDebug.getViewMatrix();
    const glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);

    idTexture currentTex;
    int idCurrentCase;

    // MVMatrix = glm::translate(MVMatrix, glm::vec3(-1, 0, 0)); //On se place en ligne 0 à gauche

    m_Skybox.draw(ViewMatrix, ProjMatrix);

    for (int i = 0; i < m_MatriceTerrain.getMatrice().size(); i++)
    {
        MVMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(-1, -1, -5));
        MVMatrix = glm::translate(MVMatrix, glm::vec3(-1, 1, -2 * i));
        MVMatrix = glm::rotate(MVMatrix, glm::radians(90.f), glm::vec3(0, 0, 1));
        MVMatrix = glm::rotate(MVMatrix, glm::radians(90.f), glm::vec3(0, 1, 0));
        MVMatrix = glm::translate(MVMatrix, glm::vec3(-1, 0, -1));

        m_tileDrawer.drawCase(ProjMatrix * ViewMatrix * MVMatrix, TextureTypeId::SOL1);

        for (int j = 0; j < m_MatriceTerrain.getMatrice().at(i).size(); j++)
        {
            MVMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(-1, -1, -5)); // On se place devant la caméra, en ligne 0 à gauche (en 0 du monde décalé de -1, 0, 0)
            MVMatrix = glm::translate(MVMatrix, glm::vec3(2 * j, 0, -i * 2)); // On se translate dans la matrice
            MVMatrix = ViewMatrix * MVMatrix;                                 // On récupère la vraie Mview matrice;

            // On texturise
            idCurrentCase = m_MatriceTerrain.getMatrice().at(i).at(j);
            currentTex = m_textureIDManager.getGLTextureMatchingName(idCurrentCase);

            m_tileDrawer.drawCase(ProjMatrix * MVMatrix, currentTex);
        }
        MVMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(-1, -1, -5));
        MVMatrix = glm::translate(MVMatrix, glm::vec3(-1 + 6, 1, -2 * i));
        MVMatrix = glm::rotate(MVMatrix, glm::radians(90.f), glm::vec3(0, 0, 1));
        MVMatrix = glm::rotate(MVMatrix, glm::radians(90.f), glm::vec3(0, 1, 0));
        MVMatrix = glm::translate(MVMatrix, glm::vec3(-1, 0, -1));
        m_tileDrawer.drawCase(ProjMatrix * ViewMatrix * MVMatrix, TextureTypeId::SOL1);
    }
}