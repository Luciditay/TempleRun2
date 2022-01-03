#include <rectangle2D.hpp>

Rectangle2D::Rectangle2D(const glimac::FilePath &filePath)
{
    fillBuffers();

    // Création program et variables uniformes
    _program = glimac::loadProgram(filePath.dirPath() + "shaders/rect2D.vs.glsl",
                                   filePath.dirPath() + "shaders/rect2D.fs.glsl");
    _locUModelMatrix = glGetUniformLocation(_program.getGLId(), "uModelMatrix");
    _locUTexture = glGetUniformLocation(_program.getGLId(), "uTexture");
}

void Rectangle2D::fillBuffers() const
{
    fillVBO();
    fillIBO();
    fillVAO();
}

void Rectangle2D::fillVBO() const
{
    // Bind du vbo
    glBindBuffer(GL_ARRAY_BUFFER, *_vbo);
    // Remplissage du vbo
    Vertex2DUV vertices[] = {
        Vertex2DUV(glm::vec2(-1, 1), glm::vec2(0, 0)),
        Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)),
        Vertex2DUV(glm::vec2(1, -1), glm::vec2(1, 1)),
        Vertex2DUV(glm::vec2(1, 1), glm::vec2(1, 0)),
    };
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);
    // Débind du vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rectangle2D::fillIBO() const
{
    // Bind du ibo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *_ibo);
    // Tableau d'indices
    uint32_t indices[] = {
        0, 1, 2, 0, 2, 3};
    // Remplissage du ibo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (6) * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    // Débind du ibo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Rectangle2D::fillVAO() const
{
    // Bind
    glBindVertexArray(*_vao);
    // Bind du ibo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *_ibo);
    // Activation attributs vertex
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COULEUR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COULEUR);
    // Spécification des attributs de vertex (bind et débind vbo)
    glBindBuffer(GL_ARRAY_BUFFER, *_vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid *)(offsetof(Vertex2DUV, position)));
    glVertexAttribPointer(VERTEX_ATTR_COULEUR, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid *)(offsetof(Vertex2DUV, coordonneesTexture)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // débind vbo
    glBindVertexArray(0);
}

const glm::mat3 scale2D(const float sx, const float sy)
{
    return glm::mat3(glm::vec3(sx, 0., 0.), glm::vec3(0., sy, 0.), glm::vec3(0., 0., 1.));
}

const glm::mat3 translate2D(const float tx, const float ty)
{
    return glm::mat3(glm::vec3(1., 0., 0.), glm::vec3(0., 1., 0.), glm::vec3(tx, ty, 1.));
}

void Rectangle2D::draw(const GLint &texture, const float &scaleW, const float &scaleH, const float &translateX, const float &translateY) const
{
    glClear(GL_DEPTH_BUFFER_BIT);

    _program.use();

    // Dessiner avec le VA0
    glBindVertexArray(*_vao);

    // Bind Texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(_locUTexture, 0);

    glm::mat3 Mscale = scale2D(scaleW, scaleH);
    glm::mat3 uModelMatrix = translate2D(translateX, translateY) * Mscale;
    glUniformMatrix3fv(_locUModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Débind
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}