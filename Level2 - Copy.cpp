#include "Level1.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Questions.h"
#include "SceneManager.h"
#include "TimeManagement.h"
#include <cstdlib>
#include <ctime>

using namespace sf;

Level1::Level1(RenderWindow& window) : window(window) {
    countAnswer = 0;
    currentScore = SceneManager::getScore();
    gameTime.setTime(10);

    // Setting up random
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    randomQuestion = (std::rand() % 2) + 1;

    questions = new Questions("Easy");
    tf_questions = new TrueOrFalse("Easy");
    fb_questions = new FillBlank("Easy");

    questions->initializeQuestions();
    tf_questions->initializeQuestions();
    fb_questions->initializeQuestions();

    // Load background image
    if (!backgroundTexture.loadFromFile("BG.png")) {
        std::cerr << "Failed to load level 1 background image!" << std::endl;
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background to fit the window size
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Load sound
    if (!buffer.loadFromFile("shotSuccess.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    //Countdown sound
    if (!countdownBuffer.loadFromFile("countdown.wav")) {  // Make sure you have this file
        std::cerr << "Failed to load countdown sound!" << std::endl;
    }
    countdownSound.setBuffer(countdownBuffer);
    // Set Sound
    sound.setBuffer(buffer);

    // Load fonts
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load main font!" << std::endl;
        return;
    }

    // Load Technology 
    if (!techFont.loadFromFile("Technology-Bold.ttf")) {
        std::cerr << "Failed to load Technology Bold font! Using fallback font." << std::endl;
        techFont = font; 
    }

    if (!Button1Texture.loadFromFile("ButtonA.png") ||
        !Button2Texture.loadFromFile("ButtonB.png") ||
        !Button3Texture.loadFromFile("ButtonC.png") ||
        !Button4Texture.loadFromFile("ButtonD.png")) {
        return;
    }

    // Timer display
    timerText.setFont(techFont);
    timerText.setCharacterSize(43);
    timerText.setFillColor(Color::Black);
    timerText.setPosition(window.getSize().x - 100, 10);
    timerText.setString("10");
    timerText.setStyle(Text::Bold);

    // Question Box
    questionBox.setSize(Vector2f(window.getSize().x - 40, 100));
    questionBox.setFillColor(Color(200, 200, 200));
    questionBox.setOutlineThickness(2);
    questionBox.setOutlineColor(Color::Black);
    questionBox.setPosition(20, 10);

    questionText.setFont(font);
    questionText.setCharacterSize(14);
    questionText.setFillColor(Color::Black);
    fitTextToRectangle(questionText, questionBox);

    // Button Size and Centering
    Vector2f answerButtonSize(window.getSize().x * 0.4f, 50);
    float centerX = (window.getSize().x - answerButtonSize.x) / 2;
    float startY = window.getSize().y * 0.30f;
    float buttonSpacing = 60;

    if (randomQuestion == 1) {
        questionText.setString(questions->getQuestion());

        button1Sprite.setTexture(Button1Texture);
        float posX = (0 % 2 == 0) ? window.getSize().x * 0.2f : window.getSize().x * 0.6f;
        float posY = (0 < 2) ? window.getSize().y * 0.4f : window.getSize().y * 0.6f;
        button1Sprite.setPosition(posX, posY);
        button1Sprite.setScale(.7f, .7f);

        button2Sprite.setTexture(Button2Texture);
        posX = (1 % 2 == 0) ? window.getSize().x * 0.2f : window.getSize().x * 0.6f;
        posY = (1 < 2) ? window.getSize().y * 0.4f : window.getSize().y * 0.6f;
        button2Sprite.setPosition(posX, posY);
        button2Sprite.setScale(.7f, .7f);

        button3Sprite.setTexture(Button3Texture);
        posX = (2 % 2 == 0) ? window.getSize().x * 0.2f : window.getSize().x * 0.6f;
        posY = (2 < 2) ? window.getSize().y * 0.4f : window.getSize().y * 0.6f;
        button3Sprite.setPosition(posX, posY);
        button3Sprite.setScale(.7f, .7f);

        button4Sprite.setTexture(Button4Texture);
        posX = (3 % 2 == 0) ? window.getSize().x * 0.2f : window.getSize().x * 0.6f;
        posY = (3 < 2) ? window.getSize().y * 0.4f : window.getSize().y * 0.6f;
        button4Sprite.setPosition(posX, posY);
        button4Sprite.setScale(.7f, .7f);

        answer1Text.setFont(font);
        answer1Text.setString(questions->getChoices()[0]);
        answer1Text.setCharacterSize(24);
        answer1Text.setFillColor(Color::Black);
        fitTextToSprite(answer1Text, button1Sprite);

        answer2Text.setFont(font);
        answer2Text.setString(questions->getChoices()[1]);
        answer2Text.setCharacterSize(24);
        answer2Text.setFillColor(Color::Black);
        fitTextToSprite(answer2Text, button2Sprite);

        answer3Text.setFont(font);
        answer3Text.setString(questions->getChoices()[2]);
        answer3Text.setCharacterSize(24);
        answer3Text.setFillColor(Color::Black);
        fitTextToSprite(answer3Text, button3Sprite);

        answer4Text.setFont(font);
        answer4Text.setString(questions->getChoices()[3]);
        answer4Text.setCharacterSize(24);
        answer4Text.setFillColor(Color::Black);
        fitTextToSprite(answer4Text, button4Sprite);
    }
    else if (randomQuestion == 2) {
        questionText.setString(tf_questions->getQuestion());
        button1Sprite.setTexture(Button1Texture);
        float posX = (0 % 2 == 0) ? window.getSize().x * 0.2f : window.getSize().x * 0.6f;
        float posY = (0 < 2) ? window.getSize().y * 0.4f : window.getSize().y * 0.6f;
        button1Sprite.setPosition(posX, posY);
        button1Sprite.setScale(.7f, .7f);

        button2Sprite.setTexture(Button2Texture);
        posX = (1 % 2 == 0) ? window.getSize().x * 0.2f : window.getSize().x * 0.6f;
        posY = (1 < 2) ? window.getSize().y * 0.4f : window.getSize().y * 0.6f;
        button2Sprite.setPosition(posX, posY);
        button2Sprite.setScale(.7f, .7f);

        answer1Text.setFont(font);
        answer1Text.setString("True");
        answer1Text.setCharacterSize(24);
        answer1Text.setFillColor(Color::Black);
        fitTextToSprite(answer1Text, button1Sprite);

        answer2Text.setFont(font);
        answer2Text.setString("False");
        answer2Text.setCharacterSize(24);
        answer2Text.setFillColor(Color::Black);
        fitTextToSprite(answer2Text, button2Sprite);
    }
    else {
        questionText.setString(fb_questions->getQuestion());
    }

    // Return Button
    Vector2f returnButtonSize(200, 50);
    returnButton.setSize(returnButtonSize);
    returnButton.setFillColor(Color::White);
    returnButton.setPosition(10, window.getSize().y - returnButtonSize.y - 10);
    returnButton.setOutlineThickness(3);
    returnButton.setOutlineColor(Color::Black);
    returnText.setFont(font);
    returnText.setString("Return to Menu");
    returnText.setCharacterSize(24);
    returnText.setFillColor(Color::Black);
    fitTextToRectangle(returnText, returnButton);

    gameTime.startTimer();
}

void Level1::fitTextToRectangle(Text& text, RectangleShape& rectangle) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        rectangle.getPosition().x + (rectangle.getSize().x - textBounds.width) / 2,
        rectangle.getPosition().y + (rectangle.getSize().y - textBounds.height) / 2
    );
}

void Level1::fitTextToSprite(Text& text, Sprite& sprite) {
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

    text.setPosition(
        spriteBounds.left + (spriteBounds.width - textBounds.width) / 2 - textBounds.left,
        spriteBounds.top + (spriteBounds.height - textBounds.height) / 2 - textBounds.top
    );
}

void Level1::updateQuestions() {
    if (randomQuestion == 1) {
        questions->initializeQuestions();
        questionText.setString(questions->getQuestion());

        answer1Text.setString(questions->getChoices()[0]);
        answer2Text.setString(questions->getChoices()[1]);
        answer3Text.setString(questions->getChoices()[2]);
        answer4Text.setString(questions->getChoices()[3]);

        fitTextToSprite(answer1Text, button1Sprite);
        fitTextToSprite(answer2Text, button2Sprite);
        fitTextToSprite(answer3Text, button3Sprite);
        fitTextToSprite(answer4Text, button4Sprite);

        fitTextToRectangle(questionText, questionBox);
    }
    else if (randomQuestion == 2) {
        tf_questions->initializeQuestions();
        questionText.setString(tf_questions->getQuestion());
        answer1Text.setString("True");
        answer2Text.setString("False");
        fitTextToSprite(answer1Text, button1Sprite);
        fitTextToSprite(answer2Text, button2Sprite);
        fitTextToRectangle(questionText, questionBox);
    }
}

void Level1::initializeStack() {
    for (int i = 0; i < 10; i++) {
        bank.push(new TrueOrFalse("Easy"));
    }
}

void Level1::handleEvents() {
    Event event;
    Vector2i mousePos = Mouse::getPosition(window);

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (event.type == Event::MouseButtonPressed) {
            if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Return to Menu Button Clicked!" << std::endl;
                SceneManager::setState(GameState::MainMenu);
            }
            else {
                Sprite* buttons[] = { &button1Sprite, &button2Sprite, &button3Sprite, &button4Sprite };
                Text* texts[] = { &answer1Text, &answer2Text, &answer3Text, &answer4Text };

                if (randomQuestion == 1) {
                    for (int i = 0; i < 4; i++) {
                        if (buttons[i]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            if (texts[i]->getString() == questions->getAnswer()) {
                                sound.play();
                                std::cout << "Answer is correct" << std::endl;
                                countAnswer++;
                                currentScore = currentScore + 20.0;
                                SceneManager::setScore(currentScore);
                                gameTime.resetTime();
                                if (countAnswer == 8) {
                                    SceneManager::setState(GameState::Leaderboard);
                                }
                                else {
                                    window.clear();
                                    updateQuestions();
                                    render();
                                }
                            }
                            else {
                                cout << "Wrong answer !!!" << endl;
                                countAnswer++;
                                gameTime.resetTime();
                                gameTime.startTimer();
                                window.clear();
                                updateQuestions();
                                render();
                            }
                        }
                    }
                }
                else {
                    for (int i = 0; i < 2; i++) {
                        if (buttons[i]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            if (texts[i]->getString() == questions->getAnswer()) {
                                sound.play();
                                std::cout << "Answer is correct" << std::endl;
                                gameTime.resetTime();
                                gameTime.startTimer();
                                window.clear();
                                updateQuestions();
                                render();
                            }
                            else {
                                cout << "Wrong answer !!!" << endl;
                                gameTime.resetTime();
                                gameTime.startTimer();
                                window.clear();
                                updateQuestions();
                                render();
                            }
                        }
                    }
                }
            }
        }
    }
}

void Level1::update() {
    Vector2i mousePos = Mouse::getPosition(window);

    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        returnButton.setFillColor(Color::Red);
    }
    else {
        returnButton.setFillColor(Color::White);
    }

    // Update timer display
    int remainingTime = gameTime.currentTime();
    timerText.setString(std::to_string(remainingTime));

    //Handles countdown sound
    if (remainingTime <= 3) {
        timerText.setFillColor(Color::Red);

        // Play countdown sound only once when reaching 3 seconds
        if (remainingTime == 3 && !countdownSoundPlayed) {
            countdownSound.play();
            countdownSoundPlayed = true;
        }
    }
    else {
        timerText.setFillColor(Color::White);
        countdownSoundPlayed = false;  // Reset for next countdown
    }  

    if (remainingTime == 0) {
        std::cout << "Time's up!\n";
        gameTime.resetTime();
        gameTime.startTimer();
        window.clear();
        updateQuestions();
        render();
    }
    std::cout << "Timer: " << remainingTime << " seconds\n";
}

void Level1::render() {
    if (randomQuestion == 1) {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(returnButton);
        window.draw(returnText);
        window.draw(questionBox);
        window.draw(questionText);
        window.draw(button1Sprite);
        window.draw(button2Sprite);
        window.draw(button3Sprite);
        window.draw(button4Sprite);
        window.draw(answerButton1);
        window.draw(answer1Text);
        window.draw(answerButton2);
        window.draw(answer2Text);
        window.draw(answerButton3);
        window.draw(answer3Text);
        window.draw(answerButton4);
        window.draw(answer4Text);
        window.draw(timerText);
        window.display();
    }
    else {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(returnButton);
        window.draw(returnText);
        window.draw(questionBox);
        window.draw(questionText);
        window.draw(button1Sprite);
        window.draw(button2Sprite);
        window.draw(answerButton1);
        window.draw(answer1Text);
        window.draw(answerButton2);
        window.draw(answer2Text);
        window.draw(timerText);
        window.display();
    }
}