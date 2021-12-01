#pragma once
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <vector>
#include <string>
#include <GL/glew.h>

struct Vertex {
    glm::vec3 _Position;
    glm::vec3 _Normal;
    glm::vec2 _TexCoords;
};

struct Texture {
    unsigned int _id;
    std::string _type;
    std::string _path;  // we store the path of the texture to compare with other textures
};  

class Mesh {
    public:
        // mesh data
        std::vector<Vertex>       _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture>      _textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(glimac::Program& program);
    private:
        //  render data
        unsigned int _VAO, _VBO, _EBO;

        void setupMesh();
};  