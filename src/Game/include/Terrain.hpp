#pragma once
#include <vector>
#include "Case.hpp"
#include "Skybox.hpp"
#include "Matrice.hpp"
#include <map>
#include "TextureManager.hpp"

class CaseTerrain;

class Terrain{
    public:
        Terrain(const std::string &fileMatrice, std::vector<P_Texture> listeTextures)
        : m_MatriceTerrain(fileMatrice),
          m_textureIDManager(listeTextures) {}

        void loadVAOVBO();
        void drawTerrain();

    private:
        Matrice m_MatriceTerrain; // On va push des vecteurs de 3 (correspondant à chaque ligne du terrain
        //CaseTerrain m_caseTerrain;
        
        TextureManager m_textureIDManager; // Une map qui va faire le lien entre l'ID d'une case (converti à partir des nombres dans la matriceTerrain) et la valeur de sa constante GLTEXTUREi, que l'on passera pour la dessiner en paramètres (pas clair, check the TP) ==> On peut aussi passer par un enum, pour ne pas avoir à convertir ?
        
        //Skybox m_Skybox;                                   // dans un std::vector (i.e ca fait du matrice) qui représentera tout le terrain/la partie du terrain actuellement générée en faisant Matrice(FileMatrice)
        GLuint vao;
        GLuint vbo;
};