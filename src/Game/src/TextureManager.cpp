#include "TextureManager.hpp"

//Prend une liste de texture. Pour chacune, associe leur "nom" (à savoir un int enuméré)
// Et la constante Open GL GL_TEXTUREi dans une map.
// Ainsi, si on connait l'ID de l'objet à dessiner, il suffit de faire map[id] pour avoir la constante GL_TEXXTUREi correspondant, qu'il faudra envoyer dans glUniform1i(uTexture, map[idTexture]) 

TextureManager::TextureManager(std::vector<P_Texture> listeTextures){
    int nomTexture;
    GLuint idTextureOpenGL;
    for (int i=0; i<listeTextures.size(); i++){
        nomTexture = listeTextures.at(i).getnomTexture();
        idTextureOpenGL = listeTextures.at(i).getIdTexture();
        glActiveTexture(GL_TEXTURE0 + TextureManager::s_nbTextures);
        glBindTexture(GL_TEXTURE_2D, idTextureOpenGL);
        m_map_NameTexture_IDTexture[nomTexture] = TextureManager::s_nbTextures;
        TextureManager::s_nbTextures++;
    }
}

TextureManager::TextureManager(P_Texture &texture){
    int nomTexture=texture.getnomTexture();
    GLuint idTextureOpenGL = texture.getIdTexture();
    glActiveTexture(GL_TEXTURE0 + TextureManager::s_nbTextures);
    glBindTexture(GL_TEXTURE_2D, idTextureOpenGL);
    m_map_NameTexture_IDTexture[nomTexture] = TextureManager::s_nbTextures;
    TextureManager::s_nbTextures++;
}

int TextureManager::getIdMatchingName(int nameTexture) const{
    return m_map_NameTexture_IDTexture.at(nameTexture);
}