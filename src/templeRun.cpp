#include <includes.hpp>


using namespace glimac;

struct Vertex3DUV{
    glm::vec3 position;
    glm::vec2 coordonneesTexture;

    Vertex3DUV(const glm::vec3 pos, const glm::vec2 texture) {
        position = pos;
        coordonneesTexture = texture;
    }

};

    struct MoonProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uMoonTexture;

    MoonProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uMoonTexture = glGetUniformLocation(m_Program.getGLId(), "uTextureMoon");
    }
    };

int main(int argc, char** argv) {
    
    // Initialize SDL and open a window
    const unsigned int largeur = 800;
    const unsigned int hauteur = 600;
    SDLWindowManager windowManager(largeur, hauteur, "3D stylée");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    //Active profondeur
    glEnable(GL_DEPTH_TEST);
    //Active transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Initialisation shaders
    FilePath applicationPath(argv[0]);
    // EarthProgram earthProgram(applicationPath);
    MoonProgram moonProgram(applicationPath);
    ObjProgram objProgram(applicationPath);

    //skybox1
    Skybox ourSkybox(applicationPath);


    //Chargement image
    std::vector<std::unique_ptr<Image>> ptrImages;
    ptrImages.push_back(loadImage("assets/textures/pacmanskin.jpg"));
    ptrImages.push_back(loadImage("assets/textures/labyrinth.png"));
    ptrImages.push_back(loadImage("assets/textures/CloudMap.jpg"));
      
    if(ptrImages[0] && ptrImages[1] && ptrImages[2]){
        std::cout << "ptrImages ok " << std::endl;
    }
    //Création texture objet : tableau de textures
    GLuint to[3];
    glGenTextures(3, &to[0]);

    //Bind texture Lune
    glBindTexture(GL_TEXTURE_2D, to[1]);
    //Envoie carte graphique
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,ptrImages[1]->getWidth(),ptrImages[1]->getHeight(), 0, GL_RGBA, GL_FLOAT, ptrImages[1]->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Débind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_DEPTH_TEST);

    //HighScores
    TTF_Init();
    const char* fontPath = "assets/font/Roboto.ttf";
    ScoreCounter score(applicationPath, largeur, hauteur);
    int compteur = 0;
    //Menus
    const char* imagePath = "assets/textures/background.jpg";
    const char* imagePath2 = "assets/textures/pacman.jpg";
    Menu menu(imagePath, fontPath, 30, applicationPath, largeur, hauteur);
    TitleScreen titleScreen(imagePath2, fontPath, 100, applicationPath, largeur, hauteur);
    DeadScreen deadScreen(imagePath2, fontPath, 100, applicationPath, largeur, hauteur);
    //Camera
    Camera maCamera(-30., M_PI/6.,0.);
    //Movements
    Character character;
    MoveMatrix moveMatrix(&maCamera, &character);

    //Chargement modèle
    stbi_set_flip_vertically_on_load(true);
    Model ourModel("assets/assetsTestAssimp/backpack.obj");

    Collectibles collectibles(&objProgram, &moveMatrix, &character, &score);
    collectibles.addCollectible(glm::vec2(10.,-100.), "Bonus", true);
    collectibles.addCollectible(glm::vec2(0.,-100.), "Coin", false);
    collectibles.addCollectible(glm::vec2(15.,10.), "Coin", true);

    Light lumiereVerte("Directional", 0, objProgram.m_Program, &moveMatrix);
    Light lumiereBlanche("Directional", 1, objProgram.m_Program, &moveMatrix);
    float enemySpeed = 0.1;
    float distanceEnemy = 100;
    bool looser = false;
    bool pause = true;

    int currentTime = 0;
    int previousTime = 0;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TEXTURE = 2;
   
    //Sol
    GLuint vboSOL;  
    glGenBuffers(1,&vboSOL);
    //Bind du vbo
    glBindBuffer(GL_ARRAY_BUFFER, vboSOL);
    //Remplissage du vbo
    Vertex3DUV vertices[] = {
        Vertex3DUV(glm::vec3(-1,0, 1), glm::vec2(0,0)),
        Vertex3DUV(glm::vec3(-1,0, -1), glm::vec2(0,1)),
        Vertex3DUV(glm::vec3(1,0, -1), glm::vec2(1,1)),
        Vertex3DUV(glm::vec3(1,0, 1), glm::vec2(1,0)),
    };
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(Vertex3DUV), vertices, GL_STATIC_DRAW);
    //Débind du vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Bind du ibo
    GLuint iboSOL;  
    glGenBuffers(1,&iboSOL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboSOL);
    //Tableau d'indices
    uint32_t indices[] = {
        0, 1, 2, 0, 2, 3
    };
    //Remplissage du ibo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (6)*sizeof(uint32_t), indices, GL_STATIC_DRAW);
    //Débind du ibo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //Bind
    GLuint vaoSOL;  
    glGenVertexArrays(1, &vaoSOL);
    glBindVertexArray(vaoSOL);
    //Bind du ibo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboSOL);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    //Spécification des attributs de vertex (bind et débind vbo)
    glBindBuffer(GL_ARRAY_BUFFER, vboSOL);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*) (offsetof(Vertex3DUV, position)));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*) (offsetof(Vertex3DUV, coordonneesTexture)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //débind vbo
    glBindVertexArray(0);

    //skybox 
    ourSkybox.fillSkyVao();
    ourSkybox.mapTexture();

    bool done = false; 
    bool gameStart = false;
    menu.setStop(&done);
    SDL_EnableKeyRepeat(10,10);
    while(!done) {

        //update current time
        currentTime = SDL_GetTicks();
        if(currentTime - previousTime > 30) {

            // Event loop:
            SDL_Event e;
            while(windowManager.pollEvent(e)) {

            
            if (!pause) {
                maCamera.handleSDLEvent(e);
                character.handleSDLEvent(e);
            }
            menu.handleSDLEvent(e, gameStart);
        
            if(e.type == SDL_MOUSEBUTTONUP) {
                gameStart = titleScreen.close();
                if (looser) {
                    deadScreen.close();
                    character.reset();
                    looser = false;
                    pause = false;
                    compteur = 0;
                    score.resetItemsAndDistance();
                    score.update();
                }
            }

            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            }

            /*********************************
             * HERE SHOULD COME THE RENDERING CODE
             *********************************/
            if(!pause) {
                glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), float(largeur)/float(hauteur), 0.1f, 1000.f);
                objProgram.setProjMatrix(ProjMatrix);
                
                character.reactToInputs();
                
                moveMatrix.computeAllMatrix();
                glm::mat4 MVMatrix = moveMatrix.getViewMatrix();
                glm::mat4 MVPMatrix = ProjMatrix*MVMatrix;
                glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

                //Nettoyage de la fenêtre
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

                //Dessin sol
                moonProgram.m_Program.use();
                glBindVertexArray(vaoSOL);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, to[1]);
                glUniform1i(moonProgram.uMoonTexture, 0);
                glm::mat4 MVMatrixLune = moveMatrix.getWorldMVMatrix();
                glm::mat4 MVPMatrixLune = ProjMatrix*MVMatrixLune;
                    //Envoi des matrices
                glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrixLune));
                glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrixLune));
                glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);


                //Objet 1 (char)
                objProgram.m_Program.use();
                //lumière
                lumiereVerte.sendUniformIntensity(glm::vec3(1.,1.,0.));
                lumiereVerte.sendUniformVec(glm::vec3(0.,1.,-1.));
                lumiereBlanche.sendUniformIntensity(glm::vec3(1.,1.,1.));
                lumiereBlanche.sendUniformVec(glm::vec3(0.,-1.,1.));
                // glm::vec4 dirLight = glm::rotate(moveMatrix.getLightMVMatrix(), float(M_PI/4.), glm::vec3(0.,0.,1.))*glm::vec4(1.,1.,1.,0.);
                // glm::vec4 dirLight = moveMatrix.getLightMVMatrix() * glm::vec4(0.,0.,1.,0.);
                // glUniform3f(objProgram.uLightDir_vs, dirLight.x, dirLight.y, dirLight.z);
                // glUniform3f(objProgram.uLightIntensity, 1.,1., 1.);
                glm::vec4 posLight = moveMatrix.getWorldMVMatrix()*glm::vec4(0.,0.02,0.,1.);
                glUniform3f(objProgram.uLightPos_vs, posLight.x, posLight.y, posLight.z);
                glUniform3f(objProgram.uLightIntensityPos, 1.,0., 0.);
                // matériaux
                glUniform3f(objProgram.uKd, 2.,2.,2.);
                glUniform3f(objProgram.uKs, 1.,1.,1.);
                glUniform1f(objProgram.uShininess, 50.);
                //Matrices        
                objProgram.sendMatrix(moveMatrix.getCharMVMatrix(), glm::vec3(4.,4.,4.), glm::vec3(0.,7.,0.));
                ourModel.Draw(objProgram.m_Program);

                //Objet2 (celui qui reste fixe au début, mais il a une light ponctuelle rouge sur lui)
                objProgram.sendMatrix(moveMatrix.getWorldMVMatrix(), glm::vec3(0.01,0.01,0.01), glm::vec3(0.,0.02,0.));
                ourModel.Draw(objProgram.m_Program);

               
                //Objet3 (on va dire c'est le méchant mouahaha)
                objProgram.sendMatrix(moveMatrix.getEnemyMVMatrix(), glm::vec3(4.,4.,4.), glm::vec3(1,1,1));
                
                ourModel.Draw(objProgram.m_Program); 

               collectibles.draw();

                ourSkybox.draw(moveMatrix,ProjMatrix);
            }
            
            if (character.isDead()) {
                //perdu
                deadScreen.open();
                deadScreen.draw();
                deadScreen.updateScore(score.getTotalScore());
                looser = true;
                pause = true;
                menu.updateHighScores(score.getTotalScore());
            }

            //Dessin de l'UI
            if (!pause && !looser) {
                compteur+=1;
                if (compteur >= 10) {
                    score.increaseDistance();
                    compteur = 0;
                }
                score.update();
                score.draw();
            }
            if (gameStart) {
                menu.draw();
            }
            titleScreen.draw();

            if (menu.someMenuIsOpen()) {
                pause=true;
            } else {
                pause = false;
            }
            if (menu.shouldStartAgain()) {
                character.reset();
                compteur = 0;
                score.resetItemsAndDistance();
                score.update();
            }

            // Update the display
            windowManager.swapBuffers();

            //update previous time
            previousTime = currentTime;
        }
    }

    TTF_Quit();

    //Libération des ressources
    glDeleteTextures(3, &to[0]);

    return EXIT_SUCCESS;
}
