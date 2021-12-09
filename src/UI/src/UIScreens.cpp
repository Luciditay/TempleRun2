#include "UIScreens.hpp"

//Ecran titre 

TitleScreen::TitleScreen(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight):
    _title("GAME", {255,255,255}, fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., windowHeight/2., true),
    _information("Click anywhere to play.", {180,180,180}, fontPath, size/4, filePath, windowWidth, windowHeight, 20, 20, false),
    _background(imagePath, filePath),
    _open(true){
}

const bool TitleScreen::close() {
        _open = false;
        return true;
}

const void TitleScreen::draw() const {
    if(_open) {
     _background.draw();
     _title.draw();
    _information.draw();
    }
}

//Ecran fin

DeadScreen::DeadScreen(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight):
    _title("Dead. Sorry.", {255,255,255}, fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., windowHeight/2., true),
    _score(("Score : "+std::to_string(0)).c_str(), {255,255,255}, fontPath, size/2, filePath, windowWidth, windowHeight, windowWidth/2., (2.*windowHeight)/3., true),
    _information("Click anywhere to play again.", {180,180,180}, fontPath, size/4, filePath, windowWidth, windowHeight, 20, 20, false),
    _background(imagePath, filePath),
    _open(true){
}

const bool DeadScreen::close() {
        _open = false;
        return true;
}

const void DeadScreen::open() {
        _open = true;
}

const void DeadScreen::draw() const {
    if(_open) {
     _background.draw();
     _title.draw();
     _score.draw();
    _information.draw();
    }
}

//Menu

Menu::Menu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight) :
    _continue(fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., windowHeight/7., true, this),
    _startAgain(fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., (windowHeight/7.)*2, true, this),
    _highScores(fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., (windowHeight/7.)*3, true, this),
    _save(fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., (windowHeight/7.)*4, true, this),
    _load(fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., (windowHeight/7.)*5, true, this),
    _quit(fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., (windowHeight/7.)*6, true, this),
    _background(imagePath, filePath),
    _open(false),
    _highScoresMenu(imagePath, fontPath, size, filePath, windowWidth, windowHeight, _clickListener, this),
    _saveMenu(imagePath, fontPath, size, filePath, windowWidth, windowHeight, _clickListener, this, "Save"),
    _loadMenu(imagePath, fontPath, size, filePath, windowWidth, windowHeight, _clickListener, this, "Load")
    {
        _clickListener.attach(_continue);
        _clickListener.attach(_startAgain);
        _clickListener.attach(_highScores);
        _clickListener.attach(_save);
        _clickListener.attach(_load);
        _clickListener.attach(_quit);
    }

const void Menu::draw() {
    if(_open) {
        _background.draw();
        _continue.draw();
        _startAgain.draw();
        _highScores.draw();
        _save.draw();
        _load.draw();
        _quit.draw();
    }
     else if (_highScoresMenu.isOpen()) {
        _highScoresMenu.draw();
    }
    else if (_saveMenu.isOpen()) {
        _saveMenu.draw();
    }
    else if (_loadMenu.isOpen()) {
        _loadMenu.draw();
    }
}

const void Menu::open() {
    SDL_EnableKeyRepeat(0,0);
    _open = true;
    _continue.enable();
    _startAgain.enable();
    _highScores.enable();
    _save.enable();
    _load.enable();
    _quit.enable();
    SDL_EnableKeyRepeat(10,10);
}

const void Menu::close() {
    SDL_EnableKeyRepeat(0,0);
    _open = false;
    _continue.enable();
    _startAgain.enable();
    _highScores.enable();
    _save.enable();
    _load.enable();
    _quit.enable();
    SDL_EnableKeyRepeat(10,10);
}

const void Menu::setStop(bool* stopGame) {
    _quit.setStop(stopGame);
}

const bool Menu::isOpen() const {
    return _open;
}

const void Menu::SubMenuOpen(const std::string& subMenuType) {
    if (subMenuType == "Highscores") {
        _highScoresMenu.open();
    } if (subMenuType == "Save") {
        _saveMenu.open();
    } if (subMenuType == "Load") {
        _loadMenu.open();
    }
}

const void Menu::allSubMenusClose() {
     _highScoresMenu.close();
     _saveMenu.close();
     _loadMenu.close();
}

void Menu::handleSDLEvent(const SDL_Event& e, bool gameStart) {
    if(e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                if(gameStart) {
                    allSubMenusClose();
                    if(isOpen()) {
                        close();
                    } else {
                        open();
                    }
                }
            }
        }

        if(e.type == SDL_MOUSEBUTTONUP) {
            _clickListener.notify();
        }
}

const void Menu::updateHighScores(const int valueScore) {
    _highScoresMenu.updateScore(valueScore);
}

SubMenu::SubMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
                const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu) :
    _return(fontPath, size, filePath, windowWidth, windowHeight, windowWidth-size*4, windowHeight - size*2, true, menu),
    _background(imagePath, filePath),
    _open(false), 
    _menu(menu) {
        clickListener.attach(_return);
}

const void SubMenu::draw() {
    if(_open) {
    _background.draw();
    _return.draw();
    }
}

const void SubMenu::open() {
    SDL_EnableKeyRepeat(0,0);
    _open = true;
    _return.enable();
    SDL_EnableKeyRepeat(10,10);
}


const void SubMenu::close() {
    SDL_EnableKeyRepeat(0,0);
    _open = false;
    _return.disable();
    SDL_EnableKeyRepeat(10,10);
}

const bool SubMenu::isOpen() const{
    return _open;
}

HighScoresMenu::HighScoresMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu) : 
    SubMenu(imagePath, fontPath, size, filePath, windowWidth, windowHeight, clickListener, menu),
    _highscores(filePath) {
        Message titre("High Scores", {255,0,0}, fontPath, size*1.5, filePath, windowWidth, windowHeight, windowWidth/2., (windowHeight/12.), true);
        _messages.push_back(std::move(titre));
        for (int i = 0; i < _highscores.getSize(); i++) {
            Message score(std::to_string(_highscores.getValue(i)).c_str(), {230,230,230}, fontPath, size, filePath, 
                            windowWidth, windowHeight, windowWidth/2., (windowHeight/12.)*(i+2), true);
            _messages.push_back(std::move(score));
            }
}

const void HighScoresMenu::updateScore(const int valueScore) {
    _highscores.newScore(valueScore);
    _highscores.save();
    _highscores.load();    
    
    int i = 0;
    for (auto it = _messages.begin()+1; it != _messages.end(); ++it) {
        it->update(std::to_string(_highscores.getValue(i)).c_str());
        i++;
    }
}

const void HighScoresMenu::draw() {
    SubMenu::draw();
    for (int i = 0; i < _messages.size(); i++) {
        _messages[i].draw();
    }
}
 
SaveOrLoadMenu::SaveOrLoadMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu, std::string action) :
    SubMenu(imagePath, fontPath, size, filePath, windowWidth, windowHeight, clickListener, menu),
    _feedback("Select a memory slot.", {255,0,0}, fontPath, size, filePath, windowWidth, windowHeight, windowWidth/2., windowHeight/3, true),
    _slot1(fontPath, size*1.5, filePath, windowWidth, windowHeight, windowWidth/4, windowHeight/2, true, 1, action, &_feedback),
    _slot2(fontPath, size*1.5, filePath, windowWidth, windowHeight, (windowWidth/4)*2, windowHeight/2, true, 2, action, &_feedback),
    _slot3(fontPath, size*1.5, filePath, windowWidth, windowHeight, (windowWidth/4)*3, windowHeight/2, true, 3, action, &_feedback),
    _titre((action).c_str(), {255,0,0}, fontPath, size*1.5, filePath, windowWidth, windowHeight, windowWidth/2., windowHeight/4, true) {
        clickListener.attach(_slot1);
        clickListener.attach(_slot2);
        clickListener.attach(_slot3);
}

const void SaveOrLoadMenu::draw() {
    SubMenu::draw();
    _slot1.draw();
    _slot2.draw();
    _slot3.draw();
    _titre.draw();
    _feedback.draw();
}

const void SaveOrLoadMenu::open() {
    SubMenu::open();
    SDL_EnableKeyRepeat(0,0);
    _slot1.enable();
    _slot2.enable();
    _slot3.enable();
    SDL_EnableKeyRepeat(10,10);
}

const void SaveOrLoadMenu::close() {
    SubMenu::close();
    SDL_EnableKeyRepeat(0,0);
    _slot1.disable();
    _slot2.disable();
    _slot3.disable();
    _feedback.update("Select a memory slot.");
    SDL_EnableKeyRepeat(10,10);
}