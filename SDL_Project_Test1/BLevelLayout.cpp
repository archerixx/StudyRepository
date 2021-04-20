#include "BLevelLayout.h"

BLevelLayout::BLevelLayout()
{
	brickRowCount = 3;
	brickColumnCount = 11;
	brickRowSpacing = 5;
	brickColumnSpacing = 5;
	backgroundTexture = "SDL_Image_Imports/retro_arcade_background.png";
	ballLives = 3;
}

BLevelLayout::BLevelLayout(int rowCount, int columnCount, int rowSpacing, int columnSpacing, const char* backGroundTexture, int ballLives)
{
	this->brickRowCount = rowCount;
	this->brickColumnCount = columnCount;
	this->brickRowSpacing = rowSpacing;
	this->brickColumnSpacing = columnSpacing;
	this->backgroundTexture = backGroundTexture;
	this->ballLives = ballLives;
}

/*
	GETs
*/
int BLevelLayout::getRowCount() const
{
	return brickRowCount;
}
int BLevelLayout::getColumnCount() const
{
	return brickColumnCount;
}
int BLevelLayout::getRowSpacing() const
{
	return brickRowSpacing;
}
int BLevelLayout::getColumtSpacing() const
{
	return brickColumnSpacing;
}
const char* BLevelLayout::getBackGroundTexture() const
{
	return backgroundTexture;
}
int BLevelLayout::getBallLives() const
{
	return ballLives;
}

/*
	SETs
*/
void BLevelLayout::setBrickRowCount(int rowCount)
{
	this->brickRowCount = rowCount;
}
void BLevelLayout::setBrickColumnCount(int columnCount)
{
	this->brickColumnCount = columnCount;
}
void BLevelLayout::setBrickRowSpacing(int rowSpacing)
{
	this->brickRowSpacing = rowSpacing;
}
void BLevelLayout::setbrickColumnSpacing(int columnSpacing)
{
	this->brickColumnSpacing = columnSpacing;
}
void BLevelLayout::setBackgroundTexture(const char* backgroundTexture)
{
	this->backgroundTexture = backgroundTexture;
}
void BLevelLayout::setBallLives(int lifesLeft)
{
	this->ballLives = lifesLeft;
}