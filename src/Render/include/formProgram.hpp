#pragma once
#include "glimac/Program.hpp"
#include <string>

using namespace glimac;

struct FormProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    FormProgram(const FilePath& applicationPath, const std::string &pathVertexShader, const std::string &pathFragShader):
        m_Program(loadProgram(applicationPath.dirPath() + pathVertexShader,
                              applicationPath.dirPath() + pathFragShader)) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};
