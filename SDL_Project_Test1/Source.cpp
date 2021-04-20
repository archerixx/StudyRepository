#include "BPlayerControl.h"
#include "BGame.h"
#include "BGame_Level_1_2.h"
#include "BGame_Level_2.h"

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
        //level states
        bool lvl_1_state = true;
        bool lvl_2_state = false;
        bool lvl_3_state = false;
        //score passed between levels
        int passTheScore = 0;
        //lives passed between levels
        int passLives = 0;

        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;
        
        //Create Level 1
        BGame_Level_1_2* Lvl1 = new BGame_Level_1_2;
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
                Lvl1->getPlayer()->handleEvent(&e);

                //Enable music with key 9 (to play/pause) and 0 (to stop)
                Lvl1->getBall()->getSound()->handleMusicEvent(&e);

                //start game with mouse click
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    Lvl1->setGameStart(true);
                }
            }

            //lvl1
            if (Lvl1->getGameStart())
            {
                Lvl1->mainGameLoop(lvl_2_state);
            }
            else
            {
                Lvl1->standByLoop();
            }

            //Level finished
            if (Lvl1->getBall()->getScore() >= 20) //980
            {
                //lvl_1_state = false;
                lvl_2_state = true;
                passTheScore = Lvl1->getBall()->getScore();
                passLives = Lvl1->getBall()->getBrickLevel_1()->getLevel_1()->getBallLives();
                break;
            }

            //if no more lifes, game over
            if (Lvl1->getGameOver())
            {
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
                    }
                    Lvl1->gameOverLoop();
                }
            }
        }
        
        //delete level 1
        delete Lvl1;

        //create Level 2 
        BGame_Level_2* Lvl2 = new BGame_Level_2;
        
        Lvl2->getBall()->setScore(passTheScore);
        Lvl2->getBall()->getBrickLevel_2()->getLevel_2()->setBallLives(passLives);
        
        Lvl2->getBall()->loadScoreAndLivesMedia(Lvl2->getBall()->getScore(), Lvl2->getBall()->getBrickLevel_2()->getLevel_2()->getBallLives());
        bool updateLevel_2 = false;
        //Lvl2->updateLevel();
        if (lvl_2_state)
        {
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
                    Lvl2->getPlayer()->handleEvent(&e);

                    //Enable music with key 9 (to play/pause) and 0 (to stop)
                    Lvl2->getBall()->getSound()->handleMusicEvent(&e);

                    //start game with mouse click
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        Lvl2->setGameStart(true);
                    }
                }

                //lvl2
                if (Lvl2->getGameStart())
                {
                    Lvl2->mainGameLoop(lvl_2_state);
                }
                else
                {
                    Lvl2->standByLoop(lvl_2_state);
                }
                
                //Update level
                if (Lvl2->getBall()->getHitCounter() == 5)
                {
                    updateLevel_2 = true;
                    Lvl2->getBall()->updateHitCounter();
                }

                if (updateLevel_2)
                {
                    Lvl2->updateLevel();
                    updateLevel_2 = false;
                }

                //Level finished
                if (Lvl2->getBall()->getScore() >= 990) //1980
                {
                    //lvl_2_state = false;
                    lvl_3_state = true;
                    passTheScore = Lvl2->getBall()->getScore();
                    passLives = Lvl2->getBall()->getBrickLevel_2()->getLevel_2()->getBallLives();
                    break;
                }

                //if no more lifes, game over
                if (Lvl2->getGameOver())
                {
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
                        }
                        Lvl2->gameOverLoop();
                    }
                }
            }
        }
        //delete level 2
        delete Lvl2;
        /*
        //Create level 3
        BGame_Level_2* Lvl3 = new BGame_Level_2;
        Lvl3->getBall()->setScore(passTheScore);
        Lvl3->getBall()->getBrickLevel_1()->getLevel_1()->setBallLives(passLives);
        Lvl3->getBall()->loadScoreAndLivesMedia(Lvl3->getBall()->getScore(), Lvl3->getBall()->getBrickLevel_1()->getLevel_1()->getBallLives());
        if (lvl_3_state)
        {
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
                    Lvl3->getPlayer()->handleEvent(&e);

                    //Enable music with key 9 (to play/pause) and 0 (to stop)
                    Lvl3->getBall()->getSound()->handleMusicEvent(&e);

                    //start game with mouse click
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        Lvl3->setGameStart(true);
                    }
                }

            }
        }
        */
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