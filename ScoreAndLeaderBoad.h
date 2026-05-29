#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;

class Questions {
protected:
    string question;
    string answer;
    vector<string> choices;
    vector<string> questionBank;
    string level;

public:
    int sizeOfBank;

    Questions();  // Default Constructor
    Questions(string level);  // Parameterized Constructor

    //Typewriter effect
    void drawAnimatedText(sf::RenderWindow& window, sf::Font& font, const std::string& text, float x, float y, int delayMs = 50);

    virtual void initializeQuestions();
    virtual string getQuestion();
    virtual string getAnswer();
    virtual vector<string> getChoices();
    virtual void printChoices();
    virtual vector<string> getBank();
    virtual int indexOfAnswer();

    virtual ~Questions() {};
};

class TrueOrFalse : public Questions {
public:
    TrueOrFalse();  // Default Constructor for TrueOrFalse
    TrueOrFalse(string level);

    void initializeQuestions() override;
    vector<string> getChoices() override;

    ~TrueOrFalse();
};

class FillBlank : public Questions {
private:

public:
    FillBlank();
    FillBlank(string level);

    void initializeQuestions() override;
    string getAnswer() override;
    ~FillBlank();
};
#endif
