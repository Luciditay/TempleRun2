// #include <glimac/includes.hpp>


// using namespace glimac;

// struct Vertex3DUV{
//     glm::vec3 position;
//     glm::vec2 coordonneesTexture;

//     Vertex3DUV(const glm::vec3 pos, const glm::vec2 texture) {
//         position = pos;
//         coordonneesTexture = texture;
//     }

// };

// int main(int argc, char const *argv[])
// {
//     /* code */
//     return 0;
// }

// int main(int argc, char** argv) {
    
//     // Initialize SDL and open a window
//     const unsigned int largeur = 800;
//     const unsigned int hauteur = 600;
//     SDLWindowManager windowManager(largeur, hauteur, "3D stylée");

//     // Initialize glew for OpenGL3+ support
//     GLenum glewInitError = glewInit();
//     if(GLEW_OK != glewInitError) {
//         std::cerr << glewGetErrorString(glewInitError) << std::endl;
//         return EXIT_FAILURE;
//     }

//     std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
//     std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

//     //Active profondeur
//     glEnable(GL_DEPTH_TEST);
//     //Active transparence
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     bool done = false; 
//     bool gameStart = false;
//     SDL_EnableKeyRepeat(10,10);
//     while(!done) {
//         // Event loop:
//         SDL_Event e;
//         while(windowManager.pollEvent(e)) 
//         {

//         if(e.type == SDL_QUIT) {
//             done = true; // Leave the loop after this iteration
//         }
//         }

//         /*********************************
//          * HERE SHOULD COME THE RENDERING CODE
//          *********************************/
       
//         //Nettoyage de la fenêtre
//         glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

//         // Dessin de la TERRE

     

//         // Update the display
//         windowManager.swapBuffers();
//     }

//     TTF_Quit();

//     //Libération des ressources
   
//     return EXIT_SUCCESS;
// }
