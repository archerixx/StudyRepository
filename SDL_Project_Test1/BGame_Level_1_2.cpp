#include "BGame_Level_1_2.h"

BGame_Level_1_2::BGame_Level_1_2()
{
    gBall = new BBall;
    gPlayer = new BPlayerControl;

    start = false;
    gameOver = false;

    tempScore = 0;
    tempLives = 0;
}

BGame_Level_1_2::~BGame_Level_1_2()
{
    //gBall->~BBall();
    //gPlayer->~BPlayerControl();
    delete gBall;
    delete gPlayer;
}
BBall* BGame_Level_1_2::getBall()
{
    return gBall;
}

BPlayerControl* BGame_Level_1_2::getPlayer()
{
    return gPlayer;
}

void BGame_Level_1_2::updateLevel()
{
    for (int i = 0; i < gBall->getBrick()->getLevel_1()->getColumnCount(); i++)
    {
        gBall->getBrick()->getSoftYellowBrick(i)->updateBrickBoarder_Y_axis(20);
        gBall->getBrick()->getMediumBlueBrick(i)->updateBrickBoarder_Y_axis(20);
        gBall->getBrick()->getHardRedBrick(i)->updateBrickBoarder_Y_axis(20);
    }
}

void BGame_Level_1_2::mainGameLoop()
{
    //Clear screen
    //SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gBall->renderBackground();
    
    //render bricks from level
    for (int i = 0; i < gBall->getBrick()->getLevel_1()->getColumnCount(); i++)
    {
        gBall->getBrick()->getSoftYellowBrick(i)->renderYellowBrick(gBall->getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gBall->getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
        gBall->getBrick()->getMediumBlueBrick(i)->renderBlueBrick(gBall->getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gBall->getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
        gBall->getBrick()->getHardRedBrick(i)->renderRedBrick(gBall->getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gBall->getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
    }
    
    //keep previous score
    tempScore = gBall->getScore();
    tempLives = gBall->getBrick()->getLevel_1()->getBallLives();

    //ball movement/collision
    gBall->ballMovementAndCollision(gPlayer->getBoardPosition().x, gPlayer->getBoardPosition().y);

    //checks if it is game over
    if (gBall->getBrick()->getLevel_1()->getBallLives() == 0)
    {
        gameOver = true;
        //load last score and number of lives
        if (gBall->getScore() > tempScore || gBall->getBrick()->getLevel_1()->getBallLives() < tempLives)
        {
            gBall->loadScoreAndLivesMedia(gBall->getScore(), gBall->getBrick()->getLevel_1()->getBallLives());
        }
    }
    //if game is not lost, reset ball on board and wait for mouse click
    else if (gBall->getLifeLostState() == true)
    {
        start = false;
    }

    //if score is changed, load and render it on screen
    if (gBall->getScore() > tempScore || gBall->getBrick()->getLevel_1()->getBallLives() < tempLives)
    {
        gBall->loadScoreAndLivesMedia(gBall->getScore(), gBall->getBrick()->getLevel_1()->getBallLives());
    }
    gBall->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    gBall->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);


    //game delay, speed
    SDL_Delay(2);

    //Render player board
    gPlayer->renderPlayerBoard();

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

void BGame_Level_1_2::standByLoop()
{
    //Clear screen
    //SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gBall->renderBackground();
    gBall->renderMenu();
    
    //render bricks from level
    for (int i = 0; i < gBall->getBrick()->getLevel_1()->getColumnCount(); i++)
    {
        gBall->getBrick()->getSoftYellowBrick(i)->renderYellowBrick(gBall->getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gBall->getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
        gBall->getBrick()->getMediumBlueBrick(i)->renderBlueBrick(gBall->getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gBall->getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
        gBall->getBrick()->getHardRedBrick(i)->renderRedBrick(gBall->getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gBall->getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
    }
    
    //render ball on board
    gBall->setBallPoint(gPlayer->getBoardPosition().x + gBall->getBoardWidth() / 2, gPlayer->getBoardPosition().y - gBall->getBallSize());
    gBall->renderBall(gPlayer->getBoardPosition().x + gBall->getBoardWidth() / 2, gPlayer->getBoardPosition().y - gBall->getBallSize());

    //Render player board
    gPlayer->renderPlayerBoard();

    //Render current frame
    //gBall->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    //gBall->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

void BGame_Level_1_2::gameOverLoop()
{   
    //Clear screen
    SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gBall->renderGameOverBackground();
    gBall->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    gBall->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

void BGame_Level_1_2::setGameStart(bool state)
{
    start = state;
}

bool BGame_Level_1_2::getGameStart()
{
    return start;
}

bool BGame_Level_1_2::getGameOver()
{
    return gameOver;
}
