#include "Level1.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Questions.h"
#include "ChooseLevel.h"
#include "SceneManager.h"
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

ChooseLevel::ChooseLevel(RenderWindow& window) : window(window) {

    // Load background image
    if (!backgroundTexture.loadFromFile("BG.png")) {
        cerr << "Failed to load level 1 background image!" << endl;
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
        cerr << "Failed to load font!" << endl;
        return;
    }

    if (!level1Texture.loadFromFile("ButtonA.png") ||
        !level2Texture.loadFromFile("btnSquare1.png") ||
        !level3Texture.loadFromFile("btnSquare1.png") ||
        !returnTexture.loadFromFile("btnSquare1.png")
        ) {
        return;
    }

    //fitTextToRectangle(questionText, questionBox);

    // Button Size and Centering
    answerButtonSize.x = (window.getSize().x * 0.24f);answerButtonSize.y = (window.getSize().y * 0.30f);
    float centerX = (window.getSize().x - answerButtonSize.x) / 2;
    float startY = window.getSize().y * 0.4f; // Start at 40% of screen height
    float buttonSpacing = 60; // Space between buttons

    // Level 1 Button Button
    level1Sprite.setTexture(level1Texture);
    level1Sprite.setPosition(0, 0);
    level1Sprite.setScale(.7f, .7f);


    /*level1Button.setSize(answerButtonSize);
    level1Button.setFillColor(Color::Cyan);
    level1Button.setPosition(centerX-(window.getSize().x*0.34f), startY);
    level1Button.setOutlineThickness(2);
    level1Button.setOutlineColor(Color::Black);
    level1Text.setFont(font);
    level1Text.setString("Level 1");
    level1Text.setCharacterSize(24);
    level1Text.setFillColor(Color::Black);
    fitTextToRectangle(level1Text, level1Button);*/

    // Level 2 Button
    level2Button.setSize(answerButtonSize);
    level2Button.setFillColor(Color::Cyan);
    level2Button.setPosition(centerX, startY);
    level2Button.setOutlineThickness(2);
    level2Button.setOutlineColor(Color::Black);
    level2Text.setFont(font);
    level2Text.setString("Level 2");
    level2Text.setCharacterSize(24);
    level2Text.setFillColor(Color::Black);
    fitTextToRectangle(level2Text, level2Button);

    // Level3 Button
    level3Button.setSize(answerButtonSize);
    level3Button.setFillColor(Color::Cyan);
    level3Button.setPosition(centerX + (window.getSize().x * 0.34f), startY);
    level3Button.setOutlineThickness(2);
    level3Button.setOutlineColor(Color::Black);
    level3Text.setFont(font);
    level3Text.setString("Level 3");
    level3Text.setCharacterSize(24);
    level3Text.setFillColor(Color::Black);
    fitTextToRectangle(level3Text, level3Button);

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
void ChooseLevel::fitTextToRectangle(Text& text, RectangleShape& rectangle) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        rectangle.getPosition().x + (rectangle.getSize().x - textBounds.width) / 2,
        rectangle.getPosition().y + (rectangle.getSize().y - textBounds.height) / 2
    );
}

/*void ChooseLevel::updateQuestions() {

}*/

void ChooseLevel::handleEvents() {
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
            else if (level1Sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                SceneManager::setState(GameState::SubLevel);
            }
            else if (level2Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                SceneManager::setState(GameState::SubLevel);
            }
            else if (level3Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                SceneManager::setState(GameState::SubLevel);
            }
        }
    }
}

void ChooseLevel::update() {
    Vector2i mousePos = Mouse::getPosition(window);
    answerButtonSize.x = (window.getSize().x * 0.24f);answerButtonSize.y = (window.getSize().y * 0.30f);
    float centerX = (window.getSize().x - answerButtonSize.x) / 2;
    float startY = window.getSize().y * 0.4f;

    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        returnButton.setFillColor(Color::Red);
    }
    else {
        returnButton.setFillColor(Color::White);
    }
    if (level1Sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        setButtonSize.x = window.getSize().x * 0.26f;
        setButtonSize.y = window.getSize().y * 0.40f;
        level1Sprite.setScale(window.getSize().x * 0.26f, window.getSize().y * 0.40f);

    }
    else {
        level1Sprite.setScale(centerX - (window.getSize().x * 0.34f), startY);
    }
    if (level2Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        setButtonSize.x = window.getSize().x * 0.26f;
        setButtonSize.y = window.getSize().y * 0.40f;
        level2Button.setSize(setButtonSize);

    }
    else {
        level2Button.setSize(answerButtonSize);
    }
    if (level3Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        setButtonSize.x = window.getSize().x * 0.26f;
        setButtonSize.y = window.getSize().y * 0.40f;
        level3Button.setSize(setButtonSize);

    }
    else {
        level3Button.setSize(answerButtonSize);
    }
}

void ChooseLevel::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(returnButton);
    window.draw(returnText);
    //window.draw(level1Button);
    window.draw(level1Sprite);
    window.draw(level1Text);
    window.draw(level2Button);
    window.draw(level2Text);
    window.draw(level3Button);
    window.draw(level3Text);
    window.display();


}
