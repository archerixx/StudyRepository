#pragma once

#include "BPlayerControl.h"
#include "BBall.h"

class BGame_Level_1_2
{
public:
    BGame_Level_1_2();
    ~BGame_Level_1_2();

    BBall* getBall();
    BPlayerControl* getPlayer();

    void updateLevel();

    void mainGameLoop();
    void standByLoop();
    void gameOverLoop();

    void setGameStart(bool state);
    bool getGameStart();

    bool getGameOver();
private:
	BBall* gBall;
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