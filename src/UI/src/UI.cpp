#include "UI.hpp"
#include "UIScreens.hpp"
#include <iostream>

// Score

ScoreCounter::ScoreCounter(const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight) : _distance(0), _items(0), _message("0", {255, 255, 255, 255}, "../assets/font/Roboto.ttf",
                                                                                                                                                    20, filePath, windowWidth, windowHeight, 10, 10, false)
{
}

void ScoreCounter::update()
{
    std::string distance = std::to_string(_distance);
    std::string items = std::to_string(_items);
    _message.update(("Distance : " + distance + " Items : " + items).c_str());
}

void ScoreCounter::increaseDistance()
{
    _distance++;
}

void ScoreCounter::increaseItems()
{
    _items++;
}

void ScoreCounter::resetItemsAndDistance()
{
    _items = 0;
    _distance = 0;
}

void ScoreCounter::draw() const
{
    _message.draw();
}

int ScoreCounter::getTotalScore()
{
    return _items + _distance;
}
int ScoreCounter::getDist()
{
    return _distance;
}

int ScoreCounter::getItems()
{
    return _items;
}
void ScoreCounter::setDist(int dist)
{

    _distance = dist;
}
void ScoreCounter::setItems(int items)
{
    _items = items;
}
// Image arrière plan

Background::Background(const char *imagePath, const glimac::FilePath &filePath) : _rect(filePath)
{

    // Chargement image
    std::unique_ptr<glimac::Image> ptrImage = glimac::loadImage(imagePath);
    if (ptrImage)
    {
    }
    // Création texture objet
    glGenTextures(1, &_texture);
    // Bind texture
    glBindTexture(GL_TEXTURE_2D, _texture);
    // Envoie carte graphique
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ptrImage->getWidth(), ptrImage->getHeight(), 0, GL_RGBA, GL_FLOAT, ptrImage->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Débind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

Background::~Background()
{
    glDeleteTextures(1, &_texture);
}

void Background::draw() const
{
    _rect.draw(_texture, 1., 1., 0., 0.);
}

// Bouton

Button::Button(const char *text, const char *fontPath, const int &size,
               const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
               const int &positionXPixels, const int &positionYPixels, const bool &middle)
    : _currentLabel(&_label),
      _label(text, {255, 255, 255, 255}, fontPath, size, filePath, windowWidth, windowHeight, positionXPixels, positionYPixels, middle),
      _labelHover(text, {255, 0, 0, 255}, fontPath, size * 1.5, filePath, windowWidth, windowHeight, positionXPixels, positionYPixels, middle),
      _enable(false)
{
}

bool Button::isHover()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int posYPixels = _label.getPosYPixels();
    int posXPixels = _label.getPosXPixels();
    int widthPixels = _label.getWidthPixels();
    int heightPixels = _label.getHeightPixels();

    if (mouseX >= posXPixels && mouseX <= posXPixels + widthPixels &&
        mouseY >= posYPixels && mouseY <= posYPixels + heightPixels)
    {
        _currentLabel = &_labelHover;
        return true;
    }
    else
    {
        _currentLabel = &_label;
        return false;
    }
}

void Button::draw()
{
    isHover();
    _currentLabel->draw();
}

void Button::enable()
{
    _enable = true;
}

void Button::disable()
{
    _enable = false;
}

// Différents boutons

ButtonMenu::ButtonMenu(const char *text, const char *fontPath, const int &size,
                       const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
                       const int &positionXPixels, const int &positionYPixels, const bool &middle, Menu *menu) : Button(text, fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                        positionXPixels, positionYPixels, middle),
                                                                                                                 _menu(menu)
{
}

void ButtonContinue::update()
{
    if (isHover() && _enable)
    {
        _menu->close();
    }
}

ButtonContinue::ButtonContinue(const char *fontPath, const int &size,
                               const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
                               const int &positionXPixels, const int &positionYPixels, const bool &middle, Menu *menu) : ButtonMenu("Continue", fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                                    positionXPixels, positionYPixels, middle, menu)
{
}

void ButtonStartAgain::update()
{
    if (isHover() && _enable)
    {
        _menu->startAgainTrue();
        _menu->close();
    }
}

ButtonStartAgain::ButtonStartAgain(const char *fontPath, const int &size,
                                   const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
                                   const int &positionXPixels, const int &positionYPixels, const bool &middle, Menu *menu) : ButtonMenu("Start Again", fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                                        positionXPixels, positionYPixels, middle, menu)
{
}

void ButtonHighScore::update()
{
    if (isHover() && _enable)
    {
        _menu->close();
        _menu->SubMenuOpen("Highscores");
    }
}

ButtonHighScore::ButtonHighScore(const char *fontPath, const int &size,
                                 const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
                                 const int &positionXPixels, const int &positionYPixels, const bool &middle, Menu *menu) : ButtonMenu("High Scores", fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                                      positionXPixels, positionYPixels, middle, menu)
{
}

void ButtonSave::update()
{
    if (isHover() && _enable)
    {
        _menu->close();
        _menu->SubMenuOpen("Save");
    }
}

ButtonSave::ButtonSave(const char *fontPath, const int &size,
                       const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
                       const int &positionXPixels, const int &positionYPixels, const bool &middle, Menu *menu) : ButtonMenu("Save", fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                            positionXPixels, positionYPixels, middle, menu)
{
}

void ButtonLoad::update()
{
    if (isHover() && _enable)
    {
        _menu->close();
        _menu->SubMenuOpen("Load");
    }
}

ButtonLoad::ButtonLoad(const char *fontPath, const int &size,
                       const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
                       const int &positionXPixels, const int &positionYPixels, const bool &middle, Menu *menu) : ButtonMenu("Load", fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                            positionXPixels, positionYPixels, middle, menu)
{
}

void ButtonQuit::update()
{
    if (isHover() && _enable)
    {
        stopGame();
    }
}

ButtonQuit::ButtonQuit(const char *fontPath, const int &size,
                       const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
                       const int &positionXPixels, const int &positionYPixels, const bool &middle, Menu *menu) : ButtonMenu("Quit", fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                            positionXPixels, positionYPixels, middle, menu),
                                                                                                                 _stopGame(nullptr)
{
}

void ButtonQuit::setStop(bool *stopGame)
{
    _stopGame = stopGame;
}

void ButtonQuit::stopGame()
{
    *(_stopGame) = true;
}

void ButtonReturn::update()
{
    if (isHover() && _enable)
    {
        _menu->open();
        _menu->allSubMenusClose();
    }
}

ButtonReturn::ButtonReturn(const char *fontPath, const int &size,
                           const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight,
                           const int &positionXPixels, const int &positionYPixels, const bool &middle, Menu *menu) : ButtonMenu("Return", fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                                positionXPixels, positionYPixels, middle, menu)
{
}

void ButtonSaveorLoadSlot::update()
{
    if (isHover() && _enable)
    {
        std::string texte;
        if (_action == "Save")
        {
            texte = "Game saved : slot " + std::to_string(_slotNumber);
            _feedback->update((texte).c_str());
            _menu->setSaveLoadString("Save" + std::to_string(_slotNumber));
        }
        else if (_action == "Load")
        {
            texte = "Game loaded : slot " + std::to_string(_slotNumber);
            _feedback->update((texte).c_str());
            _menu->setSaveLoadString("Load" + std::to_string(_slotNumber));
        }
    }
}

ButtonSaveorLoadSlot::ButtonSaveorLoadSlot(const char *fontPath, const int &size,
                                           const glimac::FilePath &filePath, const uint &windowWidth, const uint &windowHeight, const int &positionXPixels,
                                           const int &positionYPixels, const bool &middle, const int &slotNumber, const std::string &action, Message *feedback, Menu *menu) : Button(("Slot " + std::to_string(slotNumber)).c_str(), fontPath, size, filePath, windowWidth, windowHeight,
                                                                                                                                                                                     positionXPixels, positionYPixels, middle),
                                                                                                                                                                              _slotNumber(slotNumber),
                                                                                                                                                                              _action(action),
                                                                                                                                                                              _feedback(feedback),
                                                                                                                                                                              _menu(menu)
{
}
