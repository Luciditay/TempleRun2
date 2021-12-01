
#pragma once

#include <glimac/TTFtext.hpp>
#include <string>
#include <glimac/Image.hpp>
#include "glimac/Observer.hpp"


class ScoreCounter {
    public:
    ScoreCounter(const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight);
    void update(const int& valueDistance, const int& valueItems);
    const void draw() const;
    const int getTotalScore();

    private:
    int _distance;
    int _items;
    Message _message;
};

class Background {

    public: 
    Background(const char* imagePath, const glimac::FilePath& filePath);
    ~Background();
    const void draw() const;

    private:
    const Rectangle2D _rect;
    GLuint _texture;

};

class Menu; 
class Button {
    public:
    Button(const char* text, const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle);
    const bool isHover();
    const void draw();
    const void enable();
    const void disable();

    private :
    Message* _currentLabel;
    Message _label;
    Message _labelHover;

    protected:
    bool _enable;
};

class ButtonMenu : public Button {
    public:
    ButtonMenu(const char* text, const char* fontPath, const int& size, 
            const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
            const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    protected:
    Menu* _menu;
};

//Attention à bien abonner tous les boutons au ClickListener + utiliser "enableDisable()" pour pouvoir les activer

class ButtonContinue : public ButtonMenu, public Observer {
    public:
    ButtonContinue(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    virtual void update() override;
};

class ButtonStartAgain : public ButtonMenu, public Observer {
    public:
    ButtonStartAgain(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle,  Menu* menu);
    virtual void update() override;
};

class ButtonHighScore : public ButtonMenu, public Observer {
    public:
    ButtonHighScore(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    virtual void update() override;
};


class ButtonSave : public ButtonMenu, public Observer {
    public:
    ButtonSave(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    virtual void update() override;
};

class ButtonLoad : public ButtonMenu, public Observer {
    public:
    ButtonLoad(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    virtual void update() override;
};

class ButtonQuit : public ButtonMenu, public Observer {
    public:
    ButtonQuit(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    virtual void update() override;
    void setStop(bool* stopGame);
    void stopGame();

    private:
    bool* _stopGame;
};


class ButtonReturn : public ButtonMenu, public Observer {
    public:
    ButtonReturn(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    virtual void update() override;
};

//Button to save and load a game

class ButtonSaveorLoadSlot : public Button, public Observer {
    public:
    ButtonSaveorLoadSlot(const char* fontPath, const int& size, 
            const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight, const int& positionXPixels, 
            const int& positionYPixels, const bool& middle, const int& slotNumber, const std::string& action, Message* feedback);
    virtual void update() override;

    private:
    const int _slotNumber;
    const std::string _action;
    Message* _feedback;
};

