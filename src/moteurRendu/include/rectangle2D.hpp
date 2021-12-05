#pragma once

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glpp.hpp>

struct Vertex2DUV{
    glm::vec2 position;
    glm::vec2 coordonneesTexture;

    Vertex2DUV(const glm::vec2 pos, const glm::vec2 texture) {
        position = pos;
        coordonneesTexture = texture;
    }

};

class Rectangle2D {
    public:
    Rectangle2D(const glimac::FilePath &filePath);
    const void draw(const GLint& texture, const float& scaleW, const float& scaleH, const float& translateX, const float& translateY) const;

    private:
    UniqueBuffer _vbo;
    UniqueBuffer _ibo;
    UniqueVAO _vao;
    glimac::Program _program;
    GLint _locUModelMatrix;
    GLint _locUTexture;

    const void fillBuffers() const;
    const void fillVBO() const;
    const void fillIBO() const;
    const void fillVAO() const;
};