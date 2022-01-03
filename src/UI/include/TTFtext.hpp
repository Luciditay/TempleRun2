#pragma once

#include <GL/glew.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <glimac/glm.hpp>
#include <rectangle2D.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glpp.hpp>

/// \class Message
/// \brief Warning : to show the text, transparency must be activated (glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);) AND every fragment shader must return a "vec4" fFragColor for the alpha channel
class Message
{
public:
    /// \brief constructor
    /// \param text : text of the message
    /// \param color : color of the message
    /// \param fontPath : path of the font
    /// \param size : size of the font
    /// \param filePath : application path
    /// \param windowWidth : width of the application window
    /// \param windowHeight : height of the application window
    /// \param positionXPixels : position of the button in pixels on X axis (from left to right)
    /// \param positionYPixels : position of the button in pixels on Y axis (from top to bottom)
    /// \param middle : if true, message anchor is its center, if false it is the top left corner of the message
    Message(const char *text, SDL_Color color, const char *fontPath, const int size,
            const glimac::FilePath &filePath, const uint windowWidth, const uint windowHeight,
            const int positionXPixels, const int positionYPixels, const bool middle);
    /// \brief draw the message
    void draw() const;
    /// \brief change the text of the message
    void update(const char *newText);
    /// \brief change the color of the message
    void update(SDL_Color color);

    /// \brief give the position of the message on X axis in pixels
    int getPosXPixels() const;
    /// \brief give the position of the message on Y axis in pixels
    int getPosYPixels() const;
    /// \brief give the width of the message in pixels
    int getWidthPixels() const;
    /// \brief give the height of the message in pixels
    int getHeightPixels() const;

private:
    // Texte et ses propriétés
    const char *_myMessage;  /*!< message text */
    SDL_Color _textColor;    /*!< color of the text */
    const char *_fontPath;   /*!< path of the font */
    const int _fontSize;     /*!< size of the font */
    const float _posXPixels; /*!< position of the message on X axis in pixels */
    const float _posYPixels; /*!< position of the message on Y axis in pixels */
    const bool _middle;      /*!< if true, message anchor is its center, if false it is the top left corner of the message */

    // Boite de texte
    Rectangle2D _messageBox; /*!< rectangle to write the message in */

    // Pour draw
    float _width;           /*!< width in OpenGL coordinates, depending on the window size */
    float _height;          /*!< height in OpenGL coordinates, depending on the window size */
    float _posX;            /*!< position on X axis in OpenGL coordinates, depending on the window size */
    float _posY;            /*!< position on Y axis in OpenGL coordinates, depending on the window size */
    UniqueTexture _texture; /*!< Like a Glint, but it works better (handle the fact to put OpenGL objects in vectors) */

    // Infos sur la fenêtre si besoin de recalculer le texte (scale/position)
    const uint _windowWidth;  /*!< width of the window (needed to compute scale/position for OpenGL) */
    const uint _windowHeight; /*!< height of the window (needed to compute scale/position for OpenGL) */

    /// \brief render the text using TTF_text on a SDL_Surface
    SDL_Surface *renderText();
    /// \brief change the SDL_Surface into a beautiful texture on which the text is writen
    void textureFromText(SDL_Surface *surfaceText);
};