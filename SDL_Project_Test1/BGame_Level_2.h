#pragma once

#include "BPlayerControl.h"
#include "BGame.h"

class BGame_Level_2
{
public:
    BGame_Level_2();
    ~BGame_Level_2();

    BGame* getBall();
    BPlayerControl* getPlayer();

    void updateLevel();
    void mainGameLoop(bool levelState);
    void standByLoop(bool levelState);
    void gameOverLoop();

    void setGameStart(bool state);
    bool getGameStart();

    bool getGameOver();
private:
    BGame* gGame_Level_3;
    BPlayerControl* gPlayer;

    //Start game flag
    bool start;
    //Gameover flag
    bool gameOver;

    //temp values for score and lives
    int tempScore;
    int tempLives;

    const int GAME_SCORE_POSITION_X = 730;
    const int GAME_LIVES_POSITION_X = 50;
    const int GAME_SCORE_AND_LIVES_POSITION_Y = 530;
};