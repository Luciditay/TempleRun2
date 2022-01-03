#include <includes.hpp>
#include "Matrice.hpp"
#include "unistd.h"
#include "Constants.hpp"
#include "RandomWorld.hpp"

using namespace glimac;

int main(int argc, char **argv)
{

    // Initialize SDL and open a window
    const float largeur = 800;
    const float hauteur = 600;
    SDLWindowManager windowManager(largeur, hauteur, "3D stylée");

    // Initialize glew for OpenGL3+ support
    glewInitialization();

    // Active profondeur
    glEnable(GL_DEPTH_TEST);
    // Active transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    (void)argc;

    // //Initialisation shaders
    FilePath applicationPath(argv[0]);
    ObjProgram objProgram(applicationPath);

    // Modele loading
    stbi_set_flip_vertically_on_load(true);
    // Model modelCharacter("assets/assetsTestAssimp/backpack.obj", applicationPath);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    const std::string matriceFile = "../map/fileTest.txt"; // On remonte de 1 dans l'arbo, car le .exe se trouve dans build, et que le contenu de test n'est pas copié (à modifier)
    std::vector<P_Texture> listeTexture;

    // const std::string modelCharacterPath = "../assets/assetsTestAssimp/backpack.obj";
    const std::string modelCharacterPath = "../assets/obj/pacman/pacman.obj";
    // const std::string modelEnemyPath = "../assets/obj/Handgun_obj.obj";
    const std::string modelEnemyPath = "../assets/obj/ghost/ghost.obj";
    const std::string VSPath = "shaders/case3D.vs.glsl";
    const std::string FSPath = "shaders/case3D.fs.glsl";

    P_Texture textureSol(TextureTypeId::SOL, "../assets/textures/pngwing.com.png");
    P_Texture textureSol1(TextureTypeId::SOL1, "../assets/textures/pngwing.com.png");
    P_Texture textureSol2(TextureTypeId::SOL2, "../assets/textures/textureMur.jpeg");
    P_Texture textureSol10(TextureTypeId::SOL10, "../assets/textures/pngwing.com.png");
    P_Texture textureTrou(TextureTypeId::TROU, "../assets/textures/boucheEgout.jpeg");
    P_Texture textureFautSeBaisser(TextureTypeId::FautSBaisser, "../assets/textures/triforce.png");

    listeTexture.push_back(textureSol);
    listeTexture.push_back(textureSol1);
    listeTexture.push_back(textureSol2);
    listeTexture.push_back(textureSol10);
    listeTexture.push_back(textureTrou);
    listeTexture.push_back(textureFautSeBaisser);

    Matrice matriceTerrain(matriceFile);
    TextureManager textureManager(listeTexture);
    Character Player(modelCharacterPath);

    TTF_Init();

    Render3D game(matriceTerrain, textureManager, applicationPath, VSPath, FSPath, modelCharacterPath, modelEnemyPath, windowManager, largeur, hauteur, "../assets/font/Roboto.ttf", "../assets/textures/background.png", "../assets/textures/pacman.jpg");

    game.playGame(largeur, hauteur);
    return 0;
}
