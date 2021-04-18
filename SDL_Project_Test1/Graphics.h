#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 648;

//game table dimension constants
const int GAMETABLE_WIDTH = 600;
const int GAMETABLE_HEIGHT = 550;

//game player board dimension constants
const int BOARD_WIDTH = 60;
const int BOARD_HEIGHT = 10;

//The window we'll be rendering to
SDL_Window* baseWindow = NULL;
//The window renderer
SDL_Renderer* baseRenderer = NULL;

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(const char* path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void renderTexture(int x, int y, SDL_Rect* clip = NULL);

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

bool LTexture::loadFromFile(const char* path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError();
    }
    else
    {
       
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(baseRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            std::cout << "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError();
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

void LTexture::renderTexture(int x, int y, SDL_Rect* clip)
{
    //Set rendering space and renderTexture to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(baseRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

//Scene textures
LTexture blueBrickTexture;
LTexture redBrickTexture;
LTexture yellowBrickTexture;
LTexture baseBackgroundTexture;
LTexture player_Board;


class LMouseMotion
{
public:
    LMouseMotion();

    //start position that will be in relation to actual mouse position
    void setPosition(int x, int y);

    //mouse event/movement
    void handleEvent(SDL_Event* e);

    //shows player board, moving around
    void renderTexture();

private:
    //coordinateds of start position
    SDL_Point bBoardPosition;

};

LMouseMotion::LMouseMotion()
{
    bBoardPosition.x = 370;
    bBoardPosition.y = 570;

}

void LMouseMotion::setPosition(int x, int y)
{
    bBoardPosition.x = x;
    bBoardPosition.y = y;
}

void LMouseMotion::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEMOTION)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in area of game
        bool inside = true;
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            if (x < bBoardPosition.x)
            {
                bBoardPosition.x= bBoardPosition.x-10;
                if (bBoardPosition.x == 90)
                    bBoardPosition.x = bBoardPosition.x+10;
                inside = false;
            }
            else if (x > bBoardPosition.x + BOARD_WIDTH)
            {
                bBoardPosition.x= bBoardPosition.x+10;
                if (bBoardPosition.x == 610)
                    bBoardPosition.x = bBoardPosition.x - 10;
                inside = false;
            }
            else if (y < bBoardPosition.y)
            {
                inside = false;
            }
            else if (y > bBoardPosition.y + BOARD_HEIGHT)
            {
                inside = false;
            }
        default:
            break;
        }
    }
}

void LMouseMotion::renderTexture()
{
    player_Board.renderTexture(bBoardPosition.x, bBoardPosition.y);
}

LMouseMotion gButtons;

//Starts up SDL and creates window
bool initWindow();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void closeWindow();
//game functions
void game();

void game()
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
                    //Handle button events
                    gButtons.handleEvent(&e);
                }

                //Clear screen
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(baseRenderer);

                //Render background texture to screen
                baseBackgroundTexture.renderTexture(0, 0);

                //Render blue bricks to the screen
                blueBrickTexture.renderTexture(105, 150);

                //Render red bricks to the screen
                redBrickTexture.renderTexture(105, 175);

                //Render yellow bricks to the screen
                yellowBrickTexture.renderTexture(105, 200);

                //Render buttons
                gButtons.renderTexture();

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
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        success = false;
    }
    else
    {
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

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load Foo' texture
    if (!blueBrickTexture.loadFromFile("SDL_Image_Imports/Blue_Brick.png"))
    {
        printf("Failed to load Foo' texture image!\n");
        success = false;
    }

    //Load background texture
    if (!redBrickTexture.loadFromFile("SDL_Image_Imports/Red_Brick.png"))
    {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    //Load background texture
    if (!yellowBrickTexture.loadFromFile("SDL_Image_Imports/Yellow_Brick.png"))
    {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    //Load background texture
    if (!baseBackgroundTexture.loadFromFile("SDL_Image_Imports/Breakout_Layout.png"))
    {
        printf("Failed to load background texture image!\n");
        success = false;
    }

    //Load sprites
    if (!player_Board.loadFromFile("SDL_Image_Imports/player_board.png"))
    {
        printf("Failed to load button sprite texture!\n");
        success = false;
    }

    return success;
}

void closeWindow()
{
    //Free loaded images
    blueBrickTexture.free();
    redBrickTexture.free();
    yellowBrickTexture.free();
    baseBackgroundTexture.free();

    //Destroy window    
    SDL_DestroyRenderer(baseRenderer);
    SDL_DestroyWindow(baseWindow);
    baseWindow = NULL;
    baseRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}