#include "BPlayerControl.h"
#include "BBall.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 648;

//The window we'll be rendering to
SDL_Window* baseWindow = NULL;
//The window renderer
SDL_Renderer* baseRenderer = NULL;
//Globally used font
TTF_Font* baseFont = NULL;

bool initWindow();
void startGame();
void closeWindow();

//BBrickType BrickInvPurple('I', "SDL_Image_Imports/Purple_Brick.png", 0);

int main(int argc, char* args[])
{
	startGame();
	return 0;
}

bool initWindow()
{
    //Initialization flag - check if function ends successfully
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
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
                std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
                success = false;
            }
            else
            {
                //Initialize renderer color (2D)
                SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
                    success = false;
                }

                //Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError();
                    success = false;
                }

                //Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    std::cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError();
                    success = false;
                }
            }
        }
    }

    return success;
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
        BBall gBall;
        BPlayerControl gPlayer;

        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        //Start game flag
        bool start = false;

        //bool updateBrick = true;
        int tempScore = 0;

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
                    break;
                }
                    
                //Handle mouse motion events
                gPlayer.handleEvent(&e);

                //Enable music with key 9 (to play/pause) and 0 (to stop)
                gBall.getSound()->handleMusicEvent(&e);

                //start game with mouse click
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    start = true;
                }
            }
            //if mouse button is clicked, start game
            if (start)
            {
                //Clear screen
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(baseRenderer);

                //Render background texture to screen
                gBall.renderBackground();

                //render bricks from level
                for (int i = 0; i < gBall.getBrick()->getLevel()->getColumnCount(); i++)
                {
                    gBall.getBrick()->getSoftYellowBrick(i)->renderYellowBrick(gBall.getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
                    gBall.getBrick()->getMediumBlueBrick(i)->renderBlueBrick(gBall.getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
                    gBall.getBrick()->getHardRedBrick(i)->renderRedBrick(gBall.getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
                }

                //keep previous score
                tempScore = gBall.getScore();

                //ball movement/collision
                gBall.ballMovementAndCollision(gPlayer.getBoardPosition().x, gPlayer.getBoardPosition().y);

                //checks if it is game over
                if (gBall.getBrick()->getLevel()->getBallLifes() == 0)
                {
                    break;
                }
                //if game is not lost, reset ball on board and wait for mouse click
                else if (gBall.getLifeLostState() == true)
                {
                    start = false;
                }

                //if score is changed, load and render it on screen
                if (gBall.getScore() > tempScore)
                {
                    gBall.loadScoreMedia(gBall.getScore());
                }
                gBall.getScoreTexture()->renderTexture(700, 600);

                //game delay, speed
                SDL_Delay(2);

                //Render player board
                gPlayer.renderPlayerBoard();

                //Update screen
                SDL_RenderPresent(baseRenderer);                   
            }
            //show starting textures, wait for mouse click
            else
            {
                //Clear screen
                SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(baseRenderer);

                //Render background texture to screen
                gBall.renderBackground();

                //render bricks from level
                for (int i = 0; i < gBall.getBrick()->getLevel()->getColumnCount(); i++)
                {
                    gBall.getBrick()->getSoftYellowBrick(i)->renderYellowBrick(gBall.getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
                    gBall.getBrick()->getMediumBlueBrick(i)->renderBlueBrick(gBall.getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
                    gBall.getBrick()->getHardRedBrick(i)->renderRedBrick(gBall.getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
                }

                //render ball on board
                gBall.setBallPoint(gPlayer.getBoardPosition().x + gBall.getBoardWidth() / 2, gPlayer.getBoardPosition().y - gBall.getBallSize());
                gBall.renderBall(gPlayer.getBoardPosition().x + gBall.getBoardWidth() / 2, gPlayer.getBoardPosition().y - gBall.getBallSize());

                //Render player board
                gPlayer.renderPlayerBoard();

                //Render current frame
                gBall.getScoreTexture()->renderTexture(700, 600);
                //gTextTexture.renderTexture(700, 600);

                //Update screen
                SDL_RenderPresent(baseRenderer);
            }
        }
    }

    //Free resources and close SDL
    closeWindow();
}



void closeWindow()
{
    //Destroy window    
    SDL_DestroyRenderer(baseRenderer);
    SDL_DestroyWindow(baseWindow);
    baseRenderer = NULL;
    baseWindow = NULL;

    //Free global font
    TTF_CloseFont(baseFont);
    baseFont = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

//idea for next level
                /*
                if (gBall.getHitCounter() == 2 && updateBrick == true)
                {
                    for (int i = 0; i < 11; i++)
                    {
                        gBall.getBrick()->getSoftYellowBrick(i)->updateBrickBoarder_Y_axis(20);
                        gBall.getBrick()->getMediumBlueBrick(i)->updateBrickBoarder_Y_axis(20);
                        gBall.getBrick()->getHardRedBrick(i)->updateBrickBoarder_Y_axis(20);
                    }
                    updateBrick = false;
                }
                else if (gBall.getHitCounter() ==5)
                {
                    updateBrick = true;
                }
                else if (gBall.getHitCounter() == 7 && updateBrick == true)
                {
                    for (int i = 0; i < 11; i++)
                    {
                        gBall.getBrick()->getSoftYellowBrick(i)->updateBrickBoarder_Y_axis(20);
                        gBall.getBrick()->getMediumBlueBrick(i)->updateBrickBoarder_Y_axis(20);
                        gBall.getBrick()->getHardRedBrick(i)->updateBrickBoarder_Y_axis(20);
                    }

                    updateBrick = false;
                }
                */