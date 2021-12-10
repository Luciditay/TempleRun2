#pragma once
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <vector>
#include <string>
#include <GL/glew.h>

/// \struct Vertex
/// \brief 3D vertex
struct Vertex {
    glm::vec3 _Position; /*!< position (3 floats) */
    glm::vec3 _Normal; /*!< normal (3 floats) */
    glm::vec2 _TexCoords; /*!< texture coordinates (3 floats) */
};

struct Texture {
    unsigned int _id; /*!< texture id */
    std::string _type; /*!< texture type */
    std::string _path;  /*!<we store the path of the texture to compare with other textures*/ 
};  

/// \class Mesh
class Mesh {
    public:
        // mesh data
        std::vector<Vertex>       _vertices; /*!< vector of vertices of the mesh */
        std::vector<unsigned int> _indices; /*!< vector of indices of the mesh */
        std::vector<Texture>      _textures; /*!< vector of textures of the mesh */

        /// \brief constructor
        /// \param vertices : a vector of vertices 
        /// \param indices : a vector of indices 
        /// \param textures : a vector of textures 
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        /// \brief draw the mesh
        /// \param program : program of shaders used to draw the mesh
        void Draw(glimac::Program& program);
    private:
        //  render data
        unsigned int _VAO, _VBO, _EBO; /*!< buffers needed to draw */
        /// \brief create buffers
        void setupMesh();
};  