#pragma once

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

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path);

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set blending
    void setBlendMode(SDL_BlendMode blending);

    //Set alpha modulation
    void setAlpha(Uint8 alpha);

    //Renders texture at given point
    void renderTexture(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};


LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError();
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(baseRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            std::cout << "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError();
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::renderTexture(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and renderTexture to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(baseRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;

LTexture gArrowTexture;

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

            //Angle of rotation
            double degrees = 0;

            //Flip type
            SDL_RendererFlip flipType = SDL_FLIP_NONE;

            //Current animation frame
            int frame = 0;

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
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_a:
                            degrees -= 60;
                            break;

                        case SDLK_d:
                            degrees += 60;
                            break;

                        case SDLK_q:
                            flipType = SDL_FLIP_HORIZONTAL;
                            break;

                        case SDLK_w:
                            flipType = SDL_FLIP_NONE;
                            break;

                        case SDLK_e:
                            flipType = SDL_FLIP_VERTICAL;
                            break;
                        }
                    }
                }


                //Clear screen
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(baseRenderer);

                SDL_Point point = { 300, 300 };

                //Render arrow
                gArrowTexture.renderTexture((SCREEN_WIDTH - gArrowTexture.getWidth()) / 2, (SCREEN_HEIGHT - gArrowTexture.getHeight()) / 2, NULL, degrees, &point, flipType);

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
            //Create vsynced renderer for window
            baseRenderer = SDL_CreateRenderer(baseWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    //Load sprite sheet texture
    if (!gArrowTexture.loadFromFile("SDL_Image_Imports/arrow.png"))
    {
        printf("Failed to load walking animation texture!\n");
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