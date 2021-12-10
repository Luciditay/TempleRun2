
#pragma once

#include <TTFtext.hpp>
#include <string>
#include <glimac/Image.hpp>
#include "Observer.hpp"

/// \class ScoreCounter
/// \brief class showing the score on the top left corner
class ScoreCounter {
    public:
    /// \brief constructor
	/// \param  filePath : the path of the application
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    ScoreCounter(const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight);
    /// \brief update the score
    /// \param valueDistance : distance ran
    /// \param valueItems : number items collected
    void update(const int& valueDistance, const int& valueItems);
    /// \brief draw the counter
    const void draw() const;
     /// \brief give the total score (distance + items)
    const int getTotalScore();

    private:
    int _distance; /*!< distance ran by the player */
    int _items; /*!< items collected by the player */
    Message _message; /*!< text (score and distance) */
};

/// \class Backgroung
/// \brief class defining a background image
class Background {

    public: 
    /// \brief constructor
	/// \param  filePath : the path of the application
    /// \param  imagePath : the path of the image
    Background(const char* imagePath, const glimac::FilePath& filePath);
    /// \brief destructor
    ~Background();
    /// \brief draw the backgroung
    const void draw() const;

    private:
    const Rectangle2D _rect; /*!< a rectangle in 2D to draw the background on it */
    GLuint _texture; /*!< texture of the background */

};

class Menu; 

/// \class Button
class Button {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    Button(const char* text, const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle);
    /// \return true if the button is hover
    const bool isHover();
    /// \brief draw the button
    const void draw();
    /// \brief activate the button (so it is possible to click on it)
    const void enable();
    /// \brief deactivate the button (when it is hidden)
    const void disable();

    private :
    Message* _currentLabel; /*!< text as it is showed */
    Message _label; /*!< usual text (in white) */
    Message _labelHover; /*!< text when hover (in red) */

    protected:
    bool _enable; /*!< true if the button is activated */
};

/// \class Button for the Menu
class ButtonMenu : public Button {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param menu : menu that contains the button
    ButtonMenu(const char* text, const char* fontPath, const int& size, 
            const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
            const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    protected:
    Menu* _menu; /*!< menu that contains the button */
};

/// \class ButtonContinue, child of ButtonMenu and Observer (must be attached to the ClickListener to be used)
class ButtonContinue : public ButtonMenu, public Observer {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param menu : menu that contains the button
    ButtonContinue(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    /// \brief update method which is called by the ClickListener 
    virtual void update() override;
};

/// \class ButtonStartAgain, child of ButtonMenu and Observer (must be attached to the ClickListener to be used)
class ButtonStartAgain : public ButtonMenu, public Observer {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param menu : menu that contains the button
    ButtonStartAgain(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle,  Menu* menu);
    /// \brief update method which is called by the ClickListener
    virtual void update() override;
};

/// \class ButtonHighScore, child of ButtonMenu and Observer (must be attached to the ClickListener to be used)
class ButtonHighScore : public ButtonMenu, public Observer {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param menu : menu that contains the button
    ButtonHighScore(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    /// \brief update method which is called by the ClickListener
    virtual void update() override;
};

/// \class ButtonSave, child of ButtonMenu and Observer (must be attached to the ClickListener to be used)
class ButtonSave : public ButtonMenu, public Observer {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param menu : menu that contains the button
    ButtonSave(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    /// \brief update method which is called by the ClickListener
    virtual void update() override;
};

/// \class ButtonLoad, child of ButtonMenu and Observer (must be attached to the ClickListener to be used)
class ButtonLoad : public ButtonMenu, public Observer {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param menu : menu that contains the button
    ButtonLoad(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    /// \brief update method which is called by the ClickListener
    virtual void update() override;
};

/// \class ButtonQuit, child of ButtonMenu and Observer (must be attached to the ClickListener to be used)
class ButtonQuit : public ButtonMenu, public Observer {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param menu : menu that contains the button
    ButtonQuit(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    /// \brief update method which is called by the ClickListener
    virtual void update() override;
    /// \brief set the boolean stopGame that should be turned "true" to quit the game
    void setStop(bool* stopGame);
    /// \brief stop the game and close the window
    void stopGame();

    private:
    bool* _stopGame; /*!< boolean used to quit */
};

/// \class ButtonReturn, child of ButtonMenu and Observer (must be attached to the ClickListener to be used)
class ButtonReturn : public ButtonMenu, public Observer {
    public:
    /// \brief constructor
    /// \param text : the text of the button
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param menu : menu that contains the button
    ButtonReturn(const char* fontPath, const int& size, 
                const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight,
                const int& positionXPixels, const int& positionYPixels, const bool& middle, Menu* menu);
    /// \brief update method which is called by the ClickListener
    virtual void update() override;
};

//Button to save and load a game

/// \class ButtonSaveorLoadSlot, child of Button and Observer (must be attached to the ClickListener to be used)
class ButtonSaveorLoadSlot : public Button, public Observer {
    public:
    /// \brief constructor
    /// \param fontPath : path of the font
	/// \param filePath : the path of the application
    /// \param size : the size of the font
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, button anchor is its center, if false it is the top left corner of the button
    /// \param slotNumber : number of the save file modified or read by the button
    /// \param action : "Save" or "Load"
    /// \param feedback : the button can modify the feedback message in the menu "save" or "load"
    ButtonSaveorLoadSlot(const char* fontPath, const int& size, 
            const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight, const int& positionXPixels, 
            const int& positionYPixels, const bool& middle, const int& slotNumber, const std::string& action, Message* feedback);
    virtual void update() override;

    private:
    const int _slotNumber; /*!< number of the save file */
    const std::string _action; /*!< "Save" or "Load" */
    Message* _feedback; /*!< pointer to be able to change the message */
};

