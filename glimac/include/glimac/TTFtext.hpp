/*
Attention : pour afficher du texte, penser à activer la transparence pour le rendu : 
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
Et tous les fragments shaders doivent bien renvoyer des "vec4" comme fFragColor car il y a un canal alpha. 
*/

#pragma once

#include <GL/glew.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <glimac/glm.hpp>
#include <glimac/rectangle2D.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glpp.hpp>

class Message {
    public:
    Message(const char* text, SDL_Color color, const char* fontPath, const int size, 
            const glimac::FilePath &filePath, const uint windowWidth, const uint windowHeight,
            const int positionXPixels, const int positionYPixels, const bool middle);
    const void draw() const;
    void update(const char* newText);
    void update(SDL_Color color);

    const int getPosXPixels() const;
    const int getPosYPixels() const;
    const int getWidthPixels() const;
    const int getHeightPixels() const;

    private:
    //Texte et ses propriétés
    const char* _myMessage;
    SDL_Color _textColor; 
    const char* _fontPath; 
    const int _fontSize;
    const float _posXPixels;
    const float _posYPixels;
    const bool _middle;

    //Boite de texte
    Rectangle2D _messageBox;

    //Pour draw
    float _width;
    float _height;
    float _posX;
    float _posY;
    UniqueTexture _texture;

    //Infos sur la fenêtre si besoin de recalculer le texte (scale/position)
    const uint _windowWidth;
    const uint _windowHeight;
    
    SDL_Surface* renderText();
    void textureFromText(SDL_Surface* surfaceText);
};