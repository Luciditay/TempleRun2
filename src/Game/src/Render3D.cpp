#include "Render3D.hpp"
#include "glimac/glm.hpp"
#include "Constants.hpp"

void Render3D::playGame(float largeur, float hauteur)
{
    int currentTime = 0;
    int previousTime = 0;
    while (true)
    {
        // update current time
        currentTime = SDL_GetTicks();
        if (currentTime - previousTime > 30)
        {

            // Nettoyage de la fenêtre
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // update current time
            //  Event loop:
            SDL_Event e;

            while (m_windowManager.pollEvent(e))
            {

                m_camera.handleSDLEvent(e);
                m_character.handleSDLEvent(e);

                if (e.type == SDL_QUIT)
                {
                    // A CODER : FONCTION LIBERATIONS DE MEMOIRES
                    exit(EXIT_SUCCESS); // Leave the loop after this iteration
                }
            }

            /*********************************
             * HERE SHOULD COME THE RENDERING CODE
             *********************************/
            m_character.reactToInputs();
            drawTerrain(largeur / hauteur);

            // Update the display
            m_windowManager.swapBuffers();

            // update previous time
            previousTime = currentTime;
        }
    }
}

void Render3D::drawCrossBetweenTerrain(int idTypeCroisement, int zOffset, const glm::mat4 &PVMatrix)
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

void Render3D::drawTerrain(float ratio)
{
    glm::mat4 MMatrix;
    const glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);

    float tailleCase = m_tileDrawer.getSizeTile();

    int endSegmentTerrain = m_MatriceTerrain.getMatrice().size() - 1;

    idTexture currentTex;
    int idCurrentCase;
    int finCroisement = 0;

    // MVMatrix = glm::translate(MVMatrix, glm::vec3(-1, 0, 0)); //On se place en ligne 0 à gauche

    m_moveMatrix.computeAllMatrix();
    const glm::mat4 VMatrix = m_moveMatrix.getViewMatrix();
    // const glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    // const glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    const glm::mat4 MVMatrixPersonnage = m_moveMatrix.getCharMVMatrix();
    m_Skybox.draw(VMatrix, ProjMatrix);
    m_character.draw(ProjMatrix * MVMatrixPersonnage);

    const glm::mat4 worldMVMatrix = m_moveMatrix.getWorldMVMatrix();

    for (int i = 0; i < m_MatriceTerrain.getMatrice().size(); i++)
    {

        for (int j = 0; j < m_MatriceTerrain.getMatrice().at(i).size(); j++)
        {
            // On texturise
            idCurrentCase = m_MatriceTerrain.getMatrice().at(i).at(j);
            currentTex = m_textureIDManager.getGLTextureMatchingName(idCurrentCase);

            // Dessin de la case
            m_tileDrawer.drawCase(ProjMatrix * worldMVMatrix, glm::vec3(j, 0, i), currentTex);
        }

        if (idCurrentCase == 10 || idCurrentCase == 20 || idCurrentCase == 30)     // Si on arrive à un croisement : 10=left, 20=right, 30=both
        {                                                                          // Croisement means : pas de dessin des murs mais dessin d'une/deux cases en plus sur les côtés
            drawCrossBetweenTerrain(idCurrentCase, i, ProjMatrix * worldMVMatrix); // Fonction qui sert à R : appelle une fonction déjà existante
            finCroisement++;

            if (finCroisement == 3) // On arrive "au bout" du croisement, il faut dessiner les murs
            {
                m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(0, 0, i), TextureTypeId::SOL1);
                m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(1, 0, i), TextureTypeId::SOL1);
                m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(2, 0, i), TextureTypeId::SOL1);

                if (idCurrentCase == 10)
                {
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(-1, 0, i), TextureTypeId::SOL1);
                }

                if (idCurrentCase == 20)
                {
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(1, 0, i), TextureTypeId::SOL1);
                }

                if (idCurrentCase == 30)
                {
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(-1, 0, i), TextureTypeId::SOL1);
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(1, 0, i), TextureTypeId::SOL1);
                }
            }
        }

        else
        {
            //  Dessin des murs de "gauche"
            m_tileDrawer.drawMurVertical(ProjMatrix * worldMVMatrix, glm::vec3(0, 0, i), TextureTypeId::SOL1);

            // Dessin des murs de droite
            m_tileDrawer.drawMurVertical(ProjMatrix * worldMVMatrix, glm::vec3(tailleCase * 3, 0, i), TextureTypeId::SOL1);
        }
    }
}

// CHANGER LA FIN AVEC LES IF IMBRIQUES ?