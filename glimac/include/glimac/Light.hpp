#pragma once
#include <string>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/MoveMatrix.hpp>
#include <glimac/glm.hpp>
#include <cstring> 

class Light {
    public:
    Light(std::string type, int id, glimac::Program& program, MoveMatrix* moveMatrix);
    void sendUniformIntensity(glm::vec3 intensity);
    void sendUniformVec(glm::vec3 vector);
    
    private:
    const GLint m_uLightIntensity;
    const GLint m_uLightVec; // direction or position
    
    const std::string m_type; //"Directional" or "Punctual"
    const int m_id; //to identify the light in the shader : name is type+id

    MoveMatrix* m_moveMatrix;
};
