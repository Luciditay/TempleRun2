#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Texture.hpp"
#include "GL/glew.h"

typedef int idTexture;

class TextureManager{
    public:
        TextureManager(std::vector<P_Texture> listeTextures); //Va parcourir et générer toute les textures dont nous aurons besoin, et les stocker dans la STD::Map
        TextureManager(P_Texture &texture); 

        idTexture getGLTextureMatchingName(int nameTexture) const;
        static inline int s_nbTextures=0; //inline pour déf une constante satic dans la classe (c++ 17)
        
    private:
       std::map<int, idTexture> m_map_NameTexture_IDTexture;
};