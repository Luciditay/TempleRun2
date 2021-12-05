#include "Light.hpp"

Light::Light(std::string type, int id, glimac::Program& program, MoveMatrix* moveMatrix) : m_type(type), m_id(id), m_moveMatrix(moveMatrix),
    m_uLightVec(glGetUniformLocation(program.getGLId(), ("uLightVec"+type+std::to_string(id)).c_str())),
    m_uLightIntensity(glGetUniformLocation(program.getGLId(), ("uLightIntensity"+type+std::to_string(id)).c_str())) {
        std::cout << "uLightVec"+type+std::to_string(id) << std::endl;
}

void Light::sendUniformIntensity(glm::vec3 intensity) {
   glm::vec4 newIntensity = glm::vec4(intensity, 0.);
   glUniform3f(m_uLightIntensity, newIntensity.x, newIntensity.y, newIntensity.z);
}

void Light::sendUniformVec(glm::vec3 vector) {
    glm::vec4 newVector;
    if (m_type == "Directional") {
        newVector = m_moveMatrix->getLightMVMatrix()*glm::vec4(vector, 0.);
    } else {
        newVector = glm::vec4(vector, 1.);
    }
    glUniform3f(m_uLightVec, newVector.x, newVector.y, newVector.z);
}