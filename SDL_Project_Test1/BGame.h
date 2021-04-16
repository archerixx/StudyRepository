#pragma once

#include "BPlayerControl.h"
#include "BBrickType.h"
#include "BSound.h"

extern BTexture baseBackgroundTexture;
extern BTexture gTextTexture;

class BGame : protected BGraphics, public BTexture
{
public:

	bool initWindow();

	bool loadMedia();

	void closeWindow();
};
