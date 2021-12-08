#pragma once
#include <string>
#include <iostream>
#include <glimac/Program.hpp>
#include <MoveMatrix.hpp>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <cstring> 

class ObjProgram {
    private:
 
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    glm::mat4 m_ProjMatrix;

    public: 
    ObjProgram(const glimac::FilePath& applicationPath);
    void setProjMatrix(glm::mat4 projMatrix);
    void sendMatrix(glm::mat4 MMatrixObj, glm::vec3 scale, glm::vec3 translate);

    glimac::Program m_Program;

    GLint uKd;
    GLint uKs;
    GLint uShininess;
    
    GLint uLightDir_vs; //vs=view space => on doit recevoir direction*viewmatrix
    GLint uLightIntensity;
    GLint uLightPos_vs;
    GLint uLightIntensityPos;

};
