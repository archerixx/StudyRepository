
#include "BPlayerControl.h"

BPlayerControl::BPlayerControl()
{
    //allocate memory for texture
    player_Board = new BTexture;

    //sets starting position of board
    bBoardPosition.x = getGametableWidth() / 2;
    bBoardPosition.y = getGametableHeightEnd() - getBoardHeight();

    //set path for board media
    board_Media = "SDL_Image_Imports/player_board.png";

    //load board texture
    if (!loadBoardMedia())
    {
        std::cout << "Failed to load Board Texture\n";
    }
}
BPlayerControl::~BPlayerControl()
{
    //Clear texture if it exists
    if (player_Board != NULL)
    {
        player_Board->clearTexture();
        delete player_Board;
        player_Board = NULL;
        bBoardPosition = { 0, 0 };
    }
}

void BPlayerControl::setBoardPosition(int x, int y)
{
    bBoardPosition.x = x;
    bBoardPosition.y = y;
}
SDL_Point BPlayerControl::getBoardPosition()
{
    return bBoardPosition;
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
                if (bBoardPosition.x > getGametableWidthStart() && x < bBoardPosition.x)
                {
                    bBoardPosition.x -= 10;
                    break;
                }
                //if mouse is right of board
                else if (x > bBoardPosition.x + getBoardWidth() && bBoardPosition.x < (getGametableWidthEnd()-getBoardWidth()))
                {
                    bBoardPosition.x += 10;
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
    player_Board->renderTexture(bBoardPosition.x, bBoardPosition.y);
}

bool BPlayerControl::loadBoardMedia()
{
    //Loading success flag
    bool success = true;

    //load Player Board image
    if (!player_Board->loadFromFile(board_Media))
    {
        std::cout << "Failed to load Player_Board texture!\n";
        success = false;
    }

    return success;
}