#pragma once

#include "GL/glew.h"

class TileDrawer // Case de base, sans saut ni trou
{
public:
    // TileDrawer(const Vertex3DUV VertexHG, const Vertex3DUV VertexHD, const Vertex3DUV VertexBG, Vertex3DUV VertexBD)
    // : m_VertexHG(VertexHG),
    //   m_VertexHD(VertexHD),
    //   m_VertexBG(VertexBG),
    //   m_VertexBD(VertexBD)  {}

    // TileDrawer(Vertex3DUV vertices[4])
    // : m_VertexHG(vertices[0]),
    //   m_VertexHD(vertices[1]),
    //   m_VertexBG(vertices[2]),
    //   m_VertexBD(vertices[3])  {}

    TileDrawer(); // Création d'une case de 1x1

    void drawCase();

private:
    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;
};

// class CaseMur : protected Case
// {
// public:
//     CaseMur();
//     // virtual ~CaseMur(); //Virtuel car polymorphisme
//     void drawCase();

// private:
//     float hauteurMur;
// };