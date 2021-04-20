#include "BGame_Level_2.h"

BGame_Level_2::BGame_Level_2()
{
    gGame_Level_3 = new BGame(true);
    gPlayer = new BPlayerControl;
    
    start = false;
    gameOver = false;

    tempScore = 0;
    tempLives = 0;
    //gGame->getBrickLevel_2()->setPurpleBrick();

}

BGame_Level_2::~BGame_Level_2()
{
    //gGame->~BGame();
    //gPlayer->~BPlayerControl();
    //delete gGame_Level_3;
    delete gPlayer;
}
BGame* BGame_Level_2::getBall()
{
    return gGame_Level_3;
}

BPlayerControl* BGame_Level_2::getPlayer()
{
    return gPlayer;
}

void BGame_Level_2::updateLevel()
{
    for (int i = 0; i < gGame_Level_3->getBrickLevel_2()->getLevel_2()->getColumnCount(); i++)
    {
        gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->updateBrickBoarder_Y_axis(20);
        gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->updateBrickBoarder_Y_axis(20);
        gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->updateBrickBoarder_Y_axis(20);
    }
}

void BGame_Level_2::mainGameLoop(bool levelState)
{
    //Clear screen
    //SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gGame_Level_3->renderBackground();
    
    //render bricks from level
    for (int i = 0; i < gGame_Level_3->getBrickLevel_2()->getLevel_2()->getColumnCount(); i++)
    {
        //gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->renderPurpleBrick(gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->getBrickBoarderOn_X_Element(0), gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->renderYellowBrick(gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->renderBlueBrick(gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->renderRedBrick(gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
    }
    //for (int i = 0; i < 22; i++)
   // {
   //     gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->renderPurpleBrick(gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->getBrickBoarderOn_X_Element(0), gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->getBrickBoarderOn_Y_Element(0));
   // }

    
    //keep previous score
    tempScore = gGame_Level_3->getScore();
    tempLives = gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives();
    
    //ball movement/collision
    gGame_Level_3->ballMovementAndCollision(gPlayer->getBoardPosition().x, gPlayer->getBoardPosition().y, levelState);
    
    //checks if it is game over
    if (gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives() == 0)
    {
        gameOver = true;
        //load last score and number of lives
        if (gGame_Level_3->getScore() > tempScore || gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives() < tempLives)
        {
            gGame_Level_3->loadScoreAndLivesMedia(gGame_Level_3->getScore(), gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives());
        }
    }
    //if game is not lost, reset ball on board and wait for mouse click
    else if (gGame_Level_3->getLifeLostState() == true)
    {
        start = false;
    }

    //if score is changed, load and render it on screen
    if (gGame_Level_3->getScore() > tempScore || gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives() < tempLives)
    {
        gGame_Level_3->loadScoreAndLivesMedia(gGame_Level_3->getScore(), gGame_Level_3->getBrickLevel_2()->getLevel_2()->getBallLives());
    }
    gGame_Level_3->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    gGame_Level_3->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);


    //game delay, speed
    SDL_Delay(2);

    //Render player board
    gPlayer->renderPlayerBoard();

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

void BGame_Level_2::standByLoop(bool levelState)
{
    //Clear screen
    SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gGame_Level_3->renderBackground();
    gGame_Level_3->renderMenu();
    
    //render bricks from level
    for (int i = 0; i < gGame_Level_3->getBrickLevel_2()->getLevel_2()->getColumnCount(); i++)
    {
        
        gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->renderYellowBrick(gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->renderBlueBrick(gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
        gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->renderRedBrick(gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gGame_Level_3->getBrickLevel_2()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
    }
    //for (int i = 0; i < 22; i++)
    //{
    //    gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->renderPurpleBrick(gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->getBrickBoarderOn_X_Element(0), gGame->getBrickLevel_2()->getImpenetrablePurpleBrick(i)->getBrickBoarderOn_Y_Element(0));
   // }
    //render ball on board
    gGame_Level_3->setBallPoint(gPlayer->getBoardPosition().x + gGame_Level_3->getBoardWidth() / 2, gPlayer->getBoardPosition().y - gGame_Level_3->getBallSize());
    gGame_Level_3->renderBall(gPlayer->getBoardPosition().x + gGame_Level_3->getBoardWidth() / 2, gPlayer->getBoardPosition().y - gGame_Level_3->getBallSize());

    //Render player board
    gPlayer->renderPlayerBoard();

    //Render current frame
    gGame_Level_3->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    gGame_Level_3->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

void BGame_Level_2::gameOverLoop()
{
    //Clear screen
    SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
    SDL_RenderClear(baseRenderer);

    //Render background texture to screen
    gGame_Level_3->renderGameOverBackground();
    gGame_Level_3->getScoreTexture()->renderTexture(GAME_SCORE_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);
    gGame_Level_3->getLivesTexture()->renderTexture(GAME_LIVES_POSITION_X, GAME_SCORE_AND_LIVES_POSITION_Y);

    //Update screen
    SDL_RenderPresent(baseRenderer);
}

void BGame_Level_2::setGameStart(bool state)
{
    start = state;
}

bool BGame_Level_2::getGameStart()
{
    return start;
}

bool BGame_Level_2::getGameOver()
{
    return gameOver;
}
