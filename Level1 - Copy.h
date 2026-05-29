#pragma once
#ifndef GAMESUBLEVEL_H
#define GAMESUBLEVEL_H

#include <SFML/Graphics.hpp>
#include "Questions.h"
#include <memory>
using namespace sf;

class GameSubLevel {
public:

    GameSubLevel(sf::RenderWindow& window);// Constructor to set up the Level 1 screen
    void fitTextToRectangle(Text& text, RectangleShape& rectangle);

    // Define methods for handling events, updating the game state, and rendering
    void handleEvents();
    void update();
    void render();

private:
    sf::RenderWindow& window;

    //answer buttons
    Texture easyTexture;
    Texture mediumTexture;
    Texture hardTexture;
    Texture returnTexture;
    Sprite easySprite;
    Sprite mediumSprite;
    Sprite hardSprite;
    Sprite returnSprite;


    sf::RectangleShape easyButton;
    sf::RectangleShape mediumButton;
    sf::RectangleShape hardButton;
    sf::RectangleShape returnButton;
    //Text for answer Buttons
    sf::Text easyText;
    sf::Text mediumText;
    sf::Text hardText;
    sf::Text returnText;

    // Text for the return button
    sf::Sprite backgroundSprite;       // Sprite for the background
    sf::Texture backgroundTexture;     // Texture for the background
    sf::Font font;                     // Font for the text on the button
};

#endif // GAMESUBLEVEL_H
