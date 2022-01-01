#include "TextureManager.hpp"

// Prend une liste de texture. Pour chacune, associe leur "nom" (à savoir un int enuméré)
//  Et la constante Open GL GL_TEXTUREi dans une map.
//  Ainsi, si on connait l'ID de l'objet à dessiner, il suffit de faire map[id] pour avoir la constante GL_TEXXTUREi correspondant, qu'il faudra envoyer dans glUniform1i(uTexture, map[idTexture])

TextureManager::TextureManager(std::vector<P_Texture> listeTextures)
{
    int nomTexture;
    GLuint idTextureOpenGL;
    for (int i = 0; i < listeTextures.size(); i++)
    {
        nomTexture = listeTextures.at(i).getnomTexture();
        idTextureOpenGL = listeTextures.at(i).getIdTexture();
        m_map_NameTexture_IDTexture[nomTexture] = idTextureOpenGL;
    }
}

TextureManager::TextureManager(P_Texture &texture)
{
    int nomTexture = texture.getnomTexture();
    GLuint idTextureOpenGL = texture.getIdTexture();
    m_map_NameTexture_IDTexture[nomTexture] = idTextureOpenGL;
}

int TextureManager::getGLTextureMatchingName(int nameTexture) const
{
    return m_map_NameTexture_IDTexture.at(nameTexture);
}