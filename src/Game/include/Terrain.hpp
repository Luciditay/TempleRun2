#pragma once
#include <vector>
#include "Case.hpp"
#include "Skybox.hpp"

class Terrain{
    public:
        void loadMatTerrain(std::string &filePath);
        void drawTerrain();

    private:
        CaseTerrain m_casesTerrain;
        int** m_MatriceTerrain;
        Skybox m_Skybox;
        GLuint vao;
        Gluint vbo;
};