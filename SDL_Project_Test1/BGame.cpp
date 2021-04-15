#include "BGame.h"

//Texture objects
BTexture baseBackgroundTexture;

bool BGame::initWindow()
{
    //Initialization flag - check if function ends successfully
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        success = false;
    }
    else
    {
        //Create window
        baseWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, getScreenWidth(), getScreenHeight(), SDL_WINDOW_SHOWN);
        if (baseWindow == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
            success = false;
        }
        else
        {
            //Create renderer for window
            baseRenderer = SDL_CreateRenderer(baseWindow, -1, SDL_RENDERER_ACCELERATED);
            if (baseRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color (2D)
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}



bool BGame::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load background texture
    if (!baseBackgroundTexture.loadFromFile("SDL_Image_Imports/Breakout_Layout.png"))
    {
        printf("\nFailed to load background texture image!\n");
        success = false;
    }
    /*
    if (!purpleBrickTexture.loadFromFile("SDL_Image_Imports/Purple_Brick.png"))
    {
        printf("Failed to load button sprite texture!\n");
        success = false;
    }
    */
    return success;
}



void BGame::closeWindow()
{
    //Free loaded images
    //blueBrickTexture.clearTexture();
    //redBrickTexture.clearTexture();
    //yellowBrickTexture.clearTexture();
    baseBackgroundTexture.clearTexture();

    //Destroy window    
    SDL_DestroyRenderer(baseRenderer);
    SDL_DestroyWindow(baseWindow);
    baseRenderer = NULL;
    baseWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}