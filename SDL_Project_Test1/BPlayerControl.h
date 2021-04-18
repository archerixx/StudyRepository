#pragma once

#include "BTexture.h"

class BPlayerControl : public BGraphics
{
public:
    //Constructor
    BPlayerControl();
    //Destructor
    ~BPlayerControl();

    //SET board start position 
    void setBoardPosition(int x, int y);

    //GET current board position
    SDL_Point getBoardPosition();

    //mouse event/movement
    void handleEvent(SDL_Event* e);

    //render player board
    void renderPlayerBoard();

    //load Board image/texture
    bool loadBoardMedia();

private:
    //coordinateds of start position
    SDL_Point bBoardPosition;

    //player board texture
    BTexture* player_Board;

    //board media path
    const char* board_Media;
};
