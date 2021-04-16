#pragma once

#include "BGraphics.h"

class BTexture
{
private:
    //The actual hardware texture
    SDL_Texture* iTexture;

    //Image dimensions
    int iWidth;
    int iHeight;

public:
    //Initializes variables
    BTexture();

    //Deallocates memory
    ~BTexture();

    //Loads image at specified path
    bool loadFromFile(const char* path);

    //Creates image from font string
    bool loadFromRenderedText(const char* textureText, SDL_Color textColor);

    //Deallocates texture
    void clearTexture();

    //Renders texture at given point
    void renderTexture(int x, int y);

    //Gets image dimensions
    int getTextureWidth() const;
    int getTextureHeight() const;

    //override '=' operator
    BTexture& operator=(const BTexture& org);
};

