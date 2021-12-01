#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/glm.hpp>
#include <cstddef>
#include <vector>

using namespace glimac;

class Vertex2DColor{
    public:
        glm::vec2 m_position;
        glm::vec3 m_color;
    
    Vertex2DColor(glm::vec2 position, glm::vec3 color) ;
    ~Vertex2DColor() = default;
};

Vertex2DColor::Vertex2DColor(glm::vec2 position, glm::vec3 color) 
    : m_position(position), m_color(color) {}


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl",
                              applicationPath.dirPath() + "shaders/triangle.fs.glsl");
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    const float nbTriangles = 40;
    const float DeuxPi = 2*glm::pi<float>();
    const float angle = DeuxPi/nbTriangles;

    std::vector<Vertex2DColor> vertices;
    
    for (int i=0; i<nbTriangles; i++){
        vertices.push_back(Vertex2DColor(glm::vec2(0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)));
        vertices.push_back(Vertex2DColor(glm::vec2(glm::cos(i*angle), glm::sin(i*angle)), 
                                         glm::vec3(0.f, 1.f, 0.f)));
        vertices.push_back(Vertex2DColor(glm::vec2(glm::cos((i+1)*angle), glm::sin((i+1)*angle)), 
                                         glm::vec3(0.f, 1.f, 0.f)));
    }

    glBufferData(GL_ARRAY_BUFFER, nbTriangles*3*sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(3); //const GLuint VERTEX_ATTR_POS = 0
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(3,
    2, GL_FLOAT, GL_FALSE,
    sizeof(Vertex2DColor), 
    0);

    glEnableVertexAttribArray(8); //const GLuint VERTEX_ATTR_POS = 0
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(8,
    3, GL_FLOAT, GL_FALSE,
    sizeof(Vertex2DColor), 
    (const GLvoid*) offsetof(Vertex2DColor, m_color));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, nbTriangles*3);
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
