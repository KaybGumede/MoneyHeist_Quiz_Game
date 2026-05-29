#include "Questions.h"
#include <random>

Questions::Questions(string level)
{
    this->level = level;
    if (level == "Easy") {
        ifstream file("Easy.txt");
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
        }
        else {
            while (getline(file, question)) {
                questionBank.push_back(question);
            }
        }
        file.close();
    }
    else if (level == "Medium") {
        ifstream file("Medium.txt");
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
        }
        else {
            while (getline(file, question)) {
                questionBank.push_back(question);
            }
        }
        file.close();
    }
    else if (level == "Hard") {
        ifstream file("Hard.txt");
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
        }
        else {
            while (getline(file, question)) {
                questionBank.push_back(question);
            }
        }
        file.close();
    }
    if (questionBank.size() == 0) {
        cout << "file not read" << endl;
    }
    sizeOfBank = questionBank.size();
}


int Questions::indexOfAnswer() {
    int i;
    for (i = 0; i < choices.size(); i++) {
        if (answer == choices[i]) {
            break;
        }
    }return i + 1;
}

string Questions::getQuestion() { return question; }
string Questions::getAnswer() { return answer; }
vector<string> Questions::getChoices() { return choices; }
vector<string> Questions::getBank() { return questionBank; }

void Questions::initializeQuestions() {
    choices.clear();
    string randomQuestion;

    random_device rd;
    mt19937 gen(rd());
    // Define a range (e.g., 1 to 10)
    uniform_int_distribution<int> dist(1, sizeOfBank);
    // Generate a random number
    int randomNumber = dist(gen);
    cout << "Random number is: " << randomNumber << endl;

    randomQuestion = questionBank[randomNumber];
    int atPos = randomQuestion.find('@');
    int andPos = randomQuestion.find('&');
    question = randomQuestion.substr(0, atPos);
    answer = randomQuestion.substr(atPos + 1, andPos - atPos - 1);
    string choicesString = randomQuestion.substr(andPos + 1);
    stringstream ss(choicesString);
    string choice;
    while (getline(ss, choice, ',')) {
        choices.push_back(choice);
        cout << choice << endl;
    }

}
void Questions::printChoices() {
    string letters = "1234";
    cout << "Choose one number from 1 to 4 \n";
    for (int i = 0; i < choices.size(); i++) {
        cout << letters[i] << ": " << choices[i] << endl;
    }
}
int calculateScore(double time_taken) {
    if (time_taken < 5) return 10; // Fast answer
    else if (time_taken < 10) return 5; // Moderate speed
    else return 2; // Slow answer
}




//TrueOrFalse Class

TrueOrFalse::TrueOrFalse() : Questions("tf_Easy.txt") {}

TrueOrFalse::TrueOrFalse(string level) : Questions(level) {
    this->level = level;
    if (level == "Easy") {
        ifstream file("tf_Easy.txt");
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
        }
        else {
            while (getline(file, question)) {
                questionBank.push_back(question);
            }
        }
        file.close();
    }
    else if (level == "Medium") {
        ifstream file("Medium.txt");
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
        }
        else {
            while (getline(file, question)) {
                questionBank.push_back(question);
            }
        }
        file.close();
    }
    else if (level == "Hard") {
        ifstream file("Hard.txt");
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
        }
        else {
            while (getline(file, question)) {
                questionBank.push_back(question);
            }
        }
        file.close();
    }
    if (questionBank.size() == 0) {
        cout << "file not read" << endl;
    }
    sizeOfBank = questionBank.size();
}

TrueOrFalse::~TrueOrFalse() {}

void TrueOrFalse::initializeQuestions() {
    choices = { "True", "False" };

    if (sizeOfBank == 0) {
        cout << "No questions available!" << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, sizeOfBank - 1);

    int randomNumber = dist(gen);
    cout << "Random number is: " << randomNumber << endl;

    string randomQuestion = questionBank[randomNumber];
    int atPos = randomQuestion.find('@');

    if (atPos == string::npos) {
        cout << "Invalid question format!" << endl;
        return;
    }

    question = randomQuestion.substr(0, atPos);
    answer = randomQuestion.substr(atPos + 1);
}
// TrueOrFalse getChoices Override
vector<string> TrueOrFalse::getChoices() {
    return { "True", "False" };
}

//optional
//FillBlank Class
FillBlank::FillBlank() : Questions("Easy") {}

FillBlank::FillBlank(string level) : Questions(level) {}
FillBlank::~FillBlank() {}

string FillBlank::getAnswer() {
    return answer;
}

void FillBlank::initializeQuestions() {
    choices = { "True", "False" };

    if (sizeOfBank == 0) {
        cout << "No questions available!" << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, sizeOfBank - 1); // Fix range

    int randomNumber = dist(gen);
    cout << "Random number is: " << randomNumber << endl;

    string randomQuestion = questionBank[randomNumber];
    int atPos = randomQuestion.find('@');

    if (atPos == string::npos) {
        cout << "Invalid question format!" << endl;
        return;
    }

    question = randomQuestion.substr(0, atPos);
    answer = randomQuestion.substr(atPos + 1);
}