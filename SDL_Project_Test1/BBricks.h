#pragma once

#include "BBrickType.h"
#include "BLevel.h"

class BBricks : public BBrickType, public BGraphics
{
public:
	//Construcor
	BBricks();
	BBricks(bool thirdLevel);
	//Destructor
	~BBricks();

	//GET for Brick elements
	BBrickType* getSoftYellowBrick(int element);
	BBrickType* getMediumBlueBrick(int element);
	BBrickType* getHardRedBrick(int element);
	BBrickType* getImpenetrablePurpleBrick(int element);
	//GET current level
	BLevel* getLevel_1();
	BLevel* getLevel_2();

	//SET for Bricks
	void setYellowBrick(bool thridLevel, int columnCount, int rowSpacing);
	void setBlueBrick(bool thridLevel, int columnCount, int rowSpacing);
	void setRedBrick(bool thridLevel, int columnCount, int rowSpacing);
	void setPurpleBrick();

	//TODO - CHECK IF THERE ARE NEEDED
	//SETs for brick position on Y axis
	void setBrickSoftYellow_Y_Start(int position_y);
	void setBrickMediumBlue_Y_Start(int position_y);
	void setBrickHardRed_Y_Start(int position_y);
	void setBrickImpenetrablePurple_Y_Start(int position_y);
	
private:
	//Brick types
	BBrickType** BrickSoftYellow;
	BBrickType** BrickMediumBlue;
	BBrickType** BrickHardRed;
	BBrickType** BrickImpenetrablePurple;

	//Level 1
	BLevel* Level_1;
	BLevel* Level_2;

	//flag for destructor
	bool callDestructor = false;

	//Bricks row start positions on Y axis
	int BrickSoftYellow_Y_FromStart;
	int BrickSoftYellow_Y_ToEnd;
	int BrickMediumBlue_Y_FromStart;
	int BrickMediumBlue_Y_ToEnd;
	int BrickHardRed_Y_FromStart;
	int BrickHardRed_Y_ToEnd;
	int BrickImpenetrable_Y_FromStart;
	
};