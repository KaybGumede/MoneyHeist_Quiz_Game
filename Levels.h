#ifndef LEVEL1_H
#define LEVEL1_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Questions.h"
#include "TimeManagement.h"
#include <stack>
#include <memory>
using namespace sf;

class Level1 {
public:

    Level1(sf::RenderWindow& window);// Constructor to set up the Level 1 screen
    void fitTextToRectangle(Text& text, RectangleShape& rectangle);
    void fitTextToSprite(Text& text, Sprite& sprite);
    void updateQuestions();
    void initializeStack();


    // Define methods for handling events, updating the game state, and rendering
    void handleEvents();
    void update();
    void render();

private:
    stack<Questions*> bank;
    int randomQuestion;
    int countAnswer;
    double currentScore;
    TimeManagement gameTime;
    Font techFont;
    Text timerText;


    FillBlank* fb_questions;
    Questions* questions;
    TrueOrFalse* tf_questions;

    sf::RenderWindow& window;          // Reference to the main window
    sf::RectangleShape returnButton; // Return button
    //sf::SoundBuffer buffer;
    //sf::Sound sound;

    //TextBox
    // Declare these in Level1.h (private section)
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

    //sound buffer
    SoundBuffer buffer;
    Sound sound;
    SoundBuffer countdownBuffer;
    Sound countdownSound;
    bool countdownSoundPlayed;
};



#endif // LEVEL1_H
