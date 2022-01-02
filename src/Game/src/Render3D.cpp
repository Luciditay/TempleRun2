#include "Render3D.hpp"
#include "glimac/glm.hpp"
#include "Constants.hpp"

void Render3D::playGame(float largeur, float hauteur)
{
    int currentTime = 0;
    int previousTime = 0;
    Point2D<int> currentPos;
    int currentTileId;
    menu.setStop(&done);
    SDL_EnableKeyRepeat(10, 10);
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
            //    std::cout << currentTileId << std::endl;
            //   Event loop:
            SDL_Event e;

            while (m_windowManager.pollEvent(e))
            {

                m_camera.handleSDLEvent(e);
                m_character.handleSDLEvent(e, currentTileId);

                catch_UI(e);

                if (e.type == SDL_QUIT)
                {
                    // A CODER : FONCTION LIBERATIONS DE MEMOIRES
                    exit(EXIT_SUCCESS); // Leave the loop after this iteration
                }
            }

            /*********************************
             * HERE SHOULD COME THE RENDERING CODE
             *********************************/
            

            // if (menu.ge)
            if (!pause) {
                m_character.reactToInputs();
                m_character.checkState(currentTileId);
                drawTerrain(largeur / hauteur);
                enemyCalcul();
            }
            
            // !!! UI must be drawn after everything else, because it's 2D !
            draw_Ui();

            // Update the display
            m_windowManager.swapBuffers();

            // update previous time
            previousTime = currentTime;
        }
    }
    TTF_Quit();
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

    const glm::mat4 MVMatrixEnemy = m_moveMatrix.getEnemyMVMatrix();
    // m_character.draw(ProjMatrix * MVMatrixEnemy, &m_objprogram, MVMatrixEnemy);
    m_enemy.Draw(ProjMatrix * MVMatrixEnemy, &m_objprogram, MVMatrixEnemy);

    m_collectibles.draw(ProjMatrix);

    const glm::mat4 worldMVMatrix = m_moveMatrix.getWorldMVMatrix();

    std::cout << "debut draw" << std::endl;
    for (int i = 0; i < terrain.size(); i++)
    {
        std::cout << "Debut ligne " << i << std::endl;
        for (int j = 0; j < terrain.at(i).size(); j++)
        {
            // On texturise
            idCurrentCase = terrain.at(i).at(j);

            if (idCurrentCase != 0)
            {
                currentTex = m_textureIDManager.getGLTextureMatchingName(idCurrentCase);
                m_tileDrawer.drawCase(ProjMatrix * worldMVMatrix, glm::vec3(j, 0, i), currentTex);
                std::cout << currentTex << " ";

                if (j - 1 < 0 || terrain.at(i).at(j - 1) == 0) // On dessine à gauche de toute les cases au bord du monde, un mur
                {
                    m_tileDrawer.drawMurVertical(ProjMatrix * worldMVMatrix, glm::vec3(j, 0, i), m_textureIDManager.getGLTextureMatchingName(TextureTypeId::SOL1));
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
        std::cout << std::endl;
    }
}

Point2D<int> Render3D::getPosPersonnageInGame()
{
    int x = glm::floor(m_character.getPos().x + 1);
    int z = glm::floor(m_character.getPos().z);
    return {x, z};
}
// CHANGER LA FIN AVEC LES IF IMBRIQUES ?

// ui SCREEN

void Render3D::catch_UI(SDL_Event e)
{

    menu.handleSDLEvent(e, gameStart);

    if (e.type == SDL_MOUSEBUTTONUP)
    {
        gameStart = titleScreen.close();

        if (looser)
        {
            deadScreen.close();
            m_character.reset();
            looser = false;
            pause = false;
            compteur = 0;
            score.resetItemsAndDistance();
            score.update();
        }
    }
}

void Render3D::enemyCalcul()
{
    if (m_character.isDead())
    {
        // perdu
        deadScreen.open();
        deadScreen.draw();
        deadScreen.updateScore(score.getTotalScore());
        looser = true;
        pause = true;
        menu.updateHighScores(score.getTotalScore());
    }
}

void Render3D::draw_Ui()
{
    if (!pause && !looser)
    {
        compteur += 1;
        if (compteur >= 10)
        {
            score.increaseDistance();
            compteur = 0;
        }
        score.update();
        score.draw();
    }
    if (gameStart)
    {
        menu.draw();
    }
    titleScreen.draw();

    if (menu.someMenuIsOpen())
    {
        pause = true;
    }
    else
    {
        pause = false;
    }
    if (menu.shouldStartAgain())
    {
        m_character.reset();
        compteur = 0;
        score.resetItemsAndDistance();
        score.update();
    }
}
