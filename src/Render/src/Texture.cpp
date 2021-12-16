#include "Texture.hpp"
#include "glimac/Image.hpp"
#include "iostream"
#include "GL/glew.h"

GLuint P_Texture::getIdTexture() const{
    return m_idTexture;
}

int P_Texture::getnomTexture() const{
    return m_nomEnumTexture;
}

GLuint P_Texture::loadTexture(const std::string &pathTexture){    

    std::unique_ptr<glimac::Image> ptrImage = glimac::loadImage(pathTexture);

    GLuint idTexture;
    glGenTextures(1, &idTexture);

    glBindTexture(GL_TEXTURE_2D, idTexture);
    //Envoie carte graphique
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, ptrImage->getWidth(), ptrImage->getHeight(), 0, GL_RGBA, GL_FLOAT, ptrImage->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Débind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return idTexture;
}

