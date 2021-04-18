#include "BBrickType.h"

BBrickType::BBrickType()
{
	this->brickTexturePath = "";
	this->hitPoints = 0;
	this->breakScore = 0;

	BrickSoftYellowTexture = new BTexture;
	BrickMediumBlueTexture = new BTexture;
	BrickHardRedTexture = new BTexture;
}
BBrickType::~BBrickType()
{
	BrickSoftYellowTexture->clearTexture();
	delete BrickSoftYellowTexture;
	BrickSoftYellowTexture = NULL;
	BrickMediumBlueTexture->clearTexture();
	delete BrickMediumBlueTexture;
	BrickMediumBlueTexture = NULL;
	BrickHardRedTexture->clearTexture();
	delete BrickHardRedTexture;
	BrickHardRedTexture = NULL;
}

/*
	SETs
*/
void BBrickType::setBrickTexturePath(const char* bTexture)
{
	this->brickTexturePath = bTexture;
}
void BBrickType::setHitPoints(int bHitPoints)
{
	this->hitPoints = bHitPoints;
}
void BBrickType::setBreakScore(int bScore)
{
	this->breakScore = bScore;
}

/*
	GETs
*/
const char* BBrickType::getBrickTexturePath() const
{
	return brickTexturePath;
}
int BBrickType::getHitPoints() const
{
	return hitPoints;
}
int BBrickType::getBreakScore() const
{
	return breakScore;
}

/*
	SET brick boarder element
*/
void BBrickType::setBrickBoarderOn_X_Element(int index, int element)
{
	BrickBoarderOn_X[index] = element;
}
void BBrickType::setBrickBoarderOn_Y_Element(int index, int element)
{
	BrickBoarderOn_Y[index] = element;
}

/*
	GET brick boarder element
*/
int BBrickType::getBrickBoarderOn_X_Element(int element) const
{
	return BrickBoarderOn_X[element];
}
int BBrickType::getBrickBoarderOn_Y_Element(int element) const
{
	return BrickBoarderOn_Y[element];
}

//Update/moved brick on Y axis
void BBrickType::updateBrickBoarder_Y_axis(int y)
{
	BrickBoarderOn_Y[0] += y;
	BrickBoarderOn_Y[1] += y;
}

/*
	Render bricks
*/
void BBrickType::renderYellowBrick(int x, int y)
{
	BrickSoftYellowTexture->renderTexture(x, y);
}
void BBrickType::renderBlueBrick(int x, int y)
{
	BrickMediumBlueTexture->renderTexture(x, y);
}
void BBrickType::renderRedBrick(int x, int y)
{
	BrickHardRedTexture->renderTexture(x, y);
}

/*
	Load brick media
*/
bool BBrickType::loadYellowBrickMedia(const char* path)
{
	//Loading success flag
	bool success = true;

	if (!BrickSoftYellowTexture->loadFromFile(path))
	{
		std::cout << "Failed to load Yellow Brick texture!\n";
		success = false;
	}

	return success;
}
bool BBrickType::loadBlueBrickMedia(const char* path)
{
	//Loading success flag
	bool success = true;

	if (!BrickMediumBlueTexture->loadFromFile(path))
	{
		std::cout << "Failed to load Blue Brick texture!\n";
		success = false;
	}

	return success;
}
bool BBrickType::loadRedBrickMedia(const char* path)
{
	//Loading success flag
	bool success = true;

	if (!BrickHardRedTexture->loadFromFile(path))
	{
		std::cout << "Failed to load Red Brick texture!\n";
		success = false;
	}

	return success;
}

/*
	Clear brick texture
*/
void BBrickType::clearYellowTexture()
{
	BrickSoftYellowTexture->clearTexture();
}
void BBrickType::clearBlueTexture()
{
	BrickMediumBlueTexture->clearTexture();
}
void BBrickType::clearRedTexture()
{
	BrickHardRedTexture->clearTexture();
}
