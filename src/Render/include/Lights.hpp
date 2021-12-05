#pragma once
#include <string>
#include <iostream>
#include <glimac/Program.hpp>
#include <MoveMatrix.hpp>
#include <glimac/glm.hpp>
#include <cstring> 

class Lights {
    public:
    Lights(glimac::Program& program, MoveMatrix* moveMatrix);
    void newLight(std::string type, glm::vec3 intensity, glm::vec3 dirOrPos);
    void sendUniformLights();
    
    private:
    const GLint m_uLightsDirIntensity;
    const GLint m_uLightsDirection; 
    const GLint m_uLightsPunctIntensity;
    const GLint m_uLightsPunctPosition; 

    float m_LightsDirIntensity[30];
    float m_LightsDirection[30]; 
    float m_LightsPunctIntensity[30];
    float m_LightsPunctPosition[30]; 

    int m_nbLightsDir;
    int m_currentIndiceLightDir;
    int m_nbLightsPunct;
    int m_currentIndiceLightPunct;

    MoveMatrix* m_moveMatrix;
};
