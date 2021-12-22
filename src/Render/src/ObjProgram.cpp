#include "ObjProgram.hpp"

ObjProgram::ObjProgram(const glimac::FilePath &applicationPath) : m_Program(glimac::loadProgram(applicationPath.dirPath() + "shaders/obj.vs.glsl",
                                                                                                applicationPath.dirPath() + "shaders/obj.fs.glsl"))

{
    uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
    uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
    uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
    uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
    uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
    uLightPos_vs = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
    uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    uLightIntensityPos = glGetUniformLocation(m_Program.getGLId(), "uLightIntensityPos");
    // m_ProjMatrix rojMatrix = glm::perspective(glm::radians(70.f), float(largeur) / float(hauteur), 0.1f, 1000.f);
    //                 objProgram.setProjMatrix(ProjMatrix);
}

void ObjProgram::setProjMatrix(glm::mat4 projMatrix)
{
    m_ProjMatrix = projMatrix;
}

void ObjProgram::sendMatrix(glm::mat4 MVPMatrixObj)
{
    glm::mat4 NormalMatrixObj = glm::transpose(glm::inverse(MVPMatrixObj));
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrixObj));
    //  glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrixObj));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrixObj));
}