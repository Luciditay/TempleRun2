#include "glimac/TTFtext.hpp"

Message::Message(const char* text, SDL_Color color, const char* fontPath, const int size, 
                const glimac::FilePath &filePath, uint windowWidth, uint windowHeight,
                int positionXPixels, int positionYPixels, bool middle) : 
                _myMessage(text), _textColor(color), _fontPath(fontPath), _messageBox(filePath), _fontSize(size*2.), 
                _windowWidth(windowWidth), _windowHeight(windowHeight), _posXPixels(positionXPixels), _posYPixels(positionYPixels), _middle(middle) {

    if (!text[0]) { //Un message ne peut pas être vide.
        _myMessage = "/0";
    }

    SDL_Surface* surfaceText = renderText();

    textureFromText(surfaceText);
}

void Message::textureFromText(SDL_Surface* surfaceText) {
    //Bind texture
    glBindTexture(GL_TEXTURE_2D, *_texture);
    //Envoie carte graphique
    glTexImage2D(GL_TEXTURE_2D, 0, 4, surfaceText->w, surfaceText->h, 0,
                    GL_BGRA, GL_UNSIGNED_BYTE, surfaceText->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Débind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //Calcul des facteurs par lesquels il faudra scale/translate le message pour l'afficher à la taille/place voulue
    _width = float(surfaceText->w)/(2.*(float(_windowWidth)));
    _height = float(surfaceText->h)/(2.*(float(_windowHeight)));
    if(_middle==false) {
        _posX = -1+_width+((float(_posXPixels)*2.)/float(_windowWidth));
        _posY = 1-0.7*_height-((float(_posYPixels)*2.)/float(_windowHeight));
    } else {
        _posX = -1+((float(_posXPixels)*2.)/float(_windowWidth));
        _posY = 1-((float(_posYPixels)*2.)/float(_windowHeight));
    }

    //Libération mémoire SDL_Surface 
    SDL_FreeSurface(surfaceText);
}

void Message::update(const char* newText) {
    _myMessage = newText;
    SDL_Surface* surfaceText = renderText();
    textureFromText(surfaceText);
}

void Message::update(SDL_Color color) {
    _textColor = color;
    SDL_Surface* surfaceText = renderText();
    textureFromText(surfaceText);
}

SDL_Surface* Message::renderText() {
    TTF_Font *police = NULL;
    police = TTF_OpenFont(_fontPath, _fontSize);
    try{
        if(!police){
            throw std::string(TTF_GetError());
        }
    }
	catch(const std::string &error) {
			std::cerr << "error : " << error << std::endl;
	}
  
    /* Écriture du texte dans la SDL_Surface texte en mode Blended */
    SDL_Surface *texte = TTF_RenderText_Blended(police, _myMessage, _textColor);
    try{
        if(!texte){
            throw std::string(TTF_GetError());
        }
    }
	catch(const std::string &error) {
			std::cerr << "error : " << error << std::endl;
	}

    TTF_CloseFont(police);

    return texte;
}

const void Message::draw() const {
    _messageBox.draw(*_texture, _width, _height, _posX, _posY);
}

const int Message::getPosXPixels() const{
    if(_middle==false) {
        return ((_posX+1-_width)*_windowWidth)/2.;
    } else {
        return ((_posX+1)*_windowWidth)/2. - getWidthPixels()/2.;
    }
}

const int Message::getPosYPixels() const {
    if(_middle==false) {
        return (-(_posY-1+0.7*(_height))*_windowHeight)/2. ;
    } else {
        return (-(_posY-1)*_windowHeight)/2. - getHeightPixels()/2.;
    }
    
}

const int Message::getWidthPixels() const {
    return _width*_windowWidth;
}

const int Message::getHeightPixels() const {
    return 0.7*(_height*_windowHeight);
}