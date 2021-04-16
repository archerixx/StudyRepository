#include "BGame.h"
#include "BBall.h"

//The window we'll be rendering to
SDL_Window* baseWindow = NULL;
//The window renderer
SDL_Renderer* baseRenderer = NULL;
//Globally used font
TTF_Font* baseFont = NULL;

//game object
BGame game;

BSound gSound;

void startGame();

BBrickType BrickInvPurple('I', "SDL_Image_Imports/Purple_Brick.png", 0);

int main(int argc, char* args[])
{
	startGame();
	return 0;
}

void startGame()
{
    //Start up SDL and create window
    if (!game.initWindow())
    {
        std::cout << "Failed to initialize!\n";
    }
    else
    {
        //Load media
        if (!game.loadMedia())
        {
            std::cout << "Failed to load media!\n";
        }
        else
        {

            int tempScore = 0;

            BBall gBall;
            BPlayerControl gPlayer;
            gSound.loadMusic();

            //Main loop flag
            bool quit = false;
            //Event handler
            SDL_Event e;

            //Start game flag
            bool start = false;

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
                    gPlayer.handleEvent(&e);
                    
                    if (e.type == SDL_MOUSEBUTTONUP)
                    {
                        start = true;
                    }

                    //Handle key press
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_9:
                            //If there is no music playing
                            if (Mix_PlayingMusic() == 0)
                            {
                                //Play the music
                                Mix_PlayMusic(gSound.gMusic, -1);
                            }
                            //If music is being played
                            else
                            {
                                //If the music is paused
                                if (Mix_PausedMusic() == 1)
                                {
                                    //Resume the music
                                    Mix_ResumeMusic();
                                }
                                //If the music is playing
                                else
                                {
                                    //Pause the music
                                    Mix_PauseMusic();
                                }
                            }
                            break;

                        case SDLK_0:
                            //Stop the music
                            Mix_HaltMusic();
                            break;
                        }
                    }

                }
                if (start)
                {

                    //Clear screen
                    SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(baseRenderer);

                    //Render background texture to screen
                    baseBackgroundTexture.renderTexture(0, 0);

                    for (int i = 0; i < 11; i++)
                    {
                        gBall.getBrick()->getSoftYellowBrick(i)->renderYellowBrick(gBall.getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
                        gBall.getBrick()->getMediumBlueBrick(i)->renderBlueBrick(gBall.getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
                        gBall.getBrick()->getHardRedBrick(i)->renderRedBrick(gBall.getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
                    }

                    tempScore = gBall.getScore();

                    gBall.ballMovementAndCollision(gPlayer.getBoardPosition().x, gPlayer.getBoardPosition().y);

                    if (gBall.getBrick()->getLevel()->getBallLifes() == 0)
                    {
                        break;
                    }
                    else if (*gBall.lifeLost == true)
                    {
                        start = false;
                    }

                    if (gBall.getScore() > tempScore)
                    {
                        gBall.loadScoreMedia(gBall.getScore());
                    }
                    gBall.getScoreTexture()->renderTexture(700, 600);

                    SDL_Delay(2);

                    //Render player board
                    gPlayer.renderPlayerBoard();

                    //Update screen
                    SDL_RenderPresent(baseRenderer);
                }
                else
                {
                    //Clear screen
                    SDL_SetRenderDrawColor(baseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(baseRenderer);

                    //Render background texture to screen
                    baseBackgroundTexture.renderTexture(0, 0);

                    for (int i = 0; i < 11; i++)
                    {
                        gBall.getBrick()->getSoftYellowBrick(i)->renderYellowBrick(gBall.getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0));
                        gBall.getBrick()->getMediumBlueBrick(i)->renderBlueBrick(gBall.getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0));
                        gBall.getBrick()->getHardRedBrick(i)->renderRedBrick(gBall.getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0), gBall.getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0));
                    }

                    gBall.renderBall(gPlayer.getBoardPosition().x + gPlayer.BGraph.getBoardWidth() / 2, gPlayer.getBoardPosition().y - gBall.getBallSize());
                    gBall.setBallPoint(gPlayer.getBoardPosition().x + gPlayer.BGraph.getBoardWidth() / 2, gPlayer.getBoardPosition().y - gBall.getBallSize());

                    //Render player board
                    gPlayer.renderPlayerBoard();

                    //Render current frame
                    gBall.getScoreTexture()->renderTexture(700, 600);
                    //gTextTexture.renderTexture(700, 600);

                    //Update screen
                    SDL_RenderPresent(baseRenderer);
                }

            }
            std::cout << gBall.getScore();
        }
    }

    //Free resources and close SDL
    game.closeWindow();
}
