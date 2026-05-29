#include "GameSubLevel.h"
//#include "LevelSelect.h"
#include "Level1.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Questions.h"
#include "SceneManager.h"
#include <cstdlib>
#include <ctime>

using namespace sf;

GameSubLevel::GameSubLevel(RenderWindow& window) : window(window) {

    // Load background image
    if (!backgroundTexture.loadFromFile("SubBack.png")) {
        std::cerr << "Failed to load level 1 background image!" << std::endl;
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background to fit the window size
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    if (!easyTexture.loadFromFile("Button1.jpg") ||
        !mediumTexture.loadFromFile("Button2.jpg") ||
        !hardTexture.loadFromFile("Button3.jpg") ||
        !returnTexture.loadFromFile("Button4.jpg")) {
        return;
    }

    //fitTextToRectangle(questionText, questionBox);

    // Button Size and Centering
    Vector2f answerButtonSize(window.getSize().x * 0.4f, 50); // 40% of screen width
    float centerX = (window.getSize().x - answerButtonSize.x) / 2;
    float startY = window.getSize().y * 0.4f; // Start at 40% of screen height
    float buttonSpacing = 60; // Space between buttons

    // Easy Button 1
    easyButton.setSize(answerButtonSize);
    easyButton.setFillColor(Color::Blue);
    easyButton.setPosition(centerX, startY);
    easyButton.setOutlineThickness(2);
    easyButton.setOutlineColor(Color::Black);
    easyText.setFont(font);
    easyText.setString("Easy");
    easyText.setCharacterSize(24);
    easyText.setFillColor(Color::Black);
    fitTextToRectangle(easyText, easyButton);

    // Medium Button 2
    mediumButton.setSize(answerButtonSize);
    mediumButton.setFillColor(Color::Blue);
    mediumButton.setPosition(centerX, startY + buttonSpacing);
    mediumButton.setOutlineThickness(2);
    mediumButton.setOutlineColor(Color::Black);
    mediumText.setFont(font);
    mediumText.setString("Medium");
    mediumText.setCharacterSize(24);
    mediumText.setFillColor(Color::Black);
    fitTextToRectangle(mediumText, mediumButton);

    // Hard Button 3
    hardButton.setSize(answerButtonSize);
    hardButton.setFillColor(Color::Blue);
    hardButton.setPosition(centerX, startY + 2 * buttonSpacing);
    hardButton.setOutlineThickness(2);
    hardButton.setOutlineColor(Color::Black);
    hardText.setFont(font);
    hardText.setString("Hard");
    hardText.setCharacterSize(24);
    hardText.setFillColor(Color::Black);
    fitTextToRectangle(hardText, hardButton);

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
}

void GameSubLevel::fitTextToRectangle(Text& text, RectangleShape& rectangle) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        rectangle.getPosition().x + (rectangle.getSize().x - textBounds.width) / 2,
        rectangle.getPosition().y + (rectangle.getSize().y - textBounds.height) / 2
    );
}

/*void GameSubLevel::updateQuestions() {

}*/

void GameSubLevel::handleEvents() {
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
            else if (easyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                SceneManager::setState(GameState::GameScene);

            }
            else if (mediumButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                SceneManager::setState(GameState::GameScene);

            }
            else if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                SceneManager::setState(GameState::GameScene);
            }
        }
    }
}

void GameSubLevel::update() {
    Vector2i mousePos = Mouse::getPosition(window);

    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        returnButton.setFillColor(Color::Red);
    }
    else {
        returnButton.setFillColor(Color::White);
    }
}

void GameSubLevel::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(returnButton);
    window.draw(returnText);
    window.draw(easyButton);
    window.draw(easyText);
    window.draw(mediumButton);
    window.draw(mediumText);
    window.draw(hardButton);
    window.draw(hardText);
    window.display();

}
