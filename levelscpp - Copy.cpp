#include "Level2.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Questions.h"
#include <cstdlib>
#include <ctime>

using namespace sf;

Level2::Level2(RenderWindow& window) : window(window) {

    int x = time(0);
    srand(x);
    randomQuestion = 1;

    questions = new Questions("Easy");
    tf_questions = new TrueOrFalse("Easy");
    fb_questions = new FillBlank("Easy");

    questions->initializeQuestions();

    tf_questions->initializeQuestions();
    fb_questions->initializeQuestions();
    //trueOrFalse = new TrueOrFalse("Easy");
    //typeOfQuestion.push_back(new Questions("Easy"));
    //typeOfQuestion.push_back(new TrueOrFalse("Easy"));
    //typeOfQuestion[0]->initializeQuestions();
    //typeOfQuestion[1]->initializeQuestions();

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
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    if (!Button1Texture.loadFromFile("Button1.jpg") ||
        !Button2Texture.loadFromFile("Button2.jpg") ||
        !Button3Texture.loadFromFile("Button3.jpg") ||
        !Button4Texture.loadFromFile("Button4.jpg")) {
        return;
    }

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
    Vector2f answerButtonSize(window.getSize().x * 0.4f, 50); // 40% of screen width
    float centerX = (window.getSize().x - answerButtonSize.x) / 2;
    float startY = window.getSize().y * 0.4f; // Start at 40% of screen height
    float buttonSpacing = 60; // Space between buttons
    if (randomQuestion == 1) {
        questionText.setString(questions->getQuestion());
        // Answer Button 1
        answerButton1.setSize(answerButtonSize);
        answerButton1.setFillColor(Color::Blue);
        answerButton1.setPosition(centerX, startY);
        answerButton1.setOutlineThickness(2);
        answerButton1.setOutlineColor(Color::Black);
        answer1Text.setFont(font);
        answer1Text.setString(questions->getChoices()[0]);
        answer1Text.setCharacterSize(24);
        answer1Text.setFillColor(Color::Black);
        fitTextToRectangle(answer1Text, answerButton1);

        // Answer Button 2
        answerButton2.setSize(answerButtonSize);
        answerButton2.setFillColor(Color::Blue);
        answerButton2.setPosition(centerX, startY + buttonSpacing);
        answerButton2.setOutlineThickness(2);
        answerButton2.setOutlineColor(Color::Black);
        answer2Text.setFont(font);
        answer2Text.setString(questions->getChoices()[1]);
        answer2Text.setCharacterSize(24);
        answer2Text.setFillColor(Color::Black);
        fitTextToRectangle(answer2Text, answerButton2);

        // Answer Button 3
        answerButton3.setSize(answerButtonSize);
        answerButton3.setFillColor(Color::Blue);
        answerButton3.setPosition(centerX, startY + 2 * buttonSpacing);
        answerButton3.setOutlineThickness(2);
        answerButton3.setOutlineColor(Color::Black);
        answer3Text.setFont(font);
        answer3Text.setString(questions->getChoices()[2]);
        answer3Text.setCharacterSize(24);
        answer3Text.setFillColor(Color::Black);
        fitTextToRectangle(answer3Text, answerButton3);

        // Answer Button 4
        answerButton4.setSize(answerButtonSize);
        answerButton4.setFillColor(Color::Blue);
        answerButton4.setPosition(centerX, startY + 3 * buttonSpacing);
        answerButton4.setOutlineThickness(2);
        answerButton4.setOutlineColor(Color::Black);
        answer4Text.setFont(font);
        answer4Text.setString(questions->getChoices()[3]);
        answer4Text.setCharacterSize(24);
        answer4Text.setFillColor(Color::Black);
        fitTextToRectangle(answer4Text, answerButton4);

    }
    else if (randomQuestion == 2) {//True or false
        questionText.setString(tf_questions->getQuestion());
        // Answer Button 1
        answerButton1.setSize(answerButtonSize);
        answerButton1.setFillColor(Color::Blue);
        answerButton1.setPosition(centerX, startY);
        answerButton1.setOutlineThickness(2);
        answerButton1.setOutlineColor(Color::Black);
        answer1Text.setFont(font);
        answer1Text.setString("True");
        answer1Text.setCharacterSize(24);
        answer1Text.setFillColor(Color::Black);
        fitTextToRectangle(answer1Text, answerButton1);

        // Answer Button 2
        answerButton2.setSize(answerButtonSize);
        answerButton2.setFillColor(Color::Blue);
        answerButton2.setPosition(centerX, startY + buttonSpacing);
        answerButton2.setOutlineThickness(2);
        answerButton2.setOutlineColor(Color::Black);
        answer2Text.setFont(font);
        answer2Text.setString("False");
        answer2Text.setCharacterSize(24);
        answer2Text.setFillColor(Color::Black);
        fitTextToRectangle(answer2Text, answerButton2);
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
}

void Level2::fitTextToRectangle(Text& text, RectangleShape& rectangle) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        rectangle.getPosition().x + (rectangle.getSize().x - textBounds.width) / 2,
        rectangle.getPosition().y + (rectangle.getSize().y - textBounds.height) / 2
    );
}

void Level2::updateQuestions() {
    if (randomQuestion == 1) {
        questions->initializeQuestions();
        questionText.setString(questions->getQuestion());

        answer1Text.setString(questions->getChoices()[0]);
        answer2Text.setString(questions->getChoices()[1]);
        answer3Text.setString(questions->getChoices()[2]);
        answer4Text.setString(questions->getChoices()[3]);

        fitTextToRectangle(answer1Text, answerButton1);
        fitTextToRectangle(answer2Text, answerButton2);
        fitTextToRectangle(answer3Text, answerButton3);
        fitTextToRectangle(answer4Text, answerButton4);
        fitTextToRectangle(questionText, questionBox);
    }
    else if (randomQuestion == 2) {
        tf_questions->initializeQuestions();
        questionText.setString(tf_questions->getQuestion());
        answer1Text.setString("True");
        answer2Text.setString("False");
        fitTextToRectangle(questionText, questionBox);
        fitTextToRectangle(answer1Text, answerButton1);
        fitTextToRectangle(answer2Text, answerButton2);

    }
}

void Level2::handleEvents() {
    Event event;
    Vector2i mousePos = Mouse::getPosition(window);

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (event.type == Event::MouseButtonPressed) {
            if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Return to Menu Button Clicked!" << std::endl;
                window.close();
            }
            else {
                RectangleShape* buttons[] = { &answerButton1, &answerButton2, &answerButton3, &answerButton4 };
                Text* texts[] = { &answer1Text, &answer2Text, &answer3Text, &answer4Text };

                for (int i = 0; i < 4; i++) {
                    if (buttons[i]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (texts[i]->getString() == questions->getAnswer()) {
                            std::cout << "Answer is correct" << std::endl;
                            window.clear();
                            updateQuestions();
                            render();
                        }
                        else {
                            cout << "Wrong answer !!!" << endl;
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

void Level2::update() {
    Vector2i mousePos = Mouse::getPosition(window);

    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        returnButton.setFillColor(Color::Red);
    }
    else {
        returnButton.setFillColor(Color::White);
    }
}

void Level2::render() {
    if (randomQuestion == 1) {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(returnButton);
        window.draw(returnText);
        window.draw(questionBox);
        window.draw(questionText);
        window.draw(answerButton1);
        window.draw(answer1Text);
        window.draw(answerButton2);
        window.draw(answer2Text);
        window.draw(answerButton3);
        window.draw(answer3Text);
        window.draw(answerButton4);
        window.draw(answer4Text);
        window.display();
    }
    else if (randomQuestion == 2) {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(returnButton);
        window.draw(returnText);
        window.draw(questionBox);
        window.draw(questionText);
        window.draw(answerButton1);
        window.draw(answer1Text);
        window.draw(answerButton2);
        window.draw(answer2Text);
        window.display();



    }
    else {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(returnButton);
        window.draw(returnText);
        window.draw(questionBox);
        window.draw(questionText);
        window.display();




    }

}

