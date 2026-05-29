#include "ScoreAndLeaderBoad.h"
#include "SceneManager.h"
#include <iostream>

using namespace std;
using namespace sf;

ScoreAndLeaderBoad::ScoreAndLeaderBoad(RenderWindow& window) : window(window) {

    // Load background image
    if (!backgroundTexture.loadFromFile("back1.jpg")) {
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
        cerr << "Failed to load font!" << endl;
        return;
    }

    //fitTextToRectangle(questionText, questionBox);

    // Button Size and Centering
    Vector2f answerButtonSize(window.getSize().x * 0.4f, 50); // 40% of screen width
    float centerX = (window.getSize().x - answerButtonSize.x) / 2;
    float startY = window.getSize().y * 0.4f; // Start at 40% of screen height
    float buttonSpacing = 60; // Space between buttons

    sf::Vector2f rankSize(600, 50);
    // rank1
    rank1Player.setPosition(rankSize);
    rank1Player.setFillColor(Color(230, 230, 250));
    rank1Player.setPosition(100, 160);
    rank1Player.setOutlineThickness(2);
    rank1Player.setOutlineColor(Color::Black);
    score1.setFont(font);
    score1.setString("0");
    score1.setCharacterSize(2);
    score1.setFillColor(Color::Black);
    score1.setPosition(110, 170);
    //fitTextToRectangle(answer1Text, answerButton1);

// rank2
    rank2Player.setPosition(rankSize);
    rank2Player.setFillColor(Color(230, 230, 250));
    rank2Player.setPosition(100, 220);
    rank2Player.setOutlineThickness(2);
    rank2Player.setOutlineColor(Color::Black);
    score2.setFont(font);
    score2.setString("0");
    score2.setCharacterSize(2);
    score2.setFillColor(Color::Black);
    score2.setPosition(110, 230);
    //fitTextToRectangle(answer2Text, answerButton2);

// Rank3
    rank3Player.setPosition(rankSize);
    rank3Player.setFillColor(Color(230, 230, 250));
    rank3Player.setPosition(100, 280);
    rank3Player.setOutlineThickness(2);
    rank3Player.setOutlineColor(Color::Black);
    score3.setFont(font);
    score3.setString("0");
    score3.setCharacterSize(2);
    score3.setFillColor(Color::Black);
    score3.setPosition(110, 290);

    //rank 4 shape
    rank4Player.setPosition(rankSize);
    rank4Player.setFillColor(Color(230, 230, 250));
    rank4Player.setPosition(100, 340);
    rank4Player.setOutlineThickness(2);
    rank4Player.setOutlineColor(Color::Black);
    score4.setFont(font);
    score4.setString("0");
    score4.setCharacterSize(2);
    score4.setFillColor(Color::Black);
    score4.setPosition(110, 350);

    //rank 5 shape
    rank5Player.setPosition(rankSize);
    rank5Player.setFillColor(Color(230, 230, 250));
    rank5Player.setPosition(100, 400);
    rank5Player.setOutlineThickness(2);
    rank5Player.setOutlineColor(Color::Black);
    score5.setFont(font);
    score5.setString("0");
    score5.setCharacterSize(2);
    score5.setFillColor(Color::Black);
    score5.setPosition(110, 410);

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
    //fitTextToRectangle(returnText, returnButton);
}

/*void ScoreAndLeaderBoad::fitTextToRectangle(Text& text, RectangleShape& rectangle) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        rectangle.getPosition().x + (rectangle.getSize().x - textBounds.width) / 2,
        rectangle.getPosition().y + (rectangle.getSize().y - textBounds.height) / 2
    );
}

void Leaderboard::updateQuestions() {

}*/

void ScoreAndLeaderBoad::handleEvents() {
    Event event;
    Vector2i mousePos = Mouse::getPosition(window);

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (event.type == Event::MouseButtonPressed) {
            if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                cout << "Return to Menu Button Clicked!" << endl;
                SceneManager::setState(GameState::MainMenu);
            }
        }
    }
}

void ScoreAndLeaderBoad::update() {
    Vector2i mousePos = Mouse::getPosition(window);

    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        returnButton.setFillColor(Color::Red);
    }
    else {
        returnButton.setFillColor(Color::White);
    }
}

void ScoreAndLeaderBoad::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(returnButton);
    window.draw(returnText);
    window.draw(rank1Player);
    window.draw(score1);
    window.draw(rank2Player);
    window.draw(score2);
    window.draw(rank3Player);
    window.draw(score3);
    window.draw(rank4Player);
    window.draw(score4);
    window.draw(rank5Player);
    window.draw(score5);
    window.display();

}
