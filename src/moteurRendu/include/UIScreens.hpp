#pragma once
#include "UI.hpp"
#include "HighScores.hpp"
#include <vector>
#include <string>

class TitleScreen {
    public:
    TitleScreen(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight);
    const bool close(); //Return true when game is started (titleScreen closed)
    const void draw() const;

    private:
    Message _title;
    Message _information;
    const Background _background;
    bool _open;
};

class DeadScreen {
    public:
    DeadScreen(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight);
    const bool close(); //Return true when game is started (titleScreen closed)
    const void open();
    const void draw() const;

    private:
    Message _title;
    Message _score;
    Message _information;
    const Background _background;
    bool _open;
};

class Menu;
class SubMenu {
    public:
    SubMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu);
    const void draw() ;
    const void open();
    const void close();
    const bool isOpen() const;

    private:
    Menu* _menu;
    const Background _background;
    ButtonReturn _return;
    bool _open;
};

class HighScoresMenu : public SubMenu {
    public:
    HighScoresMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu);
    const void updateScore(const int valueScore);
    const void draw();

    private:
    HighScores _highscores;
    std::vector<Message> _messages;
};

class SaveOrLoadMenu : public SubMenu {
    public: 
    SaveOrLoadMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu, std::string action);
    const void draw();
    const void open();
    const void close();

    private:
    ButtonSaveorLoadSlot _slot1;
    ButtonSaveorLoadSlot _slot2;
    ButtonSaveorLoadSlot _slot3;
    Message _titre;
    Message _feedback;
};

class Menu {
    public:
    Menu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
        const uint& windowWidth, const uint& windowHeight);
    const void draw();
    const void open();
    const void close();
    const void setStop(bool* stopGame);
    const void SubMenuOpen(const std::string& subMenuType);
    const void allSubMenusClose();
    const bool isOpen() const;
    void handleSDLEvent(const SDL_Event& e, bool gameStart);
    const void updateHighScores(const int valueScore);

    private:
    ButtonContinue _continue;
    ButtonStartAgain _startAgain;
    ButtonHighScore _highScores;
    ButtonSave _save;
    ButtonLoad _load;
    ButtonQuit _quit;
    Subject _clickListener;
    const Background _background;
    bool _open;

    HighScoresMenu _highScoresMenu;
    SaveOrLoadMenu _saveMenu;
    SaveOrLoadMenu _loadMenu;
};