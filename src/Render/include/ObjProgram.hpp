#pragma once
#include <string>
#include <iostream>
#include <glimac/Program.hpp>
//#include <MoveMatrix.hpp>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <cstring>

/// \struct ObjProgram
/// \brief shader program to render 3D model objects
struct ObjProgram
{
private:
    GLint uMVPMatrix;       /*!< id of uniform variable, to send the MVP Matrix */
    GLint uMVMatrix;        /*!< id of uniform variable, to send the MV Matrix */
    GLint uNormalMatrix;    /*!< id of uniform variable, to send the Normal Matrix */
    glm::mat4 m_ProjMatrix; /*!< projection matrix */

public:
    /// \brief constructor
    /// \param applicationPath : path of the application
    ObjProgram(const glimac::FilePath &applicationPath);
    /// \brief setter for m_ProjMatrix
    /// \param projMatrix : the new projection matrix
    void setProjMatrix(glm::mat4 projMatrix);
    /// \brief send uniform matrix to the shader
    /// \param MMatrixObj : model matrix of the 3D object
    /// \param scale : scale to be applied to the 3D object
    /// \param translate : translation to be applied to the 3D object
    void sendMatrix(glm::mat4 MMatrixObj);

    glimac::Program m_Program; /*!< program */

    GLint uKd;        /*!<  id of uniform variable, diffuse coef of material */
    GLint uKs;        /*!<  id of uniform variable, glossy coef of material */
    GLint uShininess; /*!<  id of uniform variable, shininess coef of material */

    GLint uLightDir_vs;       //*!< direction of directional light (in view space) */
    GLint uLightIntensity;    //*!< intensity of directional light  */
    GLint uLightPos_vs;       //*!< position of punctual light (in view space) */
    GLint uLightIntensityPos; //*!< intensity of punctual light*/
};
