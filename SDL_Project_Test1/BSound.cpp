#include "BSound.h"

BSound::~BSound()
{
    //Free the music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
    Mix_FreeChunk(gMedium);
    gMedium = NULL;
    Mix_FreeChunk(gLow);
    gLow = NULL;
}

bool BSound::loadMusicMedia()
{
    //Loading success flag
    bool success = true;

    //Load music
    gMusic = Mix_LoadMUS("SDL_Image_Imports/BackgroundMusic.wav");
    if (gMusic == NULL)
    {
        std::cout << "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError();
        success = false;
    }
    gMedium = Mix_LoadWAV("SDL_Image_Imports/medium.wav");
    if (gMedium == NULL)
    {
        std::cout << "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError();
        success = false;
    }
    gLow = Mix_LoadWAV("SDL_Image_Imports/low.wav");
    if (gLow == NULL)
    {
        std::cout << "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError();
        success = false;
    }

    return success;
}

void BSound::handleMusicEvent(SDL_Event* e)
{
    //Handle key press
    if (e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_9:
            //If there is no music playing
            if (Mix_PlayingMusic() == 0)
            {
                //Play the music
                Mix_PlayMusic(gMusic, -1);
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
