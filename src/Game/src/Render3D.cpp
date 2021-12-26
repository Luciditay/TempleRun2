#include "Render3D.hpp"
#include "glimac/glm.hpp"
#include "Constants.hpp"

void Render3D::playGame(float largeur, float hauteur)
{
    int currentTime = 0;
    int previousTime = 0;
    Point2D<int> currentPos;
    int currentTileId;
    while (true)
    {
        // update current time
        currentTime = SDL_GetTicks();
        if (currentTime - previousTime > 30)
        {

            // Nettoyage de la fenêtre
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // On récupère la position du personnage dans la matrice
            currentPos = getPosPersonnageInGame();
            //  std::cout << currentPos.x << currentPos.z << std::endl;
            currentTileId = m_MatriceTerrain.getMatrice().at(-currentPos.z).at(currentPos.x);
            // std::cout << currentTileId << std::endl;
            //   Event loop:
            SDL_Event e;

            while (m_windowManager.pollEvent(e))
            {

                m_camera.handleSDLEvent(e);
                m_character.handleSDLEvent(e, currentTileId);

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

void Render3D::drawCrossBetweenTerrain(int idTypeCroisement, int nbreCase, int zOffset, const glm::mat4 &PVMatrix)
{
    int currentTex = m_textureIDManager.getGLTextureMatchingName(idTypeCroisement);

    if (idTypeCroisement == 10)
    {
        for (int i = 0; i < nbreCase; i++)
        {
            // Dessin de la case
            m_tileDrawer.drawCase(PVMatrix, glm::vec3(-1 - i, 0, zOffset), currentTex);
        }
        // Mur à droite
        m_tileDrawer.drawMurVertical(PVMatrix, glm::vec3(3, 0, zOffset), TextureTypeId::SOL1);
    }

    if (idTypeCroisement == 20)
    {
        for (int i = 0; i < nbreCase; i++)
        {
            // Dessin de la case
            m_tileDrawer.drawCase(PVMatrix, glm::vec3(3 + i, 0, zOffset), currentTex);
        }
        // Mur à gauche
        m_tileDrawer.drawMurVertical(PVMatrix, glm::vec3(0, 0, zOffset), TextureTypeId::SOL1);
    }

    if (idTypeCroisement == 30)
    { // On dessine une case à gauche et à droite
        for (int i = 0; i < nbreCase; i++)
        {
            m_tileDrawer.drawCase(PVMatrix, glm::vec3(-1 - i, 0, zOffset), currentTex);
            m_tileDrawer.drawCase(PVMatrix, glm::vec3(3 + i, 0, zOffset), currentTex);
        }
    }
}

void Render3D::sendLightsToProgram()
{
    m_objprogram.m_Program.use();
    // lumière
    m_lightdir1.sendUniformIntensity(glm::vec3(1., 1., 0.));
    m_lightdir1.sendUniformVec(glm::vec3(0., 1., -1.));
    m_lightdir2.sendUniformIntensity(glm::vec3(1., 1., 1.));
    m_lightdir2.sendUniformVec(glm::vec3(0., -1., 1.));
    // glm::vec4 dirLight = glm::rotate(moveMatrix.getLightMVMatrix(), float(M_PI/4.), glm::vec3(0.,0.,1.))*glm::vec4(1.,1.,1.,0.);
    glm::vec4 dirLight = m_moveMatrix.getLightMVMatrix() * glm::vec4(0., 0., 1., 0.);
    glUniform3f(m_objprogram.uLightDir_vs, dirLight.x, dirLight.y, dirLight.z);
    // glUniform3f(objProgram.uLightIntensity, 1.,1., 1.);
    glm::vec4 posLight = m_moveMatrix.getWorldMVMatrix() * glm::vec4(0., 0.02, 0., 1.);
    glUniform3f(m_objprogram.uLightPos_vs, posLight.x, posLight.y, posLight.z);
    glUniform3f(m_objprogram.uLightIntensityPos, 1., 0., 0.);
    // matériaux
    glUniform3f(m_objprogram.uKd, 2., 2., 2.);
    glUniform3f(m_objprogram.uKs, 1., 1., 1.);
    glUniform1f(m_objprogram.uShininess, 50.);
}

void Render3D::drawTerrain(float ratio)
{
    glm::mat4 MMatrix;
    const glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);

    float tailleCase = m_tileDrawer.getSizeTile();

    idTexture currentTex;
    int idCurrentCase, idLeftTile, idRightTile, idUpperTile, idLowerTile;

    const std::vector<std::vector<int>> terrain = m_MatriceTerrain.getMatrice();

    m_moveMatrix.computeAllMatrix();
    const glm::mat4 VMatrix = m_moveMatrix.getViewMatrix();
    // const glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    // const glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    const glm::mat4 MVMatrixPersonnage = m_moveMatrix.getCharMVMatrix();
    m_Skybox.draw(VMatrix, ProjMatrix);

    sendLightsToProgram();
    m_character.draw(ProjMatrix * MVMatrixPersonnage, &m_objprogram, MVMatrixPersonnage);

    const glm::mat4 worldMVMatrix = m_moveMatrix.getWorldMVMatrix();

    for (int i = 0; i < terrain.size(); i++)
    {
        for (int j = 0; j < terrain.at(i).size(); j++)
        {
            // On texturise
            idCurrentCase = terrain.at(i).at(j);

            if (idCurrentCase != 0)
            {
                currentTex = m_textureIDManager.getGLTextureMatchingName(idCurrentCase);
                m_tileDrawer.drawCase(ProjMatrix * worldMVMatrix, glm::vec3(j, 0, i), currentTex);

                if (j - 1 < 0 || terrain.at(i).at(j - 1) == 0) // On dessine à gauche de toute les cases au bord du monde, un mur
                {
                    m_tileDrawer.drawMurVertical(ProjMatrix * worldMVMatrix, glm::vec3(j, 0, i), TextureTypeId::SOL1);
                }

                if (j + 1 >= terrain.at(i).size() || terrain.at(i).at(j + 1) == 0) // On dessine à gauche de toute les cases au bord du monde, un mur
                {
                    m_tileDrawer.drawMurVertical(ProjMatrix * worldMVMatrix, glm::vec3(j + 1, 0, i), TextureTypeId::SOL1);
                }

                if (i - 1 < 0 || terrain.at(i - 1).at(j) == 0) // On dessine à gauche de toute les cases au bord du monde, un mur
                {
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(j + 1, 0, i - 1), TextureTypeId::SOL1);
                }

                if (i + 1 >= terrain.size() || terrain.at(i + 1).at(j) == 0) // On dessine à gauche de toute les cases au bord du monde, un mur
                {
                    m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(j + 1, 0, i), TextureTypeId::SOL1);
                }
            }
        }

        // if (idCurrentCase == 10)
        // {
        //     m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(-1, 0, i), TextureTypeId::SOL1);
        // }

        // if (idCurrentCase == 20)
        // {
        //     m_tileDrawer.drawMurVertical(ProjMatrix * worldMVMatrix, glm::vec3(1, 0, i), TextureTypeId::SOL1);
        // }

        // if (idCurrentCase == 30)
        // {
        //     m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(-1, 0, i), TextureTypeId::SOL1);
        //     m_tileDrawer.drawMurHorizontal(ProjMatrix * worldMVMatrix, glm::vec3(1, 0, i), TextureTypeId::SOL1);
        // }
    }
}

Point2D<int> Render3D::getPosPersonnageInGame()
{
    int x = m_character.getxAxisPosition() + 1;
    int z = glm::floor(m_character.getPos().z);
    return {x, z};
}
// CHANGER LA FIN AVEC LES IF IMBRIQUES ?