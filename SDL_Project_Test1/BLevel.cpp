#include "BLevel.h"

BLevel::BLevel()
{
	RowCount = 3;
	ColumnCount = 11;
	RowSpacing = 5;
	ColumnSpacing = 5;
	BackGroundTexture = "SDL_Image_Imports/Breakout_Layout.png";
}

BLevel::BLevel(int RC, int CC, int RS, int CS, const char* BGT)
{
	RowCount = RC;
	ColumnCount = CC;
	RowSpacing = RS;
	ColumnSpacing = CS;
	BackGroundTexture = BGT;
}

int BLevel::getRowCount() const
{
	return RowCount;
}

int BLevel::getColumnCount() const
{
	return ColumnCount;
}

int BLevel::getRowSpacing() const
{
	return RowSpacing;
}

int BLevel::getColumtSpacing() const
{
	return ColumnSpacing;
}

const char* BLevel::getBackGroundTexture() const
{
	return BackGroundTexture;
}
