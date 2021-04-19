#include "BLevel.h"

BLevel::BLevel()
{
	brickRowCount = 3;
	brickColumnCount = 11;
	brickRowSpacing = 5;
	brickColumnSpacing = 5;
	backgroundTexture = "SDL_Image_Imports/retro_arcade_background.png";
	ballLives = 3;
}

BLevel::BLevel(int rowCount, int columnCount, int rowSpacing, int columnSpacing, const char* backGroundTexture, int ballLives)
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
int BLevel::getRowCount() const
{
	return brickRowCount;
}
int BLevel::getColumnCount() const
{
	return brickColumnCount;
}
int BLevel::getRowSpacing() const
{
	return brickRowSpacing;
}
int BLevel::getColumtSpacing() const
{
	return brickColumnSpacing;
}
const char* BLevel::getBackGroundTexture() const
{
	return backgroundTexture;
}
int BLevel::getBallLives() const
{
	return ballLives;
}

/*
	SETs
*/
void BLevel::setBrickRowCount(int rowCount)
{
	this->brickRowCount = rowCount;
}
void BLevel::setBrickColumnCount(int columnCount)
{
	this->brickColumnCount = columnCount;
}
void BLevel::setBrickRowSpacing(int rowSpacing)
{
	this->brickRowSpacing = rowSpacing;
}
void BLevel::setbrickColumnSpacing(int columnSpacing)
{
	this->brickColumnSpacing = columnSpacing;
}
void BLevel::setBackgroundTexture(const char* backgroundTexture)
{
	this->backgroundTexture = backgroundTexture;
}
void BLevel::setBallLives(int lifesLeft)
{
	this->ballLives = lifesLeft;
}