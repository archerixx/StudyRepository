#pragma once

#include <SDL_mixer.h>
#include "BGraphics.h"

class BSound
{

public:
	//The music that will be played
	Mix_Music* gMusic = NULL;

	//The sound effects that will be useds
	Mix_Chunk* gMedium = NULL;
	Mix_Chunk* gLow = NULL;

	bool loadMusic();
};