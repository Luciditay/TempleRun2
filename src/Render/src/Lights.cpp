#include "Lights.hpp"

Lights::Lights(glimac::Program& program, MoveMatrix* moveMatrix) {
    for (int indiceLightsDir = 0; indiceLightsDir <9; indiceLightsDir++) {
        m_dirLights.push_back(Light("Directional", indiceLightsDir, program, moveMatrix));
        m_dirLights[indiceLightsDir].sendUniformIntensity(glm::vec3(0.,0.,0.));
        m_dirLights[indiceLightsDir].sendUniformVec(glm::vec3(0.,0.,0.));
    }
    m_dirLights.shrink_to_fit();
    for (int indiceLightsPunct = 0; indiceLightsPunct <9; indiceLightsPunct++) {
        m_punctLights.push_back(Light("Directional", indiceLightsPunct, program, moveMatrix));
        m_punctLights[indiceLightsPunct].sendUniformIntensity(glm::vec3(0.,0.,0.));
        m_punctLights[indiceLightsPunct].sendUniformVec(glm::vec3(0.,0.,0.));
    }
    m_punctLights.shrink_to_fit();
}

// Lights::Lights(glimac::Program& program, MoveMatrix* moveMatrix) : 
//     m_moveMatrix(moveMatrix), m_nbLightsDir(0), m_currentIndiceLightDir(0), m_nbLightsPunct(0), m_currentIndiceLightPunct(0),
//     m_uLightsDirIntensity(glGetUniformLocation(program.getGLId(), "uLightsDirIntensity")),
//     m_uLightsDirection(glGetUniformLocation(program.getGLId(), "_uLightsDirection")),
//     m_uLightsPunctIntensity(glGetUniformLocation(program.getGLId(), "_uLightsPunctIntensity")),
//     m_uLightsPunctPosition(glGetUniformLocation(program.getGLId(), "_uLightsPunctPosition"))
//     {
// }

// bool inArray(float* array, glm::vec3 vector, int nbElements) {
//     for (int indice = 0; indice < (nbElements-1)*3; indice+=3) {
//         if (array[indice]==vector.x && array[indice+1]==vector.y && array[indice+2]==vector.z) {
//             return true;
//         }
//     } 
//     return false;
// }

// void Lights::newLight(std::string type, glm::vec3 intensity, glm::vec3 dirOrPos) {
//     if (type == "Directional") {
//         if(!inArray(m_LightsDirection, dirOrPos, m_nbLightsDir)) { //Si il n'y a pas déjà une light dans la même direction.
//             m_LightsDirIntensity[m_currentIndiceLightDir] = intensity.x;
//             m_LightsDirIntensity[m_currentIndiceLightDir+1] = intensity.y;
//             m_LightsDirIntensity[m_currentIndiceLightDir+2] = intensity.z;

//             m_LightsDirection[m_currentIndiceLightDir] = dirOrPos.x;
//             m_LightsDirection[m_currentIndiceLightDir+1] = dirOrPos.y;
//             m_LightsDirection[m_currentIndiceLightDir+2] = dirOrPos.z;

//             if (m_currentIndiceLightDir<27) { //On rajoute la nouvelle lumière en bout de tableau ou on remplace les lumières les plus anciennes.  
//                 m_currentIndiceLightDir+=3;
//             } else {
//                 m_currentIndiceLightDir = 0;
//             }
//             if ( m_nbLightsDir <10) {
//                 m_nbLightsDir++;
//             }
//         }
//     }
//     if (type == "Punctual") {
//         if(!inArray(m_LightsPunctPosition, dirOrPos, m_nbLightsPunct)) { //Si il n'y a pas déjà une light au même endroit.
//             m_LightsPunctIntensity[m_currentIndiceLightPunct] = intensity.x;
//             m_LightsPunctIntensity[m_currentIndiceLightPunct+1] = intensity.y;
//             m_LightsPunctIntensity[m_currentIndiceLightPunct+2] = intensity.z;

//             m_LightsPunctPosition[m_currentIndiceLightPunct] = dirOrPos.x;
//             m_LightsPunctPosition[m_currentIndiceLightPunct+1] = dirOrPos.y;
//             m_LightsPunctPosition[m_currentIndiceLightPunct+2] = dirOrPos.z;

//             if (m_currentIndiceLightPunct<27) { //On rajoute la nouvelle lumière en bout de tableau ou on remplace les lumières les plus anciennes.  
//                 m_currentIndiceLightPunct+=3;
//             } else {
//                 m_currentIndiceLightPunct = 0;
//             }
//             if ( m_nbLightsPunct <10) {
//                 m_nbLightsPunct++;
//             }
//         }
//     }
// }

// void Lights::sendUniformLights() {
//     glUniform3fv(m_uLightsDirIntensity, m_nbLightsDir*3, m_LightsDirIntensity);
//     glUniform3fv(m_uLightsDirection, m_nbLightsDir*3, m_LightsDirection);
//     glUniform3fv(m_uLightsPunctIntensity, m_nbLightsPunct*3, m_LightsPunctIntensity);
//     glUniform3fv(m_uLightsPunctPosition, m_nbLightsPunct*3, m_LightsPunctPosition);
// }
    








// void Light::sendUniformIntensity(glm::vec3 intensity) {
//    glm::vec4 newIntensity = glm::vec4(intensity, 0.);
//    glUniform3f(m_uLightIntensity, newIntensity.x, newIntensity.y, newIntensity.z);
// }

// void Light::sendUniformVec(glm::vec3 vector) {
//     glm::vec4 newVector;
//     if (m_type == "Directional") {
//         newVector = m_moveMatrix->getLightMVMatrix()*glm::vec4(vector, 0.);
//     } else {
//         newVector = glm::vec4(vector, 1.);
//     }
//     glUniform3f(m_uLightVec, newVector.x, newVector.y, newVector.z);
// }