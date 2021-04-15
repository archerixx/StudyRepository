
#include "BPlayerControl.h"

BPlayerControl::BPlayerControl()
{
    //setting starting position of board
    mPosition.x = 370;
    mPosition.y = 570;

    loadBoardMedia();
}

void BPlayerControl::setBoardPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

SDL_Point BPlayerControl::getBoardPosition()
{
    return mPosition;
}

void BPlayerControl::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEMOTION)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in area of game and move board left/right
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            //if mouse is left of board
            if (mPosition.x > getGametableWidthStart() && x < mPosition.x)
            {
                mPosition.x -= 10;
                break;
            }
            //if mouse is right of board
            else if (x > mPosition.x + getBoardWidth() && mPosition.x < (getGametableWidthEnd()-getBoardWidth()))
            {
                mPosition.x += 10;
                break;
            }
        default:
            break;
        }
    }
}

void BPlayerControl::renderPlayerBoard()
{   
    //render player board texture in BTexture class
    player_Board.renderTexture(mPosition.x, mPosition.y);
}

bool BPlayerControl::loadBoardMedia()
{
    //Loading success flag
    bool success = true;

    //load Player Board image
    if (!player_Board.loadFromFile("SDL_Image_Imports/player_board.png"))
    {
        printf("Failed to load Player_Board texture!\n");
        success = false;
    }

    return success;
}