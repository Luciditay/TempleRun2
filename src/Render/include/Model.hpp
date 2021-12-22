#pragma once
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <Mesh.hpp>
#include <stb/stb_image.h>
//#include "ObjProgram.hpp"

/// \class Model
/// \brief class that load a 3D object .obj using assimp
class Model
{
public:
    /// \brief constructor (load the .obj)
    /// \param path : path of the .obj
    Model(std::string path)
    //: m_objProgramme(applicationPath)
    {
        loadModel(path);
    }
    /// \brief draw the object
    /// \param program : used to draw
    void Draw(glimac::Program &program);

private:
    // model data
    std::vector<Mesh> _meshes;            /*!< vector of model meshes */
    std::string _directory;               /*!< model directory */
    std::vector<Texture> textures_loaded; /*!< vector of loaded texture */
                                          //    ObjProgram m_objProgramme;

    /// \brief load the .obj
    /// \param path : path of the .obj
    void loadModel(std::string path);
    /// \brief travel through every node of the model (recursive)
    /// \param node : according to assimp documentation : a node has a "place and orientation relative to their parents", and it "can refer to 0..x meshes"
    /// \param scene : imported 3D scene (with assimp)
    void processNode(aiNode *node, const aiScene *scene);
    /// \brief fill a mesh with the data imported by assimp
    /// \param mesh : data of a 3D model (imported by assimp)
    /// \param scene : imported 3D scene (with assimp)
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    /// \brief load textures
    /// \param mat : assimp material
    /// \param type : type of the texture (aiTextureType_DIFFUSE or aiTextureType_SPECULAR)
    /// \param typeName : "texture_diffuse" or "texture_specular"
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                              std::string typeName);
};