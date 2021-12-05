#include "Case.hpp"


CaseTerrain::~CaseTerrain(){
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    delete &m_VertexHG;
    delete &m_VertexHD;
    delete &m_VertexBG;
    delete &m_VertexBD;
}

void CaseTerrain::loadCase(){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glm::vec4 vertices[] = {m_VertexHG, m_VertexHD, m_VertexBG, m_VertexBD};
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(glm::vec4), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    uint32_t indices[] = {
        0, 1, 2, 1, 2, 3
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
    0, 
    4,
    GL_FLOAT,
    GL_FALSE,
    sizeof(glm::vec4),
    0
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CaseTerrain::drawCase(){
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

