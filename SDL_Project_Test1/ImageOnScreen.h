#pragma once

#include <sdl\SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//The window we'll be rendering to
SDL_Window* baseWindow = NULL;

//The surface contained by the window
SDL_Surface* baseScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* iHelloWorld = NULL;

//Starts up SDL and creates window
bool initWindow();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void closeWindow();

//call base functions
void ImageOnScreenFoo();

//what should main look like
/*
int main()
{
	ImageOnScreenFoo();
	return 0;
}
*/

void ImageOnScreenFoo()
{
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //Start up SDL and create window
    if (!initWindow())
    {
        std::cout << ("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            std::cout << ("Failed to load media!\n");
        }
        else
        {
            //While application is running
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                //Apply the image
                SDL_BlitSurface(iHelloWorld, NULL, baseScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(baseWindow);

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
        std::cout << ("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // TODO: try other flags https://wiki.libsdl.org/SDL_WindowFlags
        //Create window
        baseWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (baseWindow == NULL)
        {
            std::cout << ("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            baseScreenSurface = SDL_GetWindowSurface(baseWindow);
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    iHelloWorld = SDL_LoadBMP("SDL_Image_Imports/my_name.bmp");
    if (iHelloWorld == NULL)
    {
        std::cout << ("Unable to load image %s! SDL Error: %s\n", "SDL_Image_Imports/my_name.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void closeWindow()
{
    //Deallocate surface
    SDL_FreeSurface(iHelloWorld);
    iHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow(baseWindow);
    baseWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}