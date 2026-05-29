#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#pragma once
#include <SFML/Graphics.hpp>
//#include <avatar.h>



enum class GameState {
    FirstScene,
    MainMenu,
    ChooseLevel,
    SubLevel,
    GameScene,
    ScoreAndLeaderboard,
    Leaderboard
};

class SceneManager {
private:
    //    vector<avatar> avatarStore;
public:
    static GameState& getState();

    static void setState(GameState newState);
    static void setScore(double& num);
    static double getScore();
    static double score;
};


#endif // SCENEMANAGER_H
