#pragma once

#include "BPlayerControl.h"
#include "BBrickType.h"

extern BTexture baseBackgroundTexture;

class BGame : protected BGraphics, public BTexture
{
public:

	bool initWindow();

	bool loadMedia();

	void closeWindow();
};
