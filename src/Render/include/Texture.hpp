#pragma once
#include "glimac/Image.hpp"
#include <string>
#include "GL/glew.h" 

class P_Texture{
    public:      
        GLuint getIdTexture() const;
        int getnomTexture() const;

        P_Texture(const int nomEnumTexture, const std::string &pathTexture) 
        : m_nomEnumTexture(nomEnumTexture),
          m_idTexture(loadTexture(pathTexture)) {}

    private:
        GLuint loadTexture(const std::string &pathTexture);

    private:
        const int m_nomEnumTexture;
        GLuint m_idTexture;
};