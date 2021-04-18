#pragma once

#include "BGraphics.h"

class BTexture
{
public:
    //Initializes variables
    BTexture();

    //Deallocates memory
    ~BTexture();

    //Deallocates texture
    void clearTexture();

    //Loads image at specified path
    bool loadFromFile(const char* path);

    //Creates image from font string
    bool loadFromRenderedText(const char* textureText, SDL_Color textColor);

    //Renders texture at given point
    void renderTexture(int x, int y);

private:
    //The actual hardware texture
    SDL_Texture* iTexture;

    //Image dimensions
    int iWidth;
    int iHeight;
};

