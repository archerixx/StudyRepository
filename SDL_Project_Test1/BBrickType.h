#pragma once

#include "BTexture.h"

class BBrickType
{
public:
	//Constructor
	BBrickType();

	//Destructor
	~BBrickType();

	//SET functions for private variables
	void setBrickTexturePath(const char* bTexture);
	void setHitPoints(int bHitPoints);
	void setBreakScore(int bScore);

	//GET function for private vraiables
	const char* getBrickTexturePath() const;
	int getHitPoints() const;
	int getBreakScore() const;

	//SET boarder element for X or Y axis
	void setBrickBoarderOn_X_Element(int index, int element);
	void setBrickBoarderOn_Y_Element(int index, int element);

	//GET boarder element on X/Y axis
	int getBrickBoarderOn_X_Element(int element) const;
	int getBrickBoarderOn_Y_Element(int element) const;

	//update/move bricks on y-axis
	void updateBrickBoarder_Y_axis(int y);

	//render bricks
	void renderYellowBrick(int x, int y);
	void renderBlueBrick(int x, int y);
	void renderRedBrick(int x, int y);

	//load media for bricks
	bool loadYellowBrickMedia(const char* path);
	bool loadBlueBrickMedia(const char* path);
	bool loadRedBrickMedia(const char* path);

	//clear brick texture media
	void clearYellowTexture();
	void clearBlueTexture();
	void clearRedTexture();

private: 
	//brick testure path
	const char* brickTexturePath;
	//brick hit points
	int hitPoints;
	//brick break gameScore
	int breakScore;

	//Boarders of brick on X and Y axis
	int BrickBoarderOn_X[2] = {0};
	int BrickBoarderOn_Y[2] = {0};

	//Bricks texture
	BTexture* BrickSoftYellowTexture;
	BTexture* BrickMediumBlueTexture;
	BTexture* BrickHardRedTexture;
};

