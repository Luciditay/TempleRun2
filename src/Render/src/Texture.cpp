#include "Texture.hpp"
#include "glimac/Image.hpp"
#include "iostream"
#include "GL/glew.h"

Texture::Texture(std::string pathTexture){
    m_ptrImage(loadIma)
}


GLuint loadAndBindTexture(const glimac::Image &ptrImage)
{    
    GLuint textureId;
    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);
    //Envoie carte graphique
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,ptrImage.getWidth(),ptrImage.getHeight(), 0, GL_RGBA, GL_FLOAT, ptrImage.getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Débind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;
}