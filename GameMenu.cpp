#include "GameMenu.h"
#include "Level1.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "Questions.h"
#include "SceneManager.h"

using namespace std;
using namespace sf;

GameMenu::GameMenu(sf::RenderWindow& window) : window(window), inMenu(true) {
    // Load background texture and set it to the sprite
    if (!backgroundTexture.loadFromFile("BG.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        exit(-1);
    }
    if (!bgCharacters.loadFromFile("bgChar.png") ||
        !panelTex.loadFromFile("assets/panel.png") ||
        !titleTex.loadFromFile("assets/title_bar.png") ||
        !startTex.loadFromFile("assets/btn_start.png") ||
        !optionsTex.loadFromFile("assets/btn_options.png") ||
        !creditsTex.loadFromFile("assets/btn_credits.png")) {
        std::cerr << "Failed to load one or more images.\n";
    }


    if (!squareTexture.loadFromFile("button_square_flatRed.png")) {
        std::cerr << "Failed to load play button image!" << std::endl;
    }

    Vector2f answerButtonSize(window.getSize().x * 0.4f, 50); // 40% of screen width
    float centerX = (window.getSize().x - answerButtonSize.x) / 2;
    float startY = window.getSize().y * 0.4f; // Start at 40% of screen height

    //Sprites
    panelTex.setSmooth(true);
    panel.setTexture(panelTex);
    panel.setPosition(centerX, window.getSize().y * 0.50f); // center-ish
    title.setTexture(titleTex);
    title.setPosition(centerX, window.getSize().y * 0.4f); // same X as panel
    startBtn.setTexture(startTex);
    startBtn.setPosition(centerX, window.getSize().y * 0.5f);
    startBtn.setScale(.7f, .7f);
    optionsBtn.setTexture(optionsTex);
    optionsBtn.setPosition(centerX, window.getSize().y * 0.59f);
    optionsBtn.setScale(.7f, .7f);
    creditsBtn.setTexture(creditsTex);
    creditsBtn.setPosition(centerX, window.getSize().y * 0.68f);
    creditsBtn.setScale(.7f, .7f);
    bgPic.setTexture(bgCharacters);
    bgPic.setPosition(window.getSize().x * 0.4f, window.getSize().y * 0.1f);
    bgPic.setScale(2.0f, 2.5f);

    square.setTexture(squareTexture);
    square.setPosition(centerX, startY);
    square.setScale(2.5f, 2.5f);


    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    ); // Adjust the background to fit the window size

    // Load font
    if (!font.loadFromFile("Dallia.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        exit(-1);
    }

    // Title text with shadow effect
    titleTxt.setFont(font);
    titleTxt.setString("The Compiler Conspiracy");
    titleTxt.setCharacterSize(60);
    titleTxt.setFillColor(sf::Color::Yellow);
    titleTxt.setStyle(sf::Text::Bold);
    titleTxt.setPosition(50, 80);

    titleShadow = titleTxt;
    titleShadow.setFillColor(sf::Color::Black);
    titleShadow.setPosition(title.getPosition().x + 3, title.getPosition().y + 3);

    // Play Button Setup
    /*playButton.setSize(sf::Vector2f(200, 50));
    playButton.setFillColor(sf::Color::White);
    playButton.setPosition(300, 250);
    playButton.setOutlineThickness(3);
    playButton.setOutlineColor(sf::Color::Black);*/

    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::Black);
    playText.setPosition(centerX + 100, window.getSize().y * 0.52f);

    // Quit Button Setup
    /*quitButton.setSize(sf::Vector2f(200, 50));
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition(300, 350);
    quitButton.setOutlineThickness(3);
    quitButton.setOutlineColor(sf::Color::Black);*/

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(30);
    quitText.setFillColor(sf::Color::Black);
    quitText.setPosition(centerX + 100, window.getSize().y * 0.7f);
}

void GameMenu::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (startBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                SceneManager::setState(GameState::ChooseLevel);
                //startGame();
            }
            if (creditsBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                window.close();
            }
        }
    }
}

void GameMenu::update() {
    // Handle hover effects
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //playButton.setFillColor(playButton.getGlobalBounds().contains(mousePos.x, mousePos.y) ? sf::Color::Green : sf::Color::White);
    //quitButton.setFillColor(quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y) ? sf::Color::Red : sf::Color::White);
}

void GameMenu::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(bgPic);
    window.draw(titleShadow);  // Draw shadow first
    //window.draw(title);// Then draw the main title
    //window.draw(square);
    //sprites
    //window.draw(panel);
    //window.draw(title);
    window.draw(startBtn);
    window.draw(optionsBtn);
    window.draw(creditsBtn);

    //window.draw(playButton);
    window.draw(playText);
    //window.draw(quitButton1);
    window.draw(quitText);
    window.display();
}

bool GameMenu::isInMenu() const {
    return inMenu;
}

void GameMenu::startGame() {
    inMenu = false;// Transition to the game
    SceneManager::setState(GameState::ChooseLevel);
}
