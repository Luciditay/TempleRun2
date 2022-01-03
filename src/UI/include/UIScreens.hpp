#pragma once
#include "UI.hpp"
#include "HighScores.hpp"
#include <vector>
#include <string>

/// \class TitleScreen
/// \brief class defining the first screen the player sees once they start up their game
class TitleScreen {
    public:
    /// \brief constructor
	/// \param imagePath : path of the background image
    /// \param fontPath : path of font used to write the text
    /// \param size : size of the title
    /// \param filePath : application path
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    TitleScreen(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight);

    /// \brief close the title screen 
    /// \return true when game is started
    const bool close(); 

    /// \brief draw the title screen 
    const void draw() const;

    private:

    Message _title;  /*!< game title */
    Message _information;  /*!< "Click anywhere to play." */
    const Background _background;  /*!< Background image */
    bool _open;  /*!< true is the title screen is open */
};

/// \class DeadScreen
/// \brief class defining the screen that the player sees when their character dies
class DeadScreen {
    public:
    /// \brief constructor
	/// \param imagePath : path of the background image
    /// \param fontPath : path of font used to write the text
    /// \param size : size of the title
    /// \param filePath : application path
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    DeadScreen(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, const uint& windowWidth, const uint& windowHeight);
    /// \brief close the dead screen 
    const void close(); 
    /// \brief open the dead screen 
    const void open();
    /// \brief draw the dead screen 
    const void draw() const;
    /// \brief show the last score when the character dies
    /// \param valueScore : new score 
    const void updateScore(const int valueScore);

    private:
    Message _title;  /*!< Death message */
    Message _score;  /*!< Score message */
    Message _information;  /*!< "Click anywhere to play again." */
    const Background _background; /*!< Background image */
    bool _open; /*!< true is the dead screen is open */
};

class Menu;

/// \class SubMenu
/// \brief parent class defining the submenus you can reach from the main menu
class SubMenu {
    public:
    /// \brief constructor
	/// \param imagePath : path of the background image
    /// \param fontPath : path of font used to write the text
    /// \param size : size of the title
    /// \param filePath : application path
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param clickListener : the observer, in the SDL events loop, that can update all the buttons : every button must be attached to it
     /// \param menu : main menu
    SubMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu);
    /// \brief draw the submenu
    const void draw() ;
    /// \brief open the submenu
    const void open();
    /// \brief close the submenu
    const void close();
    /// \return true if the submenu is open
    const bool isOpen() const;

    private:
    Menu* _menu; /*!< Main menu */
    const Background _background; /*!< Background image */
    ButtonReturn _return; /*!<  "Return to main menu" button */
    bool _open; /*!< true if the submenu is open */
};

/// \class HighScoresMenu
/// \brief submenu child, show highscores array
class HighScoresMenu : public SubMenu {
    public:
    /// \brief constructor
	/// \param imagePath : path of the background image
    /// \param fontPath : path of font used to write the text
    /// \param size : size of the title
    /// \param filePath : application path
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param clickListener : the observer, in the SDL events loop, that can update all the buttons : every button must be attached to it
    /// \param menu : main menu
    HighScoresMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu);
    /// \brief add a new score (if it is good enough), called when you die
    /// \param valueScore : new score 
    const void updateScore(const int valueScore);
    /// \brief draw the highscores menu
    const void draw();

    private:
    HighScores _highscores; /*!< highscores */
    std::vector<Message> _messages; /*!< vector of messages, to show the title and the scores values */
};

/// \class SaveOrLoadMenu
/// \brief submenu child, show buttons to save or load the game
class SaveOrLoadMenu : public SubMenu {
    public: 
    /// \brief constructor
	/// \param imagePath : path of the background image
    /// \param fontPath : path of font used to write the text
    /// \param size : size of the title
    /// \param filePath : application path
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param clickListener : the observer, in the SDL events loop, that can update all the buttons : every button must be attached to it
    /// \param menu : main menu
    /// \param action : string "Save" or "Load" that defines the action of the 3 ButtonSaveorLoadSlots
    SaveOrLoadMenu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
            const uint& windowWidth, const uint& windowHeight, Subject &clickListener, Menu* menu, std::string action);
    /// \brief draw the SaveOrLoad menu
    const void draw();
    /// \brief open the SaveOrLoad menu
    const void open();
    /// \brief close the SaveOrLoad menu
    const void close();

    private:
    ButtonSaveorLoadSlot _slot1; /*!< save file 1 */
    ButtonSaveorLoadSlot _slot2; /*!< save file 2 */
    ButtonSaveorLoadSlot _slot3; /*!< save file 3 */
    Message _titre; /*!< "Save" or "Load" */
    Message _feedback; /*!< feedback message : tells which file has been saved/loaded */
};

/// \class Menu
/// \brief main menu
class Menu {
    public:
    /// \brief constructor
	/// \param imagePath : path of the background image
    /// \param fontPath : path of font used to write the text
    /// \param size : size of the title
    /// \param filePath : application path
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    Menu(const char* imagePath, const char* fontPath, const int& size, const glimac::FilePath& filePath, 
        const uint& windowWidth, const uint& windowHeight);
    /// \brief draw the main menu or a submenu if needed
    const void draw();
    /// \brief open the main menu
    const void open();
    /// \brief close the main menu
    const void close();
    /// \brief set the boolean stopGame, because the quit button must turn this boolean "true" to quit the game
    const void setStop(bool* stopGame);
    /// \brief open one submenu depending on the string ("Highscores", "Save" or "Load")
    const void SubMenuOpen(const std::string& subMenuType);
    /// \brief close all submenus
    const void allSubMenusClose();
    /// \return true if the main menu is open
    const bool isOpen() const;
    /// \return true if at least one submenu or the main menu is open
    const bool someMenuIsOpen() const;
    /// \brief on click, the clickListener updates every button, and echap open/close the menu
    void handleSDLEvent(const SDL_Event& e, bool gameStart);
    /// \brief add a new score (if it is good enough)
    const void updateHighScores(const int valueScore);
    /// \brief called when the player wants to start again (turn the boolean "true")
    void startAgainTrue();
    /// \return true if the player wants to start again
    const bool shouldStartAgain();
    const std::string getSaveLoadString();
    void setSaveLoadString(const std::string whatToDo);

    private:
    ButtonContinue _continue; /*!< button to quit the menu/pause */
    ButtonStartAgain _startAgain; /*!< button to start again */
    ButtonHighScore _highScores; /*!< button to open HighScores menu */
    ButtonSave _save; /*!< button to open Save menu */
    ButtonLoad _load; /*!< button to open Load menu */
    ButtonQuit _quit; /*!< button to quit game and close the window */
    Subject _clickListener; /*!< update buttons when needed */
    const Background _background; /*!< background image*/
    bool _open; /*!< true if the main menu is open */
    bool _startGameAgain; /*!< true if the player wants to start again */

    HighScoresMenu _highScoresMenu; /*!< submenu */
    SaveOrLoadMenu _saveMenu; /*!< submenu */
    SaveOrLoadMenu _loadMenu; /*!< submenu */
    std::string _saveLoadString;
};