#pragma once
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <glimac/Mesh.hpp>
#include <stb/stb_image.h>

class Model 
{
    public:
        Model(std::string path)
        {
            loadModel(path);
        }
        void Draw(glimac::Program& program);	
    private:
        // model data
        std::vector<Mesh> _meshes;
        std::string _directory;
        std::vector<Texture> textures_loaded; 

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
};