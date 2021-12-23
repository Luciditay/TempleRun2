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

class Game
{
public:
    Game(const Matrice &m, const TextureManager &tm, const FilePath &applicationPath, const std::string &VSPath, const std::string &FSPath, const std::string &modelPath, const glimac::SDLWindowManager &wm)
        : m_MatriceTerrain(m),
          m_tileDrawer(applicationPath, VSPath, FSPath),
          m_textureIDManager(tm),
          m_camDebug(),
          m_rotateTerrainLeft(false),
          m_rotateTerrainRight(false),
          m_Skybox(applicationPath),
          m_character(modelPath, applicationPath),
          m_windowManager(wm) {} // Default constructor of cam is fine

    void playGame();

    void drawTerrain(float ratio, cameraDebug &camDebug, Character &c);

    void drawCrossBetweenTerrain(int idTypeCroisement, int zOffset, const glm::mat4 &PVMatrix); // Draw un croisement

    glm::mat4 MMatrixMur(int xOffset, int yOffset, int zOffset);
    glm::mat4 MMatrixMurHorizontal(const glm::vec3 &offset);

    cameraDebug getCamDebug() const
    {
        return m_camDebug;
    }

private:
    Matrice m_MatriceTerrain;          // On va push des vecteurs de 3 (correspondant à chaque ligne du terrain
    TileDrawer m_tileDrawer;           // Contient le vao, le vbo et une carré de 2x2 démarrant à (0, 0)
    TextureManager m_textureIDManager; // Une map qui va faire le lien entre l'ID d'une case (converti à partir des nombres dans la matriceTerrain) et la valeur de sa constante GLTEXTUREi, que l'on passera pour la dessiner en paramètres (pas clair, check the TP) ==> On peut aussi passer par un enum, pour ne pas avoir à convertir ?
    cameraDebug m_camDebug;
    Skybox m_Skybox; // dans un std::vector (i.e ca fait du matrice) qui représentera tout le terrain/la partie du terrain actuellement générée en faisant Matrice(FileMatrice)
    Character m_character;
    SDLWindowManager m_windowManager;
    bool m_rotateTerrainLeft;
    bool m_rotateTerrainRight;
};