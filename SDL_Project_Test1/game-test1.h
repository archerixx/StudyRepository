
#include "BTexture.h"

SDL_Window* baseWindow = NULL;
SDL_Renderer* baseRenderer = NULL;
BTexture game;

class BPlayerControl
{
public:
    BPlayerControl();

    //start position that will be in relation to actual mouse position
    void setBoardPosition(int x, int y);

    //mouse event/movement
    void handleEvent(SDL_Event* e);

    //shows player board, moving around
    void renderTexture();

    BTexture player_Board;

private:
    //coordinateds of start position
    SDL_Point mPosition;
};

BPlayerControl::BPlayerControl()
{
    mPosition.x = 370;
    mPosition.y = 570;
}

void BPlayerControl::setBoardPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void BPlayerControl::handleEvent(SDL_Event* e)
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
            if (x < mPosition.x)
            {
                mPosition.x = mPosition.x - 10;
                if (mPosition.x == 90)
                    mPosition.x = mPosition.x + 10;
                inside = false;
            }
            else if (x > mPosition.x + game.getBoardWidth())
            {
                mPosition.x = mPosition.x + 10;
                if (mPosition.x == 610)
                    mPosition.x = mPosition.x - 10;
                inside = false;
            }
            else if (y < mPosition.y)
            {
                inside = false;
            }
            else if (y > mPosition.y + game.getBoardHeight())
            {
                inside = false;
            }
        default:
            break;
        }
    }
}

void BPlayerControl::renderTexture()
{
    player_Board.renderTexture(mPosition.x, mPosition.y);
}

BPlayerControl gButtons;
BTexture player_Board;

BTexture blueBrickTexture;
BTexture redBrickTexture;
BTexture yellowBrickTexture;
BTexture baseBackgroundTexture;

void startGame();
bool initWindow();
void closeWindow();
bool loadMedia();

int main(int argc, char* args[])
{
    startGame();
    return 0;
}

void startGame()
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
        baseWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game.getScreenWidth(), game.getScreenHeight(), SDL_WINDOW_SHOWN);
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
        printf("\nFailed to load Foo' texture image!\n");
        success = false;
    }

    //Load background texture
    if (!redBrickTexture.loadFromFile("SDL_Image_Imports/Red_Brick.png"))
    {
        printf("\nFailed to load background texture image!\n");
        success = false;
    }

    //Load background texture
    if (!yellowBrickTexture.loadFromFile("SDL_Image_Imports/Yellow_Brick.png"))
    {
        printf("\nFailed to load background texture image!\n");
        success = false;
    }

    //Load background texture
    if (!baseBackgroundTexture.loadFromFile("SDL_Image_Imports/Breakout_Layout.png"))
    {
        printf("\nFailed to load background texture image!\n");
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
    blueBrickTexture.clearTexture();
    redBrickTexture.clearTexture();
    yellowBrickTexture.clearTexture();
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