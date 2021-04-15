#include "BBrickType.h"

BBrickType::BBrickType()
{
	this->brickID = 0;
	this->brickTexturePath = "";
	this->hitPoints = 0;
	//BrickSoftYellowTextureTest = NULL;
}

BBrickType::BBrickType(char bID, const char* bTexture, int bHitPoints)
{
	this->brickID = bID;
	this->brickTexturePath = bTexture;
	this->hitPoints = bHitPoints;
	//hitSound = bHitSound;
	//breakSound = bBreakSound;
	//breakScore = bBreakScore;
}
void BBrickType::clearTexture()
{
	BrickSoftYellowTexture.clearTexture();
}
/*
BBrickType::~BBrickType()
{
	delete BrickSoftYellowTextureTest;
}
*/
void BBrickType::setBrickID(char bID)
{
	this->brickID = bID;
}

void BBrickType::setBrickTexturePath(const char* bTexture)
{
	this->brickTexturePath = bTexture;
}

void BBrickType::setHitPoints(int bHitPoints)
{
	this->hitPoints = bHitPoints;
}

int BBrickType::getBrickID() const
{
	return brickID;
}

const char* BBrickType::getBrickTexturePath() const
{
	return brickTexturePath;
}

int BBrickType::getHitPoints() const
{
	return hitPoints;
}

void BBrickType::setBrickBoarderOn_X_Element(int index, int element)
{
	BrickBoarderOn_X[index] = element;
}

void BBrickType::setBrickBoarderOn_Y_Element(int index, int element)
{
	BrickBoarderOn_Y[index] = element;
}

int BBrickType::getBrickBoarderOn_X_Element(int element)
{
	return BrickBoarderOn_X[element];
}

int BBrickType::getBrickBoarderOn_Y_Element(int element)
{
	return BrickBoarderOn_Y[element];
}

void BBrickType::setYellowBrickTexture(BTexture& texture)
{
	BrickSoftYellowTexture = texture;
}

BTexture BBrickType::getYellowBrickTexture()
{
	return BrickSoftYellowTexture;
}

void BBrickType::renderYellowBrick(int x, int y)
{
	BrickSoftYellowTexture.renderTexture(x, y);
}

void BBrickType::renderBlueBrick(int x, int y)
{
	BrickMediumBlueTexture.renderTexture(x, y);
}

void BBrickType::renderRedBrick(int x, int y)
{
	BrickHardRedTexture.renderTexture(x, y);
}

bool BBrickType::loadYellowBrickMedia(const char* path)
{
	//Loading success flag
	bool success = true;

	if (!BrickSoftYellowTexture.loadFromFile(path))
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

	if (!BrickMediumBlueTexture.loadFromFile(path))
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

	if (!BrickHardRedTexture.loadFromFile(path))
	{
		std::cout << "Failed to load Red Brick texture!\n";
		success = false;
	}

	return success;
}
/*
void BBrickType::renderYellowBrickTest(int x, int y)
{
	BrickSoftYellowTextureTest->renderTexture(x, y);
}

bool BBrickType::loadYellowBrickMediaTest()
{
	//Loading success flag
	bool success = true;

	if (!BrickSoftYellowTextureTest->loadFromFile("SDL_Image_Imports/Yellow_Brick.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}

	return success;

}
*/