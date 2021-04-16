#include "BSound.h"

bool BSound::loadMusic()
{
    //Loading success flag
    bool success = true;

    //Load music
    gMusic = Mix_LoadMUS("SDL_Image_Imports/BackgroundMusic.wav");
    if (gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gMedium = Mix_LoadWAV("SDL_Image_Imports/medium.wav");
    if (gMedium == NULL)
    {
        printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    gLow = Mix_LoadWAV("SDL_Image_Imports/low.wav");
    if (gLow == NULL)
    {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}