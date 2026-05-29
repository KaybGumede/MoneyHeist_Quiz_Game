#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameMenu.h"
#include "Level1.h"
#include "Level2.h"
#include "FirstScene.h"
#include "SceneManager.h"
#include "ChooseLevel.h"
#include "GameSubLevel.h"
#include "ScoreAndLeaderBoad.h"
#include "Leaderboard.h"


/*enum class GameState {
    FirstScene,
    MainMenu,
    LevelSelect,
    SubLevel,
    Game,
    ScoreBoard,
    Leaderboard
};

GameState currentState = GameState::Splash;*/


int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "C++ Money Heist", sf::Style::Fullscreen);
    GameMenu menu(window);
    Level1* level1 = nullptr; // Pointer to Level1, initially null
    Level2* level2 = nullptr;
    FirstScene* intro = nullptr;
    ChooseLevel* chooseLevel = nullptr;
    GameSubLevel* subLevel = nullptr;
    ScoreAndLeaderBoad* afterGame = nullptr;
    Leaderboard* leaderboard = nullptr;



    /*while (window.isOpen()) {
        if (menu.isInMenu()) {
            menu.handleEvents();
            menu.update();
            menu.render();
        } else {
            if (!level1) {  // Only create Level1 once when switching from the menu
                level1 = new Level1(window);
            }
            level1->handleEvents();
            level1->update();
            level1->render();
        }
    }

    // Clean up dynamically allocated memory
    if (level1) {
        delete level1;
        level1 = nullptr;
    }*/
    while (window.isOpen()) {
        switch (SceneManager::getState()) {
        case GameState::FirstScene:
            // render splash screen or intro
            // on completion/input: currentState = GameState::MainMenu;
            if (!intro) {
                intro = new FirstScene(window);
            }
            intro->handleEvents();
            intro->update();
            intro->render();
            break;
        case GameState::MainMenu:
            // Use GameMenu class here
            menu.handleEvents();
            menu.update();
            menu.render();
            break;
        case GameState::ChooseLevel:
            // Create ChooseLevel scene (custom class, like GameMenu)
            if (!chooseLevel) {
                chooseLevel = new ChooseLevel(window);
            }
            chooseLevel->handleEvents();
            chooseLevel->update();
            chooseLevel->render();

            break;
        case GameState::SubLevel:
            // Choose sub-levels
            if (!level1) {  // Only create Level1 once when switching from the menu
                level1 = new Level1(window);
            }
            level1->handleEvents();
            level1->update();
            level1->render();
            break;
        case GameState::GameScene:
            // Play actual game via Level1, Level2, etc.
                /*if (!gamePlay) {  // Only create Level1 once when switching from the menu
                gamePlay = new GameScene(window);
                }
                gamePlay->handleEvents();
                gamePlay->update();
                gamePlay->render();
                if (!level1) {  // Only create Level1 once when switching from the menu
                level1 = new Level1(window);
                }
                level1->handleEvents();
                level1->update();
                level1->render();*/
                //if(!level)

            break;
        case GameState::ScoreAndLeaderboard:
            // Show score after game ends, provide option to view leaderboard
            if (!afterGame) {
                afterGame = new ScoreAndLeaderBoad(window);
            }
            afterGame->handleEvents();
            afterGame->update();
            afterGame->render();
            break;
        case GameState::Leaderboard:
            // Show leaderboard
            if (!leaderboard) {
                leaderboard = new Leaderboard(window);
            }
            leaderboard->handleEvents();
            leaderboard->update();
            leaderboard->render();
            break;
        }
    }

    delete intro;
    delete level1;
    delete level2;

    return 0;
}



