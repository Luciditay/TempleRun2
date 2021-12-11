#pragma once

#include <glm/glm.hpp>
#include <includes.hpp>
#include "Vertex3D.hpp"

class Case
{
public:
    virtual void loadCase() const = 0;
    virtual void drawCase() const = 0; //Méthode virtuelle pure
};

class CaseTerrain : protected Case //Case de base, sans saut ni trou
{
public:
    CaseTerrain(const Vertex3DUV VertexHG, const Vertex3DUV VertexHD, const Vertex3DUV VertexBG, Vertex3DUV VertexBD) 
    : m_VertexHG(VertexHG), 
      m_VertexHD(VertexHD), 
      m_VertexBG(VertexBG), 
      m_VertexBD(VertexBD)  {}

    ~CaseTerrain();
    void loadCase();
    void drawCase();

private:
    Vertex3DUV  m_VertexHG; //Les quatres coins de la case
    Vertex3DUV  m_VertexHD;
    Vertex3DUV  m_VertexBG;
    Vertex3DUV  m_VertexBD;
    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;
};

class CaseMur : protected Case
{
public:
    CaseMur();
    virtual ~CaseMur(); //Virtuel car polymorphisme
    void drawCase();

private:
    float hauteurMur;

};