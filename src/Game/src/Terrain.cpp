#include "Terrain.hpp"

void Terrain::drawTerrain(CaseTerrain &Case, float ratio, cameraDebug& camDebug){
    
    glm::mat4 MVMatrix;
    glm::mat4 MVPMatrix;
    glm::mat4 ProjMatrix;

    TextureMap currentTex;
    int idCurrentCase;

    MVMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(0, -1, -5));
    MVMatrix = camDebug.getViewMatrix() * MVMatrix;
    MVMatrix = glm::translate(MVMatrix, glm::vec3(-1, 0, 0)); //On se place
    ProjMatrix = glm::perspective(glm::radians(70.f), ratio, 0.1f, 100.f);
    m_formeProgramme.m_Program.use();

    std::cout << "START" << std::endl;
    for (int i=0; i<m_MatriceTerrain.getMatrice().size(); i++)
    {
        for (int j=0; j<m_MatriceTerrain.getMatrice().at(i).size(); j++)
        {
            idCurrentCase = m_MatriceTerrain.getMatrice().at(i).at(j);
            std::cout << idCurrentCase << std::endl;
            currentTex = m_textureIDManager.getTextureMatchingName(idCurrentCase);
            glUniform1i(m_formeProgramme.uTexture, currentTex.gl_texture);
            Case.drawCase();
            MVMatrix = glm::translate(MVMatrix, glm::vec3(-1, 0, 0)); //On décale de 1 vers la droite
            glUniformMatrix4fv(m_formeProgramme.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        }
        MVMatrix = glm::translate(MVMatrix, glm::vec3(3, 0, 1)); //On revient au début de la ligne d'après à gauche    }
    }
    std::cout << "STOP" << std::endl;
    
    

    // glUniformMatrix4fv(m_formeProgramme.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

    // Case.drawCase();

    // for (int i=0; i<10; i++){
    //   //  std::cout << ProjMatrix * MVMatrix << std::endl;
    //    // glBindTexture(GL_TEXTURE_2D, currentTex.idTexture);
    //     glUniform1i(m_formeProgramme.uTexture, currentTex.gl_texture);
    //     MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -1));
    //     glUniformMatrix4fv(m_formeProgramme.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        
    // }
}