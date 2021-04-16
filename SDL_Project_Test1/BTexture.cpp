#include "BTexture.h"


BTexture::BTexture()
{
    //Initialize
    iTexture = NULL;
    iWidth = 0;
    iHeight = 0;
}

BTexture::~BTexture()
{
    //Deallocate
    clearTexture();
}

bool BTexture::loadFromFile(const char* path)
{
    //Get rid of preexisting texture
    clearTexture();

    //The final texture
    //SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image %s! SDL_image Error: %s\n" << path << "\n" << IMG_GetError();
    }
    else
    {
        //Color key image, blends specific color of image (in this case "black")
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
        
        //Create texture from surface pixels
        iTexture = SDL_CreateTextureFromSurface(baseRenderer, loadedSurface);
        if (iTexture == NULL)
        {
            std::cout << "Unable to create texture from %s! SDL Error: %s\n" << path << "\n"<< SDL_GetError();
        }
        else
        {
            //Get image dimensions
            iWidth = loadedSurface->w;
            iHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    //iTexture = newTexture;
    return iTexture != NULL;
}

bool BTexture::loadFromRenderedText(const char* textureText, SDL_Color textColor)
{
    //Get rid of preexisting texture
    clearTexture();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(baseFont, textureText, textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Color key image, blends specific color of image (in this case "black")
        SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 0, 0, 0));

        //Create texture from surface pixels
        iTexture = SDL_CreateTextureFromSurface(baseRenderer, textSurface);
        if (iTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            iWidth = textSurface->w;
            iHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return iTexture != NULL;
}

void BTexture::clearTexture()
{
    //Clear texture if it exists
    if (iTexture != NULL)
    {
        SDL_DestroyTexture(iTexture);
        iTexture = NULL;
        iWidth = 0;
        iHeight = 0;
    }
}

void BTexture::renderTexture(int x, int y)
{
    //Set rendering space and renderTexture to screen (x, y represent position and iWidth/iHeight size of texture)
    SDL_Rect renderQuad = { x, y, iWidth, iHeight };
    SDL_RenderCopy(baseRenderer, iTexture, NULL, &renderQuad);
}

int BTexture::getTextureWidth() const
{
    return iWidth;
}

int BTexture::getTextureHeight() const
{
    return iHeight;
}

BTexture& BTexture::operator=(const BTexture& org)
{
    //if 
    if (this == &org)
    {
        return *this;
    }
    else
    {
        SDL_DestroyTexture(iTexture);
        iTexture = NULL;

        this->iTexture = org.iTexture;
        this->iWidth = org.iWidth;
        this->iHeight = org.iHeight;

        return *this;
    }
}