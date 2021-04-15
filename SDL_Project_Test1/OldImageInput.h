#include <sdl\SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//The window we'll be rendering to
SDL_Window* baseWindow = NULL;
//The surface contained by the window
SDL_Surface* baseScreenSurface = NULL;
//Loads individual image
SDL_Surface* iloadSurface(std::string path);
//The images that correspond to a keypress
SDL_Surface* iKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
//Current displayed image
SDL_Surface* iCurrentSurface = NULL;

SDL_Surface* iHelloWorld = NULL; //should we replaced/deleted

//Starts up SDL and creates window
bool initWindow();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void closeWindow();
//run main functions
void ImageOnScreenFoo();

int main(int argc, char* args[])
{
    ImageOnScreenFoo();
    return 0;
}

void ImageOnScreenFoo()
{
    //Start up SDL and create window
    if (!initWindow())
    {
        std::cout << ("Failed to initialize!\n");
    }
    else
    {
        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        //Set default current surface
        iCurrentSurface = iKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

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
                while (SDL_PollEvent(&e))
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    //User presses a key
                    else if (e.type == SDL_KEYDOWN)
                    {
                        //Select surfaces based on key press
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            iCurrentSurface = iKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;

                        case SDLK_DOWN:
                            iCurrentSurface = iKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;

                        case SDLK_LEFT:
                            iCurrentSurface = iKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;

                        case SDLK_RIGHT:
                            iCurrentSurface = iKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                        default:
                            iCurrentSurface = iKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }

                //Apply the image
                SDL_BlitSurface(iCurrentSurface, NULL, baseScreenSurface, NULL);

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

//TODO - try to clean it up, so it doesnt take this many lines
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    iKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = iloadSurface("SDL_Image_Imports/press.bmp");
    if (iKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        std::cout << ("Failed to load 'press' image!\n");
        success = false;
    }

    //Load up surface
    iKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = iloadSurface("SDL_Image_Imports/up.bmp");
    if (iKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        std::cout << ("Failed to load 'up' image!\n");
        success = false;
    }

    //Load down surface
    iKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = iloadSurface("SDL_Image_Imports/down.bmp");
    if (iKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        std::cout << ("Failed to load 'down' image!\n");
        success = false;
    }

    //Load left surface
    iKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = iloadSurface("SDL_Image_Imports/left.bmp");
    if (iKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        std::cout << ("Failed to load 'left' image!\n");
        success = false;
    }

    //Load right surface
    iKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = iloadSurface("SDL_Image_Imports/right.bmp");
    if (iKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        std::cout << ("Failed to load 'right' image!\n");
        success = false;
    }

    return success;
}

SDL_Surface* iloadSurface(std::string path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str()); //need to experiment here
    if (loadedSurface == NULL)
    {
        std::cout << ("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return loadedSurface;
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