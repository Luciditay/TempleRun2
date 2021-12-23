#include "Skybox.hpp"

Skybox::Skybox(const glimac::FilePath &filePath)
{

    tabTex = {"../assets/textures/skybox/right.jpg",
              "../assets/textures/skybox/left.jpg",
              "../assets/textures/skybox/bottom.jpg",
              "../assets/textures/skybox/top.jpg",
              "../assets/textures/skybox/front.jpg",
              "../assets/textures/skybox/back.jpg"};

    _program = glimac::loadProgram(filePath.dirPath() + "shaders/skyBox.vs.glsl",
                                   filePath.dirPath() + "shaders/skyBox.fs.glsl");
    _projection = glGetUniformLocation(_program.getGLId(), "projection");
    _view = glGetUniformLocation(_program.getGLId(), "view");
    _skybox = glGetUniformLocation(_program.getGLId(), "skybox");

    fillSkyVao();
    mapTexture();
}

unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

const void Skybox::fillSkyVao()
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tabVert), &tabVert, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

const void Skybox::mapTexture()
{
    cubemapTexture = loadCubemap(tabTex);
}

const void Skybox::draw(glm::mat4 view, glm::mat4 proj)
{

    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    _program.use();
    glm::mat4 MVMatrix = glm::mat4(glm::mat3(view)); // remove translation from the view matrix
    glUniformMatrix4fv(_view, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(_projection, 1, GL_FALSE, glm::value_ptr(proj));

    glBindVertexArray(_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}
