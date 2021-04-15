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
                SDL_RenderClear(baseRenderer);

                // Viewport part
                //Top left corner viewport
                SDL_Rect topLeftViewport;
                topLeftViewport.x = 0;
                topLeftViewport.y = 0;
                topLeftViewport.w = SCREEN_WIDTH / 2;
                topLeftViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(baseRenderer, &topLeftViewport);

                //Render texture to screen
                SDL_RenderCopy(baseRenderer, baseTexture, NULL, NULL);

                //Top right viewport
                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH / 2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH / 2;
                topRightViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(baseRenderer, &topRightViewport);

                //Render texture to screen
                SDL_RenderCopy(baseRenderer, baseTexture, NULL, NULL);

                //Bottom viewport
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT / 2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(baseRenderer, &bottomViewport);

                //Render texture to screen
                SDL_RenderCopy(baseRenderer, baseTexture, NULL, NULL);

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

    //Load PNG texture
    baseTexture = iloadTexture("SDL_Image_Imports/press.png");
    if (baseTexture == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

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