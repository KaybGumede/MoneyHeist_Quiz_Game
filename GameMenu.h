#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <SFML/Graphics.hpp>
#include "Questions.h"
#include <memory>
#include <SFML/Window.hpp>
using namespace sf;

class ChooseLevel {
public:

    ChooseLevel(sf::RenderWindow& window);// Constructor to set up the Level 1 screen
    void fitTextToRectangle(Text& text, RectangleShape& rectangle);

    // Define methods for handling events, updating the game state, and rendering
    void handleEvents();
    void update();
    void render();

private:
    sf::RenderWindow& window;
    Vector2f setButtonSize;
    Vector2f answerButtonSize;// 40% of screen width
    //answer buttons
    Texture level1Texture;
    Texture level2Texture;
    Texture level3Texture;
    Texture lockTexture;
    Texture returnTexture;
    Sprite level1Sprite;
    Sprite level2Sprite;
    Sprite level3Sprite;
    Sprite lockSprite;
    Sprite returnSprite;


    sf::RectangleShape level1Button;
    sf::RectangleShape level2Button;
    sf::RectangleShape level3Button;
    sf::RectangleShape returnButton;
    //Text for answer Buttons
    sf::Text level1Text;
    sf::Text level2Text;
    sf::Text level3Text;
    sf::Text returnText;
    // Text for the return button
    sf::Sprite backgroundSprite;       // Sprite for the background
    sf::Texture backgroundTexture;     // Texture for the background
    sf::Font font;                     // Font for the text on the button
};



#endif // CHOOSELEVEL_H
