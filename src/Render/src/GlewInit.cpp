#include "GlewInit.hpp"
#include "GL/glew.h"
#include "iostream"
#include <cstdlib>
    
void glewInitialization(){    
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        exit(EXIT_FAILURE);
    }
}
