#ifndef GAMEMENU_H
#define GAMEMENU_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Questions.h"

using namespace sf;

class GameMenu {
private:
    Text questionText;
    Questions* originalQuestions;
public:
    // Constructor
    GameMenu(sf::RenderWindow& window);

    // Event handling
    void handleEvents();

    // Update game logic
    void update();

    // Render game elements
    void render();

    // Check if we're still in the menu
    bool isInMenu() const;

    // Transition to Level1
    void startGame();
    ~GameMenu() {
        if (originalQuestions) {
            delete originalQuestions;
            originalQuestions = nullptr;
        }
    }

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    //texture
    Texture squareTexture;
    Texture panelTex, titleTex, startTex, optionsTex, creditsTex, bgCharacters;

    //sprites
    Sprite panel, title, startBtn, optionsBtn, creditsBtn, bgPic;

    // Title and shadow
    sf::Text titleTxt;
    sf::Text titleShadow;

    // Buttons
    Sprite square;

    //sf::RectangleShape playButton;
    //sf::RectangleShape quitButton;
    sf::Text playText;
    sf::Text quitText;

    bool inMenu;
};

#endif // GAMEMENU_H
