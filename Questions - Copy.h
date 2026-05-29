#pragma once
#ifndef LEVEL2_H
#define LEVEL2_H

#include <SFML/Graphics.hpp>
#include "Questions.h"
#include <memory>
using namespace sf;

class Level2 {
public:

    Level2(sf::RenderWindow& window);// Constructor to set up the Level 1 screen
    void fitTextToRectangle(Text& text, RectangleShape& rectangle);
    void updateQuestions();


    // Define methods for handling events, updating the game state, and rendering
    void handleEvents();
    void update();
    void render();

private:
    int randomQuestion;
    FillBlank* fb_questions;
    Questions* questions;
    TrueOrFalse* tf_questions;

    sf::RenderWindow& window;          // Reference to the main window
    sf::RectangleShape returnButton;  // Return button

    //TextBox
    // Declare these in Level2.h
    sf::RectangleShape questionBox;
    sf::Text questionText;

    //answer buttons
    Texture Button1Texture;
    Texture Button2Texture;
    Texture Button3Texture;
    Texture Button4Texture;
    Sprite button1Sprite;
    Sprite button2Sprite;
    Sprite button3Sprite;
    Sprite button4Sprite;


    sf::RectangleShape answerButton1;
    sf::RectangleShape answerButton2;
    sf::RectangleShape answerButton3;
    sf::RectangleShape answerButton4;
    //Text for answer Buttons
    sf::Text answer1Text;
    sf::Text answer2Text;
    sf::Text answer3Text;
    sf::Text answer4Text;

    sf::Text returnText;               // Text for the return button
    sf::Sprite backgroundSprite;       // Sprite for the background
    sf::Texture backgroundTexture;     // Texture for the background
    sf::Font font;                     // Font for the text on the button
};


#endif // LEVEL2_H
