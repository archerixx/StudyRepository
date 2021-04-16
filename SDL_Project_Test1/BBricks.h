#pragma once

#include "BBrickType.h"
#include "BLevel.h"

class BBricks : public BBrickType
{
private:
	//Brick types
	BBrickType BrickSoftYellow[11];
	BBrickType BrickMediumBlue[11];
	BBrickType BrickHardRed[11];

	//Level 1
	BLevel* Level_1 = new BLevel;

	//Bricks row start positions on Y axis
	const int BrickSoftYellow_Y_Start = 200;
	const int BrickMediumBlue_Y_Start = 175;
	const int BrickHardRed_Y_Start = 150;

	int BrickLifeCounter;

public:

	//GET for Brick elements
	BBrickType* getSoftYellowBrick(int element);
	BBrickType* getMediumBlueBrick(int element);
	BBrickType* getHardRedBrick(int element);

	//SET for Bricks
	void setYellowBrick();
	void setBlueBrick();
	void setRedBrick();

	BLevel* getLevel();

};