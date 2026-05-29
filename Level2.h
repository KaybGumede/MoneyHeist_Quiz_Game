#pragma once
#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;

class Leaderboard {
public:

    Leaderboard(sf::RenderWindow& window);// Constructor to set up the Level 1 screen
    void fitTextToRectangle(Text& text, RectangleShape& rectangle);

    // methods for handling events, updating the game state, and rendering
    void handleEvents();
    void update();
    void render();

private:

    sf::RenderWindow& window;          // Reference to the main window
    sf::RectangleShape returnButton;  // Return button


    //answer buttons
    Texture Button1Texture;
    Texture Button2Texture;
    Texture Button3Texture;
    Texture Button4Texture;
    Sprite button1Sprite;
    Sprite button2Sprite;
    Sprite button3Sprite;
    Sprite button4Sprite;


    sf::RectangleShape leaderBoadHolder;
    sf::RectangleShape rank1Player;
    sf::RectangleShape rank2Player;
    sf::RectangleShape rank3Player;
    sf::RectangleShape rank4Player;
    sf::RectangleShape rank5Player;


    sf::RectangleShape rank1Circle;
    sf::RectangleShape rank2Circle;
    sf::RectangleShape rank3Circle;
    //Score
    sf::Text score1;
    sf::Text score2;
    sf::Text score3;
    sf::Text score4;
    sf::Text score5;

    //Text for answer Buttons
    sf::Text name1;
    sf::Text name2;
    sf::Text name3;
    sf::Text name4;
    sf::Text name5;

    //Rank
    sf::Text rankNum1;
    sf::Text rankNum2;
    sf::Text rankNum3;
    sf::Text rankNum4;
    sf::Text rankNum5;

    sf::Text returnText;               // Text for the return button
    sf::Sprite backgroundSprite;       // Sprite for the background
    sf::Texture backgroundTexture;     // Texture for the background
    sf::Font font;                     // Font for the text on the button
};


#endif // LEADERBOARD_H
