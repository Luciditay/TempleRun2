#pragma once

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glpp.hpp>

/// \struct Vertex2DUV
/// \brief a vertex in 2D
struct Vertex2DUV
{
    glm::vec2 position;           /*!< position of the vertex */
    glm::vec2 coordonneesTexture; /*!< texture coordinates */

    /// \brief constructor
    /// \param pos : position
    /// \param texture : texture coordinate
    Vertex2DUV(const glm::vec2 pos, const glm::vec2 texture)
    {
        position = pos;
        coordonneesTexture = texture;
    }
};

/// \class Rectangle2D
/// \brief a rectangle drawn in 2D (for the UI)
class Rectangle2D
{
public:
    /// \brief constructor
    /// \param filePath : application path
    Rectangle2D(const glimac::FilePath &filePath);
    /// \brief draw the rectangle
    /// \param texture : id of the texture to bind
    /// \param scaleW : scale (width)
    /// \param scaleH : scale (height)
    /// \param translateX : translate (X axis)
    /// \param translateY : translate (Y axis)
    void draw(const GLint &texture, const float &scaleW, const float &scaleH, const float &translateX, const float &translateY) const;

private:
    UniqueBuffer _vbo;        /*!<  VBO (Glint that handles to put OpenGL objects in vectors) */
    UniqueBuffer _ibo;        /*!<  IBO (Glint that handles to put OpenGL objects in vectors) */
    UniqueVAO _vao;           /*!<  VAO (Glint that handles to put OpenGL objects in vectors) */
    glimac::Program _program; /*!< shaders program */
    GLint _locUModelMatrix;   /*!< id of uniform variable, to send the Model Matrix */
    GLint _locUTexture;       /*!< id of uniform variable, to send the texture */

    /// \brief fill all the 3 buffers
    void fillBuffers() const;
    /// \brief fill VBO buffers
    void fillVBO() const;
    /// \brief fill IBO buffers
    void fillIBO() const;
    /// \brief fill Vertex Array Object
    void fillVAO() const;
};