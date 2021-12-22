#include "Game.hpp"
#include "glimac/glm.hpp"
#include "Constants.hpp"

void Game::drawCrossBetweenTerrain(int idTypeCroisement, int zOffset, const glm::mat4 &PVMatrix)
{
    int currentTex = m_textureIDManager.getGLTextureMatchingName(idTypeCroisement);

    if (idTypeCroisement == 10)
    {
        // Dessin de la case
        m_tileDrawer.drawCase(PVMatrix, glm::vec3(-1, 0, zOffset), currentTex);
        m_tileDrawer.drawCase(PVMatrix, glm::vec3(-2, 0, zOffset), currentTex);
        // Mur à droite
        m_tileDrawer.drawMurVertical(PVMatrix, glm::vec3(3, 0, zOffset), TextureTypeId::SOL1);
    }

    if (idTypeCroisement == 20)
    {
        m_tileDrawer.drawCase(PVMatrix, glm::vec3(3, 0, zOffset), currentTex);
        m_tileDrawer.drawCase(PVMatrix, glm::vec3(4, 0, zOffset), currentTex);
        // Mur à gauche
        m_tileDrawer.drawMurVertical(PVMatrix, glm::vec3(0, 0, zOffset), TextureTypeId::SOL1);
    }

    if (idTypeCroisement == 30)
    { // On dessine une case à gauche et à droite
        m_tileDrawer.drawCase(PVMatrix, glm::vec3(-1, 0, zOffset), currentTex);
        m_tileDrawer.drawCase(PVMatrix, glm::vec3(-2, 0, zOffset), currentTex);
        m_tileDrawer.drawCase(PVMatrix, glm::vec3(3, 0, zOffset), currentTex);
        m_tileDrawer.drawCase(PVMatrix, glm::vec3(4, 0, zOffset), currentTex);
    }
}

void Game::drawTerrain(float ratio, cameraDebug &camDebug)
{
    glm::mat4 MMatrix;
    const glm::mat4 ViewMatrix = camDebug.getViewMatrix();
    const glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);

    float tailleCase = m_tileDrawer.getSizeTile();

    int endSegmentTerrain = m_MatriceTerrain.getMatrice().size() - 1;

    idTexture currentTex;
    int idCurrentCase;
    int finCroisement = 0;

    // MVMatrix = glm::translate(MVMatrix, glm::vec3(-1, 0, 0)); //On se place en ligne 0 à gauche

    m_Skybox.draw(ViewMatrix, ProjMatrix);
    m_character.draw(ProjMatrix * ViewMatrix);

    for (int i = 0; i < m_MatriceTerrain.getMatrice().size(); i++)
    {

        for (int j = 0; j < m_MatriceTerrain.getMatrice().at(i).size(); j++)
        {
            // On texturise
            idCurrentCase = m_MatriceTerrain.getMatrice().at(i).at(j);
            currentTex = m_textureIDManager.getGLTextureMatchingName(idCurrentCase);

            // Dessin de la case
            m_tileDrawer.drawCase(ProjMatrix * ViewMatrix, glm::vec3(j, 0, i), currentTex);
        }

        if (idCurrentCase == 10 || idCurrentCase == 20 || idCurrentCase == 30)  // Si on arrive à un croisement : 10=left, 20=right, 30=both
        {                                                                       // Croisement means : pas de dessin des murs mais dessin d'une/deux cases en plus sur les côtés
            drawCrossBetweenTerrain(idCurrentCase, i, ProjMatrix * ViewMatrix); // Fonction qui sert à R : appelle une fonction déjà existante
            finCroisement++;

            if (finCroisement == 3) // On arrive "au bout" du croisement, il faut dessiner les murs
            {
                m_tileDrawer.drawMurHorizontal(ProjMatrix * ViewMatrix, glm::vec3(0, 0, i), TextureTypeId::SOL1);
                m_tileDrawer.drawMurHorizontal(ProjMatrix * ViewMatrix, glm::vec3(1, 0, i), TextureTypeId::SOL1);
                m_tileDrawer.drawMurHorizontal(ProjMatrix * ViewMatrix, glm::vec3(2, 0, i), TextureTypeId::SOL1);

                if (idCurrentCase == 10)
                {
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * ViewMatrix, glm::vec3(-1, 0, i), TextureTypeId::SOL1);
                }

                if (idCurrentCase == 20)
                {
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * ViewMatrix, glm::vec3(1, 0, i), TextureTypeId::SOL1);
                }

                if (idCurrentCase == 30)
                {
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * ViewMatrix, glm::vec3(-1, 0, i), TextureTypeId::SOL1);
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * ViewMatrix, glm::vec3(1, 0, i), TextureTypeId::SOL1);
                }
            }
        }

        else
        {
            //  Dessin des murs de "gauche"
            m_tileDrawer.drawMurVertical(ProjMatrix * ViewMatrix, glm::vec3(0, 0, i), TextureTypeId::SOL1);

            // Dessin des murs de droite
            m_tileDrawer.drawMurVertical(ProjMatrix * ViewMatrix, glm::vec3(tailleCase * 3, 0, i), TextureTypeId::SOL1);
        }
    }
}

// CHANGER LA FIN AVEC LES IF IMBRIQUES ?