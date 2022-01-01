#include "TileDrawer.hpp"
#include <glm/glm.hpp>
#include "Vertex3D.hpp"
#include "glimac/glm.hpp"

TileDrawer::TileDrawer(const FilePath &applicationPath, const std::string &pathVertexShader, const std::string &pathFragShader, float size) // Création d'une case de 1x1
    : m_formeProgramme(applicationPath, pathVertexShader, pathFragShader),
      m_size(size)
{
    const Vertex3DUV vertices[] = {{glm::vec3(-m_size / 2, 0., m_size), glm::vec3(1., 0., 0.), glm::vec2(0., 0.)}, // BG
                                   {glm::vec3(m_size / 2, 0., m_size), glm::vec3(0., 1., 0.), glm::vec2(1., 0.)},  // BD
                                   {glm::vec3(-m_size / 2., 0., 0.), glm::vec3(0., 0., 1.), glm::vec2(0., 1.)},    // HG
                                   {glm::vec3(m_size / 2., 0., 0.), glm::vec3(1., 0., 1.), glm::vec2(1., 1.)}};

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

void TileDrawer::drawCase(const glm::mat4 &VPMatrix, const glm::vec3 &tileOffset, const glm::vec3 &rotation, int texture)
{
    glm::mat4 MMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(0, 0, 0));                                    // On se place devant la caméra, en ligne 0 à gauche (en 0 du monde décalé de -1, 0, 0)
    MMatrix = glm::translate(MMatrix, glm::vec3(m_size * tileOffset.x, tileOffset.y, -tileOffset.z * m_size)); // On se translate dans la matrice
    // MMatrix = glm::rotate(MMatrix, glm::radians(90.f), rotation);                                              // On récupère la vraie Mview matrice;
    m_formeProgramme.m_Program.use();

    glUniformMatrix4fv(m_formeProgramme.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(VPMatrix * MMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(m_formeProgramme.uTexture, 0);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TileDrawer::drawCase(const glm::mat4 &VPMatrix, const glm::vec3 &tileOffset, int texture)
{
    glm::mat4 MMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(0, 0, 0));                                    // On se place devant la caméra, en ligne 0 à gauche (en 0 du monde décalé de -1, 0, 0)
    MMatrix = glm::translate(MMatrix, glm::vec3(m_size * tileOffset.x, tileOffset.y, -tileOffset.z * m_size)); // On se translate dans la matrice                                               // On récupère la vraie Mview matrice;
    m_formeProgramme.m_Program.use();

    glUniformMatrix4fv(m_formeProgramme.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(VPMatrix * MMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(m_formeProgramme.uTexture, 0);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TileDrawer::drawMurHorizontal(const glm::mat4 &VPMatrix, const glm::vec3 &offset, int TypeTextureID)
{
    // Séparer lA M matrix du code dessin ?
    glm::mat4 MMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(0, 0, 0));
    MMatrix = glm::translate(MMatrix, glm::vec3(-m_size / 2 + m_size * offset.x, m_size / 2, m_size * -offset.z));
    MMatrix = glm::rotate(MMatrix, glm::radians(90.f), glm::vec3(1, 0, 0));
    MMatrix = glm::translate(MMatrix, glm::vec3(-m_size / 2, 0, -m_size / 2));

    m_formeProgramme.m_Program.use();

    glUniformMatrix4fv(m_formeProgramme.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(VPMatrix * MMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TypeTextureID);
    glUniform1i(m_formeProgramme.uTexture, 0);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void TileDrawer::drawMurVertical(const glm::mat4 &VPMatrix, const glm::vec3 &offset, int TypeTextureID)
{
    // Séparer lA M matrix du code dessin ?
    glm::mat4 MMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(0, 0, 0));
    MMatrix = glm::translate(MMatrix, glm::vec3(-m_size / 2 + m_size * offset.x, m_size / 2, m_size * -offset.z));
    MMatrix = glm::rotate(MMatrix, glm::radians(90.f), glm::vec3(0, 0, 1));
    MMatrix = glm::rotate(MMatrix, glm::radians(90.f), glm::vec3(0, 1, 0));
    MMatrix = glm::translate(MMatrix, glm::vec3(-m_size / 2, 0, -m_size / 2));

    m_formeProgramme.m_Program.use();

    glUniformMatrix4fv(m_formeProgramme.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(VPMatrix * MMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TypeTextureID);
    glUniform1i(m_formeProgramme.uTexture, 0);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}