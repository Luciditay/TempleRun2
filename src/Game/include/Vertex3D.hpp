#pragma once

#include "glm/glm.hpp"

struct Vertex3DUV{
    glm::vec3 m_position;
    glm::vec3 m_color;
    glm::vec2 m_texturePos;

    Vertex3DUV(const glm::vec3 pos, const glm::vec3 color, const glm::vec2 texture) {
        m_position = pos;
        m_color = color;
        m_texturePos = texture;
    }
};
