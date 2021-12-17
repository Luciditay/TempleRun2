#pragma once
#include <vector>
#include "Case.hpp"
#include "Skybox.hpp"
#include "Matrice.hpp"
#include <map>
#include "TextureManager.hpp"
#include "Drawer.hpp"
#include "cameraDebug.hpp"
#include "glimac/Program.hpp"

class CaseTerrain;

class Terrain{
    public:
       
        Terrain(const std::string &fileMatrice, std::vector<P_Texture> listeTextures, const FilePath& applicationPath, const std::string &pathVertexShader, const std::string &pathFragShader)
        : m_MatriceTerrain(fileMatrice),
         // m_caseTerrain(),
          m_formeProgramme(applicationPath, pathVertexShader, pathFragShader),
          m_textureIDManager(listeTextures),
          m_camDebug() {} //Default constructor of cam is fine

        void loadVAOVBO();
        void drawTerrain(CaseTerrain &Case, float ratio, cameraDebug &camDebug);

        cameraDebug getCamDebug() const{
            return m_camDebug;
        }

    private:
        Matrice m_MatriceTerrain; // On va push des vecteurs de 3 (correspondant à chaque ligne du terrain
        //CaseTerrain m_caseTerrain; //Contient le vao, le vbo et une carré de 1x1 démarrant à 
        //Drawer m_drawer;
        FormProgram m_formeProgramme;
        TextureManager m_textureIDManager; // Une map qui va faire le lien entre l'ID d'une case (converti à partir des nombres dans la matriceTerrain) et la valeur de sa constante GLTEXTUREi, que l'on passera pour la dessiner en paramètres (pas clair, check the TP) ==> On peut aussi passer par un enum, pour ne pas avoir à convertir ?
        cameraDebug m_camDebug;
        //Skybox m_Skybox;                                   // dans un std::vector (i.e ca fait du matrice) qui représentera tout le terrain/la partie du terrain actuellement générée en faisant Matrice(FileMatrice)
       
};