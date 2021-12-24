#pragma once

#include "GL/glew.h"
#include "formProgram.hpp"
#include "glimac/FilePath.hpp"
#include "glm/glm.hpp"

class TileDrawer // Case de base, sans saut ni trou
{
public:
    TileDrawer(const FilePath &applicationPath, const std::string &pathVertexShader, const std::string &pathFragShader, float size = 2); // Création d'une case de 1x1

    void drawCase(const glm::mat4 &VPMatrix, const glm::vec3 &offset, int texture);

    void drawMurHorizontal(const glm::mat4 &VPMatrix, const glm::vec3 &offset, int texture);
    void drawMurVertical(const glm::mat4 &VPMatrix, const glm::vec3 &offset, int TypeTextureID);

    float getSizeTile()
    {
        return m_size;
    }

private:
    FormProgram m_formeProgramme;
    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;
    float m_size;
};