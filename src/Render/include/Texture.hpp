#pragma once
#include "glimac/Image.hpp"
#include <string>
#include "GL/glew.h" 

class Texture{
    public:
        Texture(std::string pathTexture);
        void getIdTexture();

    private:
        std::unique_ptr<Image> m_ptrImage;
        GLuint m_idTexture;
};

GLuint loadAndBindTexture(const glimac::Image &ptrImage);