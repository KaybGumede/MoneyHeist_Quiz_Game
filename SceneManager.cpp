#include "SceneManager.h"

#include "SceneManager.h"

GameState& SceneManager::getState() {
    static GameState currentState = GameState::FirstScene;
    return currentState;
}
void SceneManager::setState(GameState newState) {
    getState() = newState;
}
double SceneManager::getScore() {
    return score;
}
void SceneManager::setScore(double& num) {
    score = score + num;
}
double SceneManager::score = 0.0;

