#include <includes.hpp>
#include "Matrice.hpp"
#include "unistd.h"

using namespace glimac;

int main(int argc, char** argv) {
    
    // Initialize SDL and open a window
    const float largeur = 800;
    const float hauteur = 600;
    SDLWindowManager windowManager(largeur, hauteur, "3D stylée");

    // Initialize glew for OpenGL3+ support
    glewInitialization();

    //Active profondeur
    glEnable(GL_DEPTH_TEST);
    //Active transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // //Initialisation shaders
   
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    Matrice matTest("../test/fileTest.txt"); //On remonte de 1 dans l'arbo, car le .exe se trouve dans build, et que le contenu de test n'est pas copié (à modifier)


    FilePath applicationPath(argv[0]);
    
    const int TEXTURE_SOL = 0;
    P_Texture textureSol(TEXTURE_SOL, "../assets/textures/dirt.png"); 
    TextureManager textManager(textureSol);

    CaseTerrain CaseTest1(applicationPath, "shaders/case3D.vs.glsl", "shaders/case3D.fs.glsl");

    CaseTest1.loadCase();

    constexpr GLuint VERTEX_ATTR_POSITION = 0;
    constexpr GLuint VERTEX_ATTR_TEXTURE = 2;

    cameraDebug camDebug;

    glm::mat4 MVMatrix;
    glm::mat4 MVPMatrix;
    glm::mat4 ProjMatrix;
   
    bool done = false; 
    bool gameStart = false;
    SDL_EnableKeyRepeat(10,10);
    while(!done) {

         //Nettoyage de la fenêtre
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        //update current time
            // Event loop:
            SDL_Event e;
            while(windowManager.pollEvent(e)) {

                camDebug.reactSDLEvents(e);

            
                if(e.type == SDL_QUIT) {
                    done = true; // Leave the loop after this iteration
                }
            }

            /*********************************
             * HERE SHOULD COME THE RENDERING CODE
             *********************************/
            
            MVMatrix = glm::translate(glm::mat4{1.f}, glm::vec3(0, 0, -5));
            //MVMatrix = glm::scale(MVMatrix, glm::vec3(20, 20, 20));

            MVMatrix =   camDebug.getViewMatrix() *MVMatrix;
            ProjMatrix = glm::perspective(glm::radians(70.f), largeur/hauteur, 0.1f, 100.f);

            CaseTest1.m_drawer.m_Program.use();


            //glUniform4fv(caseProgramme.uMVMatrix, 1, glm::value_ptr(glm::mat4{1.f}));
            glUniformMatrix4fv(CaseTest1.m_drawer.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

            CaseTest1.drawCase();

            for (int i=0; i<10; i++){
                
                MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -1));
                glUniformMatrix4fv(CaseTest1.m_drawer.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                CaseTest1.drawCase();

            }
                
              
            // Update the display
            windowManager.swapBuffers();

            //update previous time
        }
    

   // TTF_Quit();

    //Libération des ressources
    //glDeleteTextures(1, &t1);

    return EXIT_SUCCESS;
}
