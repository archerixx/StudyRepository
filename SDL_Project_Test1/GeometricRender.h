#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//The window we'll be rendering to
SDL_Window* baseWindow = NULL;
//The window renderer
SDL_Renderer* baseRenderer = NULL;
//Current displayed texture
SDL_Texture* baseTexture = NULL;
//Loads individual image
SDL_Texture* iloadTexture(const char* path);

//Starts up SDL and creates window
bool initWindow();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void closeWindow();
//run main functions
void mainFoo();

int main(int argc, char* args[])
{
    mainFoo();
    return 0;
}

void mainFoo()
{
    //Start up SDL and create window
    if (!initWindow())
    {
        std::cout << "Failed to initialize!\n";
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            std::cout << "Failed to load media!\n";
        }
        else
        {
            //Main loop flag
            bool quit = false;
            //Event handler
            SDL_Event e;

            //While application is running
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e))
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(baseRenderer);

                //Render red filled quad
                SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(baseRenderer, &fillRect);

                //Render green outlined quad
                SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
                SDL_SetRenderDrawColor(baseRenderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderDrawRect(baseRenderer, &outlineRect);

                //Draw blue horizontal line
                SDL_SetRenderDrawColor(baseRenderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderDrawLine(baseRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

                //Draw vertical line of yellow dots
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0x00, 0xFF);
                for (int i = 0; i < SCREEN_HEIGHT; i += 4)
                {
                    SDL_RenderDrawPoint(baseRenderer, SCREEN_WIDTH / 2, i);
                }

                //Update screen
                SDL_RenderPresent(baseRenderer);

            }
        }
    }
    //Free resources and close SDL
    closeWindow();
}

bool initWindow()
{
    //Initialization flag - check if function ends successfully
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        success = false;
    }
    else
    {
        // TODO: try other flags https://wiki.libsdl.org/SDL_WindowFlags
        //Create window
        baseWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

SDL_Texture* iloadTexture(const char* path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(baseRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Nothing to load
    return success;
}

void closeWindow()
{
    //Destroy loaded image/texture
    SDL_DestroyTexture(baseTexture);
    baseTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer(baseRenderer);
    SDL_DestroyWindow(baseWindow);
    baseRenderer = NULL;
    baseWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}