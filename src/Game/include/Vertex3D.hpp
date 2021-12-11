#pragma once

#include "glm/glm.hpp"

struct Vertex3DUV{
    glm::vec3 m_position;
    glm::vec2 m_coordonneesTexture;

    Vertex3DUV(const glm::vec3 pos, const glm::vec2 texture) {
        m_position = pos;
        m_coordonneesTexture = texture;
    }
};
