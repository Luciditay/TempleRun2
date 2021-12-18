#include "TileDrawer.hpp"
#include <glm/glm.hpp>
#include "Vertex3D.hpp"
#include "glimac/glm.hpp"

TileDrawer::TileDrawer(const FilePath &applicationPath, const std::string &pathVertexShader, const std::string &pathFragShader) // Création d'une case de 1x1
    : m_formeProgramme(applicationPath, pathVertexShader, pathFragShader)
{
    const Vertex3DUV vertices[] = {{glm::vec3(-0.5, 0., 1.), glm::vec3(1., 0., 0.), glm::vec2(0., 0.)}, // BG
                                   {glm::vec3(0.5, 0., 1.), glm::vec3(0., 1., 0.), glm::vec2(1., 0.)},  // BD
                                   {glm::vec3(-0.5, 0., 0.), glm::vec3(0., 0., 1.), glm::vec2(0., 1.)}, // HG
                                   {glm::vec3(0.5, 0., 0.), glm::vec3(1., 0., 1.), glm::vec2(1., 1.)}};

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex3DUV), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    uint32_t indices[] = {
        0, 1, 2, 1, 2, 3};

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(
        0,
        3, // Nombre de Vertex
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex3DUV),
        0);

    glVertexAttribPointer(
        1,
        3, // Nombre de Vertex
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex3DUV),
        (const void *)(offsetof(Vertex3DUV, m_color)));

    glVertexAttribPointer(
        2,
        2, // Nombre de Vertex
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex3DUV),
        (const void *)(offsetof(Vertex3DUV, m_texturePos)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TileDrawer::drawCase(const glm::mat4 &MVPMatrix, int texture)
{
    m_formeProgramme.m_Program.use();

    glUniformMatrix4fv(m_formeProgramme.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

    glUniform1i(m_formeProgramme.uTexture, texture);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
