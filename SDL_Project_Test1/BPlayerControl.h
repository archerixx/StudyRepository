#pragma once

#include "BTexture.h"

class BPlayerControl : protected BGraphics, public BTexture
{
public:
    BPlayerControl();

    //SET start position 
    void setBoardPosition(int x, int y);

    //GET current board position
    SDL_Point getBoardPosition();

    //mouse event/movement
    void handleEvent(SDL_Event* e);

    //shows player board, moving around
    void renderPlayerBoard();

    //load Board image/texture
    bool loadBoardMedia();

    BGraphics BGraph;

private:
    //coordinateds of start position
    SDL_Point mPosition;

    //player board texture
    BTexture player_Board;

};
