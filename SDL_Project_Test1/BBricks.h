#pragma once

#include "BBrickType.h"
#include "BLevel.h"

class BBricks : public BBrickType, public BGraphics
{
public:
	//Construcor
	BBricks();
	//Destructor
	~BBricks();

	//GET for Brick elements
	BBrickType* getSoftYellowBrick(int element);
	BBrickType* getMediumBlueBrick(int element);
	BBrickType* getHardRedBrick(int element);
	//GET current level
	BLevel* getLevel();

	//SET for Bricks
	void setYellowBrick();
	void setBlueBrick();
	void setRedBrick();

	//SETs for brick position on Y axis
	void setBrickSoftYellow_Y_Start(int position_y);
	void setBrickMediumBlue_Y_Start(int position_y);
	void setBrickHardRed_Y_Start(int position_y);
	
private:
	//Brick types
	BBrickType** BrickSoftYellow;
	BBrickType** BrickMediumBlue;
	BBrickType** BrickHardRed;

	//Level 1
	BLevel* Level_1;

	//Bricks row start positions on Y axis
	int BrickSoftYellow_Y_FromStart;
	int BrickMediumBlue_Y_FromStart;
	int BrickHardRed_Y_FromStart;
};