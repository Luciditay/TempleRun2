#pragma once
#include <vector>
#include "TileDrawer.hpp"
#include "Skybox.hpp"
#include "Matrice.hpp"
#include <map>
#include "TextureManager.hpp"
#include "cameraDebug.hpp"
#include "glimac/Program.hpp"
#include "GlewInit.hpp"
#include "Cameras.hpp"
#include "MoveMatrix.hpp"
#include "ObjProgram.hpp"
#include "Light.hpp"
#include "Vertex3D.hpp"
#include "Collectible.hpp"
#include "Collectibles.hpp"
#include "CollectibleRenderer.hpp"
#include "Model.hpp"
#include "TTFtext.hpp"
#include "UI.hpp"
#include "UIScreens.hpp"
#include "HighScores.hpp"

class Render3D
{
public:
    Render3D(const Matrice &m, const TextureManager &tm, Camera &cam, const FilePath &applicationPath, const std::string &VSPath, const std::string &FSPath, const std::string &modelPath, const std::string &modelPathEnemy, const glimac::SDLWindowManager &wm, float largeur, float hauteur, const char *fontpath, const char *image1, const char *image2)
        : m_MatriceTerrain(m),
          m_tileDrawer(applicationPath, VSPath, FSPath),
          m_textureIDManager(tm),
          m_camera(-2., M_PI / 6., 0.),
          m_rotateTerrainLeft(false),
          m_rotateTerrainRight(false),
          m_Skybox(applicationPath),
          m_character(modelPath),
          m_enemy(modelPathEnemy),
          m_moveMatrix(&m_camera, &m_character),
          m_objprogram(applicationPath),
          m_lightdir1("Directional", 0, m_objprogram.m_Program, &m_moveMatrix),
          m_lightdir2("Directional", 1, m_objprogram.m_Program, &m_moveMatrix),
          m_windowManager(wm),

          //////LAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
          // ui
          compteur(0),
          fontPath(fontpath),
          score(applicationPath, largeur, hauteur),
          imagePath(image1),
          imagePath2(image2),
          menu(imagePath, fontPath, 30, applicationPath, largeur, hauteur),
          titleScreen(imagePath2, fontPath, 100, applicationPath, largeur, hauteur),
          deadScreen(imagePath2, fontPath, 100, applicationPath, largeur, hauteur),
          done(false),
          gameStart(false),
          enemySpeed(0.1),
          distanceEnemy(100),
          looser(false),
          pause(true),
          m_collectibles(&m_objprogram, &m_moveMatrix, &m_character, &score)

    {
        stbi_set_flip_vertically_on_load(false);
        m_enemy = Model(modelPathEnemy);
        m_collectibles.addCollectible(glm::vec2(1., -4.), "Bonus", true);
        m_collectibles.addCollectible(glm::vec2(2., -6.), "Coin", false);
        m_collectibles.addCollectible(glm::vec2(0., -10.), "Coin", false);
        m_collectibles.addCollectible(glm::vec2(1., -14.), "Bonus", false);
        m_collectibles.addCollectible(glm::vec2(7., -9.), "Coin", true);
        m_collectibles.addCollectible(glm::vec2(8., -7.), "Bonus", false);
        m_collectibles.addCollectible(glm::vec2(9., -13.), "Coin", false);
    } // Default constructor of cam is fine

    void playGame(float largeur, float hauteur);

    void drawTerrain(float ratio);

    void drawCrossBetweenTerrain(int idTypeCroisement, int nbreCase, int zOffset, const glm::mat4 &PVMatrix); // Draw un croisement

    Point2D<int> getPosPersonnageInGame();

    void sendLightsToProgram();

    void WillCharacterDie();

    void updateCharacterState(int i, int j);

    glm::mat4 MMatrixMur(int xOffset, int yOffset, int zOffset);
    glm::mat4 MMatrixMurHorizontal(const glm::vec3 &offset);
    void catch_UI(SDL_Event e);
    void enemyCalcul();
    void draw_Ui();
    void save(int slot);
    void load(int slot);
    void loadAndSave(std::string str);

private:
    Matrice m_MatriceTerrain;          // On va push des vecteurs de 3 (correspondant à chaque ligne du terrain
    TileDrawer m_tileDrawer;           // Contient le vao, le vbo et une carré de 2x2 démarrant à (0, 0)
    TextureManager m_textureIDManager; // Une map qui va faire le lien entre l'ID d'une case (converti à partir des nombres dans la matriceTerrain) et la valeur de sa constante GLTEXTUREi, que l'on passera pour la dessiner en paramètres (pas clair, check the TP) ==> On peut aussi passer par un enum, pour ne pas avoir à convertir ?
    Camera m_camera;
    Skybox m_Skybox; // dans un std::vector (i.e ca fait du matrice) qui représentera tout le terrain/la partie du terrain actuellement générée en faisant Matrice(FileMatrice)
    Character m_character;
    SDLWindowManager m_windowManager;
    MoveMatrix m_moveMatrix;
    bool m_rotateTerrainLeft;
    bool m_rotateTerrainRight;
    ObjProgram m_objprogram;
    Model m_enemy;

    // Collectibles collectibles;

    Collectibles m_collectibles;

    Light m_lightdir1;
    Light m_lightdir2;

    // ui
    //////LAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    const char *fontPath;
    int compteur;
    ScoreCounter score;
    const char *imagePath;
    const char *imagePath2;
    Menu menu;
    TitleScreen titleScreen;
    DeadScreen deadScreen;
    bool done;
    bool gameStart;
    float enemySpeed;
    float distanceEnemy;
    bool looser;
    bool pause;
};